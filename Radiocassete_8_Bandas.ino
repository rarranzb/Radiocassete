// =============================================================
// ADAU1701-TCPi-ESP32  — ver version.h
// =============================================================

#include "version.h"       // ← FW_VERSION, FW_DATE
#include "user_config.h"   // ← parámetros configurables del proyecto

#include <WiFi.h>
#include <Wire.h>
#include <WebServer.h>
#include <Preferences.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <Update.h>
#include <SPIFFS.h>
#include <math.h>

#define BOOT_BUTTON_PIN    0
#define WAKE_PIN GPIO_NUM_4

#define EEPROM_I2C_ADDR   0x50

#define PARAM_RAM_END     0x03FF
#define PROG_RAM_START    0x0400
#define PROG_RAM_END      0x07FF
#define CTRL_REG_START    0x0800

#define SAFELOAD_DATA_0   0x0810
#define SAFELOAD_ADDR_0   0x0815
#define IST_BIT           0x20

#define CTRL_WRITE        0x09
#define CTRL_READ_REQ     0x0A
#define CTRL_READ_RESP    0x0B
#define BUFFER_SIZE       (1024 * 16)

#define LOG(fmt, ...) do { char _lb[256]; snprintf(_lb,sizeof(_lb),fmt,##__VA_ARGS__); logWrite(_lb); } while(0)
#define LOGLN(msg)    do { logWrite(msg); logWrite("\n"); } while(0)

#define EEPROM_MAX_SIZE   (32 * 1024)
#define EEPROM_PAGE_SIZE  64
#define CAPTURE_MAX_SIZE  (28 * 1024)

#define EQ_NUM_BANDS    8
#define EQ_SAMPLE_RATE  48000.0f
#define EQ_MEM_SLOTS    5

Preferences  prefs;
WiFiServer*  tcpServer = nullptr;
WiFiClient   client;
WebServer    httpServer(80);

bool     apMode          = false;
bool     dspRunning      = false;
bool     logEnabled      = false;
uint8_t  lastCoreCtrl[2] = {0x00, 0x1C};
uint8_t  rxBuffer[BUFFER_SIZE];
int      rxLen           = 0;

uint8_t  captureBuffer[CAPTURE_MAX_SIZE];
int      captureLen      = 0;
bool     captureReady    = false;
bool     pendingDspReset = false;

// ── Esquema DSP activo ────────────────────────────────────
// -1 = desconocido, 0..3 = banco, 99 = SigmaStudio
int      activeRamSource    = -1;   // qué programa corre en la RAM del DSP
int      activeEepromSource = -1;   // qué banco fue grabado en la EEPROM

String   savedSSID, savedPassword;
int      pinSCL, pinSDA, pinRESET, pinSELFBOOT, pinLED;

// ── Declaraciones adelantadas (Forward Declarations) ──────────
void loadConfig();
void loadEqBands();
void initHardware();
void scanI2C();
bool connectWiFi();
void setupHTTP();
void setupOTA();
void resetDSP();
void updateVU();
void ssePush(bool full = false);
void blinkLED(int count);
void logWrite(const char* msg);
int  processBuffer(uint8_t* buf, int len);
void safeloadChunk(uint16_t address, uint8_t* data, int words);
bool readEEPROM();
void saveActiveSources();

// Externas de schema_manager
void sendSchemaList();
void saveSchema();
void loadSchema();
void downloadSchema();
void uploadSchemaHandler();
void uploadSchemaData();
String getSchemaListJSON();

// Externas de backup_manager
void sendBackup();
void restoreHandler();
void restoreUploadData();

// Externas de EQ
void writeEqBand(int band);
void updateBassDSP();
void writeInputVol(uint16_t addr, float dB);

// Externas de Sine Tone (sine_tone.ino)
extern uint16_t addrSineLMask, addrSineLFreq, addrSineLIson;
extern uint16_t addrSineRMask, addrSineRFreq, addrSineRIson;
void setSineToneFreq(float hz);
void setSineToneEnable(bool on);

// ── Configuración de red y dispositivo (NVS, editables desde Config) ──
String   deviceHostname = HOSTNAME;
String   apSSID         = AP_SSID;
String   apPassword     = AP_PASSWORD;
String   otaPassword    = OTA_PASSWORD;
uint16_t tcpPort        = TCP_PORT;
uint8_t  dspI2cAddr     = DSP_I2C_ADDR;
uint32_t vuWindowMs     = VU_WINDOW_MS;

#define LOG_BUF_LINES  100
#define LOG_BUF_LEN    120
char     logBuf[LOG_BUF_LINES][LOG_BUF_LEN];
int      logBufHead  = 0;
int      logBufCount = 0;

enum EqType { EQ_PEAK = 0, EQ_LOW_SHELF = 1, EQ_HIGH_SHELF = 2 };
struct EqBand { float freq; float gainDb; float q; uint16_t baseAddr; EqType type; };

EqBand eqBands[EQ_NUM_BANDS] = {
  {  40.0f, 0.0f, 0.7f, EQ_BAND0_ADDR, EQ_LOW_SHELF},
  { 100.0f, 0.0f, 1.0f, EQ_BAND1_ADDR, EQ_PEAK},
  { 250.0f, 0.0f, 1.2f, EQ_BAND2_ADDR, EQ_PEAK},
  { 800.0f, 0.0f, 1.4f, EQ_BAND3_ADDR, EQ_PEAK},
  {2500.0f, 0.0f, 1.4f, EQ_BAND4_ADDR, EQ_PEAK},
  {5000.0f, 0.0f, 1.2f, EQ_BAND5_ADDR, EQ_PEAK},
  {10000.0f,0.0f, 1.0f, EQ_BAND6_ADDR, EQ_PEAK},
  {16000.0f,0.0f, 0.7f, EQ_BAND7_ADDR, EQ_HIGH_SHELF},
};

const float EQ_DEFAULT_FREQ[EQ_NUM_BANDS] = { 40.0f, 100.0f, 250.0f,  800.0f, 2500.0f, 5000.0f, 10000.0f, 16000.0f};
const float EQ_DEFAULT_GAIN[EQ_NUM_BANDS] = {  0.0f,   0.0f,   0.0f,    0.0f,    0.0f,    0.0f,     0.0f,     0.0f};
const float EQ_DEFAULT_Q[EQ_NUM_BANDS]    = {  0.7f,   1.0f,   1.2f,    1.4f,    1.4f,    1.2f,     1.0f,     0.7f};

bool  eqEnabled      = true;
bool  eqBootEnabled  = true;   // Cargar EQ al DSP en el arranque
int   eqActiveSlot   = -1;
float eqLastNX       = 0.0f;
float eqLastNY       = 0.0f;

// ── Dynamic Bass Boost ────────────────────────────────────────
float    bassFreq      = 40.0f;
float    bassBoost     = 9.0f;
float    bassCompRatio = 10.0f;    // ratio X:1 (1..20)
uint16_t addrBassFreq  = 0x0014;
uint16_t addrBassBoost = 0x001A;
uint16_t addrBassComp  = DEFAULT_ADDR_BASS_C;

// ── Input Volume ──────────────────────────────────────────────
float    inputVolBT        = 0.0f;    // dB, rango -30..+6
float    inputVolLineIn    = 0.0f;    // dB, rango -30..+6
float    inputVolSineTone  = 0.0f;    // dB, rango -30..+6
uint16_t addrInputVolBT    = DEFAULT_ADDR_INVOL_BT;
uint16_t addrInputVolLineIn= DEFAULT_ADDR_INVOL_LI;
uint16_t addrInputVolSineTone = DEFAULT_ADDR_INVOL_ST;

// ── DSP Lock ──────────────────────────────────────────────────
bool dspLocked = false;  // Cuando true, ningún control web escribe al DSP

// ── DAC Mute ─────────────────────────────────────────────────
bool dspMuted = false;    // Cuando true, DAC del ADAU1701 está muteado

// ── Line Input Mute ──────────────────────────────────────────
bool lineMuted = false;   // Cuando true, ADC (entrada de línea) muteado

// ── Sleep state (visible para SSE) ───────────────────────────
bool     sleepPending   = false;
int      sleepCountdown = -1;   // segundos restantes (-1 = no sleep)

// ── VU Meter ──────────────────────────────────────────────────
uint16_t      addrVuL  = DEFAULT_ADDR_VU_L;   // byte offset ReadBack L; ajustar en Config
uint16_t      addrVuR  = DEFAULT_ADDR_VU_R;   // byte offset ReadBack R; ajustar en Config
float         vuLevelL = 0.0f;
float         vuLevelR = 0.0f;
unsigned long vuLastMs  = 0;
unsigned long sseLastMs = 0;
unsigned long sseFullLastMs = 0;

void setup() {
  Serial.begin(115200);
  delay(500);


  pinMode(4, INPUT_PULLUP);   // por defecto estará en 1


  LOG("\n[BOOT] ADAU1701-TCPi-ESP32 v%s (%s)\n", FW_VERSION, FW_DATE);

  loadConfig();
  loadEqBands();
  if (!SPIFFS.begin(false)) {
    Serial.println("[SPIFFS] Formateando...");
    SPIFFS.format();
    SPIFFS.begin(false);
  }
  Serial.println("[SPIFFS] OK");
  initHardware();
  scanI2C();

  connectWiFi();
  // ── Power saving ──────────────────────────────────────────────
  WiFi.setSleep(false);   // Sleep ON bloquea sseClient.print() ~50ms por push
  Serial.println("[PWR] CPU 80MHz, WiFi sleep OFF, TX power 10dBm");

  setupHTTP();
  setupOTA();
  tcpServer = new WiFiServer(tcpPort);
  tcpServer->begin();

  blinkLED(apMode ? 10 : 2);
  Serial.printf("[BOOT] Ready  AP:192.168.4.1  STA:%s  TCP:%d\n",
    apMode ? "no conectado" : WiFi.localIP().toString().c_str(), TCP_PORT);

  // Arrancar DSP via selfboot EEPROM — incluye re-aplicar EQ y volúmenes
  // Necesario tanto en boot normal como en wake-from-deep-sleep
  resetDSP();
  Serial.println("[BOOT] DSP selfboot completado — dspRunning=true");
}

void loop() {
  httpServer.handleClient();
  if (!apMode) {
    ArduinoOTA.handle();
  }

  // VU meter (cada 15 ms) + SSE fast push (cada 35 ms) + SSE full push (cada 1s)
  unsigned long _now = millis();
  if (_now - vuLastMs >= 15) { vuLastMs = _now; updateVU(); }
  if (_now - sseLastMs >= 35) { sseLastMs = _now; ssePush(false); }
  if (_now - sseFullLastMs >= 1000) { sseFullLastMs = _now; ssePush(true); }

  if (pendingDspReset) {
    pendingDspReset = false;
    resetDSP();
  }

  // --- Lógica de reposo y botones (debe funcionar siempre, incluido apMode) ---
  static unsigned long sleepTimerMs = 0;
  static int lastNotifySec = -1;

  if (digitalRead(4) == HIGH) {
    if (!sleepPending) {
      sleepPending = true;
      sleepTimerMs = _now;
      LOGLN("[PWR] Orden de reposo (Pin 4 HIGH). Apagando en 90 segundos...");
      lastNotifySec = 90;
      sleepCountdown = 90;
    } else {
      unsigned long elapsed = _now - sleepTimerMs;
      int secondsLeft = (int)((90000 - elapsed) / 1000);
      sleepCountdown = secondsLeft > 0 ? secondsLeft : 0;
      if (elapsed >= 90000) {
        LOGLN("[PWR] Ejecutando Deep Sleep (ext0=0) ahora.");
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 0);
        delay(100);
        esp_deep_sleep_start();
      } else if (secondsLeft % 10 == 0 && secondsLeft != lastNotifySec) {
        lastNotifySec = secondsLeft;
        LOG("[PWR] Apagando en %d segundos...\n", secondsLeft);
      }
    }
  } else {
    if (sleepPending) {
      sleepPending = false;
      sleepCountdown = -1;
      lastNotifySec = -1;
      LOGLN("[PWR] Orden de reposo abortada. (Pin 4 LOW)");
    }
  }

  if (digitalRead(BOOT_BUTTON_PIN) == LOW) {
    delay(50);
    if (digitalRead(BOOT_BUTTON_PIN) == LOW) {
      LOGLN("[BTN] DSP reset");
      blinkLED(3);
      resetDSP();
      while (digitalRead(BOOT_BUTTON_PIN) == LOW) delay(10);
    }
  }

  if (WiFi.status() != WL_CONNECTED && !apMode) {
    LOGLN("[WiFi] Lost -> reconnecting...");
    connectWiFi();
  }

  if (!client || !client.connected()) {
    digitalWrite(pinLED, LOW);
    client = tcpServer->available();
    if (client) {
      Serial.printf("[TCP] Connection from %s\n", client.remoteIP().toString().c_str());
      digitalWrite(pinLED, HIGH);
      blinkLED(2);
      captureLen   = 0;
      captureReady = false;
      rxLen        = 0;
      dspRunning   = false;
    }
  }

  if (client && client.connected() && client.available()) {
    int n = client.readBytes(rxBuffer + rxLen, BUFFER_SIZE - rxLen);
    rxLen += n;
    int consumed = processBuffer(rxBuffer, rxLen);
    if (consumed > 0 && consumed < rxLen)
      memmove(rxBuffer, rxBuffer + consumed, rxLen - consumed);
    rxLen = (consumed <= rxLen) ? rxLen - consumed : 0;
  }
}

// =============================================================
// schema_manager.ino — Sistema de esquemas DSP
// =============================================================
//
// Permite guardar y cargar el binario completo de SigmaStudio
// (el program RAM) junto con las direcciones de parámetros
// actuales, para alternar de forma segura entre esquemas.
//
// Guarda en SPIFFS:
//  /schema_X.bin  -> archivo EEPROM binario (captureBuffer)
//  /schema_X.json -> direcciones de DSP y Config
// =============================================================

#include <Arduino.h>
#include <SPIFFS.h>

extern void directWrite(uint8_t i2cAddr, uint16_t regAddr, uint8_t* data, uint16_t dataLen);

#define MAX_SCHEMAS 4

String schemaBinPath(int slot) {
  return "/schema_" + String(slot) + ".bin";
}

String schemaJsonPath(int slot) {
  return "/schema_" + String(slot) + ".json";
}

bool hasSchema(int slot) {
  return SPIFFS.exists(schemaBinPath(slot)) && SPIFFS.exists(schemaJsonPath(slot));
}

// ── GET /schema/list ──────────────────────────────────────────
void sendSchemaList() {
  String j = "[";
  for (int i = 0; i < MAX_SCHEMAS; i++) {
    if (i > 0) j += ",";
    j += hasSchema(i) ? "true" : "false";
  }
  j += "]";
  httpServer.send(200, "application/json", j);
}

// ── GET /schema/state ──────────────────────────────────────────
// Igual que sendSchemaList pero de uso interno para la UI
String getSchemaListJSON() {
  String j = "[";
  for (int i = 0; i < MAX_SCHEMAS; i++) {
    if (i > 0) j += ",";
    j += hasSchema(i) ? "true" : "false";
  }
  j += "]";
  return j;
}

// ── POST /schema/save ────────────────────────────────────────
void saveSchema() {
  if (!httpServer.hasArg("slot")) {
    httpServer.send(400, "text/plain", "Missing slot");
    return;
  }
  int slot = httpServer.arg("slot").toInt();
  if (slot < 0 || slot >= MAX_SCHEMAS) {
    httpServer.send(400, "text/plain", "Invalid slot");
    return;
  }

  // Comprobar que hay una captura reciente lista para guardar
  if (!captureReady || captureLen == 0) {
    httpServer.send(400, "text/plain", "No hay captura de SigmaStudio en RAM");
    return;
  }

  // 1. Guardar el captureBuffer en SPIFFS (binario de la EEPROM)
  File fBin = SPIFFS.open(schemaBinPath(slot), FILE_WRITE);
  if (!fBin) {
    httpServer.send(500, "text/plain", "Error abriendo archivo .bin");
    return;
  }
  // Añadir la terminación de la EEPROM
  captureBuffer[captureLen++] = 0x00;
  captureBuffer[captureLen++] = 0x00;
  
  fBin.write(captureBuffer, captureLen);
  fBin.close();

  // Deshacer el apaño para evitar romper el próximo save_eeprom
  captureLen -= 2;

  // 2. Guardar las direcciones de variables en SPIFFS (.json)
  File fJson = SPIFFS.open(schemaJsonPath(slot), FILE_WRITE);
  if (!fJson) {
    httpServer.send(500, "text/plain", "Error abriendo archivo .json");
    return;
  }
  
  String j = "{";
  for (int b = 0; b < EQ_NUM_BANDS; b++) {
    j += "\"a" + String(b) + "\":" + String(eqBands[b].baseAddr) + ",";
  }
  j += "\"bfa\":" + String(addrBassFreq) + ",";
  j += "\"bba\":" + String(addrBassBoost) + ",";
  j += "\"bca\":" + String(addrBassComp) + ",";
  j += "\"ivbt\":" + String(addrInputVolBT) + ",";
  j += "\"ivli\":" + String(addrInputVolLineIn) + ",";
  j += "\"vul\":" + String(addrVuL) + ",";
  j += "\"vur\":" + String(addrVuR);
  j += "}";
  
  fJson.print(j);
  fJson.close();

  httpServer.send(200, "text/plain", "Esquema guardado en Banco " + String(slot + 1));
}

// ── GET /schema/download?slot=N ──────────────────────────────
// Descarga el .bin y .json del banco como un solo archivo binario
// con cabecera: [4 bytes binLen][binData][jsonData]
void downloadSchema() {
  if (!httpServer.hasArg("slot")) {
    httpServer.send(400, "text/plain", "Missing slot");
    return;
  }
  int slot = httpServer.arg("slot").toInt();
  if (slot < 0 || slot >= MAX_SCHEMAS || !hasSchema(slot)) {
    httpServer.send(400, "text/plain", "Banco vacio o invalido");
    return;
  }

  File fBin = SPIFFS.open(schemaBinPath(slot), FILE_READ);
  File fJson = SPIFFS.open(schemaJsonPath(slot), FILE_READ);
  if (!fBin || !fJson) {
    if (fBin) fBin.close();
    if (fJson) fJson.close();
    httpServer.send(500, "text/plain", "Error abriendo archivos");
    return;
  }

  uint32_t binSize  = fBin.size();
  uint32_t jsonSize = fJson.size();
  uint32_t totalSize = 4 + binSize + jsonSize;

  String filename = "banco_" + String(slot + 1) + ".rcbin";
  httpServer.sendHeader("Content-Disposition", "attachment; filename=\"" + filename + "\"");
  httpServer.setContentLength(totalSize);
  httpServer.send(200, "application/octet-stream", "");

  // cabecera: 4 bytes con el tamaño del .bin (little-endian)
  uint8_t hdr[4];
  hdr[0] = binSize & 0xFF;
  hdr[1] = (binSize >> 8) & 0xFF;
  hdr[2] = (binSize >> 16) & 0xFF;
  hdr[3] = (binSize >> 24) & 0xFF;
  httpServer.client().write(hdr, 4);

  // enviar .bin
  uint8_t buf[256];
  while (fBin.available()) {
    int n = fBin.read(buf, sizeof(buf));
    httpServer.client().write(buf, n);
  }
  fBin.close();

  // enviar .json
  while (fJson.available()) {
    int n = fJson.read(buf, sizeof(buf));
    httpServer.client().write(buf, n);
  }
  fJson.close();
}

// ── POST /schema/upload?slot=N ──────────────────────────────
// Recibe un archivo .rcbin y lo guarda en el slot indicado
static int _uploadSlot = -1;
static File _uploadBin;
static File _uploadJson;
static uint32_t _uploadBinSize = 0;
static uint32_t _uploadWritten = 0;
static bool _uploadHeaderParsed = false;

void uploadSchemaHandler() {
  bool ok = (_uploadSlot >= 0 && _uploadHeaderParsed);
  httpServer.send(ok ? 200 : 500, "text/plain",
    ok ? "Banco " + String(_uploadSlot + 1) + " importado!" : "Error en la subida");
}

void uploadSchemaData() {
  HTTPUpload& up = httpServer.upload();

  if (up.status == UPLOAD_FILE_START) {
    if (!httpServer.hasArg("slot")) { _uploadSlot = -1; return; }
    _uploadSlot = httpServer.arg("slot").toInt();
    if (_uploadSlot < 0 || _uploadSlot >= MAX_SCHEMAS) { _uploadSlot = -1; return; }
    _uploadBinSize = 0;
    _uploadWritten = 0;
    _uploadHeaderParsed = false;
    _uploadBin  = SPIFFS.open(schemaBinPath(_uploadSlot), FILE_WRITE);
    _uploadJson = SPIFFS.open(schemaJsonPath(_uploadSlot), FILE_WRITE);
    if (!_uploadBin || !_uploadJson) { _uploadSlot = -1; return; }
    Serial.printf("[SCHEMA] Upload start slot %d\n", _uploadSlot);
  }
  else if (up.status == UPLOAD_FILE_WRITE && _uploadSlot >= 0) {
    uint8_t* data = up.buf;
    size_t len = up.currentSize;
    size_t offset = 0;

    // Parsear cabecera (4 bytes con binSize)
    if (!_uploadHeaderParsed) {
      if (len < 4) return;  // necesitamos al menos la cabecera
      _uploadBinSize = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
      _uploadHeaderParsed = true;
      offset = 4;
      len -= 4;
    }

    // Escribir datos al .bin hasta completar binSize
    if (_uploadWritten < _uploadBinSize) {
      uint32_t binRemaining = _uploadBinSize - _uploadWritten;
      uint32_t toWrite = (len < binRemaining) ? len : binRemaining;
      _uploadBin.write(data + offset, toWrite);
      _uploadWritten += toWrite;
      offset += toWrite;
      len -= toWrite;
    }

    // El resto va al .json
    if (len > 0) {
      _uploadJson.write(data + offset, len);
    }
  }
  else if (up.status == UPLOAD_FILE_END && _uploadSlot >= 0) {
    _uploadBin.close();
    _uploadJson.close();
    Serial.printf("[SCHEMA] Upload done slot %d: bin=%u bytes\n", _uploadSlot, _uploadBinSize);
  }
}

// ── POST /schema/load ────────────────────────────────────────
void loadSchema() {
  if (!httpServer.hasArg("slot")) {
    httpServer.send(400, "text/plain", "Missing slot");
    return;
  }
  int slot = httpServer.arg("slot").toInt();
  if (slot < 0 || slot >= MAX_SCHEMAS || !hasSchema(slot)) {
    httpServer.send(400, "text/plain", "Banco vacio o invalido");
    return;
  }

  // 1. Cargar Json de parámetros DSP
  File fJson = SPIFFS.open(schemaJsonPath(slot), FILE_READ);
  if (!fJson) {
    httpServer.send(500, "text/plain", "Error leyendo .json");
    return;
  }
  String j = fJson.readString();
  fJson.close();

  // Parsear el json a chollo en vivo
  auto getInt = [&](const String& key) -> int {
    int i = j.indexOf("\"" + key + "\":");
    if (i < 0) return -1;
    int end = j.indexOf(",", i);
    if (end < 0) end = j.indexOf("}", i);
    return j.substring(i + key.length() + 3, end).toInt();
  };

  for (int b = 0; b < EQ_NUM_BANDS; b++) {
    int val = getInt("a" + String(b));
    if (val >= 0) eqBands[b].baseAddr = val;
  }
  int v = getInt("bfa"); if (v >= 0) addrBassFreq = v;
  v = getInt("bba"); if (v >= 0) addrBassBoost = v;
  v = getInt("bca"); if (v >= 0) addrBassComp = v;
  v = getInt("ivbt"); if (v >= 0) addrInputVolBT = v;
  v = getInt("ivli"); if (v >= 0) addrInputVolLineIn = v;
  v = getInt("vul"); if (v >= 0) addrVuL = v;
  v = getInt("vur"); if (v >= 0) addrVuR = v;

  // Persistir inmediatamente las nuevas direcciones en el NVS
  saveEqAddrs(); 

  // 2. Cargar Binario a RAM
  File fBin = SPIFFS.open(schemaBinPath(slot), FILE_READ);
  if (!fBin) {
    httpServer.send(500, "text/plain", "Error leyendo .bin");
    return;
  }
  
  captureLen = 0;
  while (fBin.available() && captureLen < CAPTURE_MAX_SIZE) {
    captureBuffer[captureLen++] = fBin.read();
  }
  fBin.close();

  if (captureLen < 2) {
    captureLen = 0;
    httpServer.send(500, "text/plain", "Binario corto invalido");
    return;
  }

  // El binario guardado incluia el `0x00 0x00` final, que es lo que detectamos
  // Lo removemos del captureLen para que writeEEPROM()() no lo asome doble:
  captureLen -= 2;
  captureReady = true;

  bool toRam = (httpServer.hasArg("ram") && httpServer.arg("ram") == "1");

  if (toRam) {
    // ---- Escribir directo a la RAM del DSP vía I2C ----
    
    // 1. Parar el DSP core
    uint8_t stopCmd[] = {0x00, 0x00}; // core disable
    directWrite(dspI2cAddr, 0x081C, stopCmd, 2);
    delay(20);

    // 2. Transmitir bloques del selfboot buffer al DSP
    int offset = 0;
    while (offset < captureLen) {
      if (captureBuffer[offset] == 0x01) {
        uint16_t count = (captureBuffer[offset + 1] << 8) | captureBuffer[offset + 2];
        uint16_t addr = (captureBuffer[offset + 4] << 8) | captureBuffer[offset + 5];
        int dataLen = count - 3;
        uint8_t* payload = captureBuffer + offset + 6;
        
        directWrite(dspI2cAddr, addr, payload, dataLen);
        offset += count + 3;
      } else if (captureBuffer[offset] == 0x00 && (offset + 1 >= captureLen || captureBuffer[offset + 1] == 0x00)) {
        break;
      } else {
        offset++;
      }
    }

    // 3. Volver a arrancar el DSP core
    uint8_t runCmd[] = {lastCoreCtrl[0], lastCoreCtrl[1] | 0x04}; // core run
    directWrite(dspI2cAddr, 0x081C, runCmd, 2);
    delay(10);
    
    // Como las direcciones han cambiado, reaplicamos todo desde el ESP32
    if (eqEnabled) {
      for (int b = 0; b < EQ_NUM_BANDS; b++) writeEqBand(b);
      updateBassDSP();
      writeInputVol(addrInputVolBT, inputVolBT);
      writeInputVol(addrInputVolLineIn, inputVolLineIn);
      writeInputVol(addrInputVolSineTone, inputVolSineTone);
    }

    activeRamSource = slot;  // 0..3 = banco cargado a RAM
    saveActiveSources();
    httpServer.send(200, "text/plain", "Esquema " + String(slot + 1) + " cargado a RAM!");

  } else {
    // ---- Escribir a la EEPROM selfboot ----
    bool ok = writeEEPROM();
    prefs.begin("tcpi", false); prefs.putBool("eeprom_ok", ok); prefs.end();

    if (ok) {
      activeEepromSource = slot;  // banco grabado en EEPROM
      activeRamSource    = slot;  // tras resetDSP la RAM también viene de este banco
      saveActiveSources();
      httpServer.send(200, "text/plain", "Esquema " + String(slot + 1) + " grabado en EEPROM!");
      resetDSP(); // reinicia el DSP para que coja la eeprom
    } else {
      httpServer.send(500, "text/plain", "Fallo programando DSP");
    }
  }
}

// =============================================================
// backup_manager.ino — Backup y restauración completa
// =============================================================
//
// Descarga/sube un archivo .rcbak con TODO el estado persistente:
//   - Configuración NVS (WiFi, pines, DSP, EQ, bass, volúmenes...)
//   - Presets EQ (p0..p4.json en SPIFFS)
//   - Esquemas DSP (schema_0..3.bin/.json en SPIFFS)
//
// Formato binario .rcbak:
//   [4B] "RCBK"              magic
//   [4B] nvsLen (LE)         longitud del JSON de NVS
//   [nvsLen B] NVS JSON      configuración serializada
//   [1B] fileCount           número de archivos SPIFFS
//   Por cada archivo:
//     [1B] nameLen
//     [nameLen B] nombre     (ej. "/p0.json")
//     [4B] dataLen (LE)
//     [dataLen B] datos
// =============================================================

#include <Arduino.h>
#include <SPIFFS.h>

// ── Helpers ─────────────────────────────────────────────────────

static String jsonEsc(const String& s) {
  String r;
  r.reserve(s.length() + 8);
  for (unsigned int i = 0; i < s.length(); i++) {
    if (s[i] == '"')       r += "\\\"";
    else if (s[i] == '\\') r += "\\\\";
    else                   r += s[i];
  }
  return r;
}

static void writeLE32(WiFiClient& cl, uint32_t v) {
  uint8_t b[4];
  b[0] = v & 0xFF; b[1] = (v >> 8) & 0xFF;
  b[2] = (v >> 16) & 0xFF; b[3] = (v >> 24) & 0xFF;
  cl.write(b, 4);
}

static uint32_t readLE32(File& f) {
  uint8_t b[4];
  f.read(b, 4);
  return b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
}

// ── Construir JSON con toda la config NVS ───────────────────────

static String buildNvsJson() {
  String j = "{";
  // Strings
  j += "\"ssid\":\"" + jsonEsc(savedSSID) + "\",";
  j += "\"password\":\"" + jsonEsc(savedPassword) + "\",";
  j += "\"hostname\":\"" + jsonEsc(deviceHostname) + "\",";
  j += "\"ap_ssid\":\"" + jsonEsc(apSSID) + "\",";
  j += "\"ap_pass\":\"" + jsonEsc(apPassword) + "\",";
  j += "\"ota_pass\":\"" + jsonEsc(otaPassword) + "\",";
  // Uints
  j += "\"tcp_port\":" + String(tcpPort) + ",";
  j += "\"dsp_addr\":" + String(dspI2cAddr) + ",";
  j += "\"vu_win\":" + String(vuWindowMs) + ",";
  // Pins (int)
  j += "\"pin_scl\":" + String(pinSCL) + ",";
  j += "\"pin_sda\":" + String(pinSDA) + ",";
  j += "\"pin_reset\":" + String(pinRESET) + ",";
  j += "\"pin_selfboot\":" + String(pinSELFBOOT) + ",";
  j += "\"pin_led\":" + String(pinLED) + ",";
  // Bools
  j += "\"eq_boot\":" + String(eqBootEnabled ? "true" : "false") + ",";
  j += "\"dsp_lock\":" + String(dspLocked ? "true" : "false") + ",";
  // Active sources
  j += "\"act_ram\":" + String(activeRamSource) + ",";
  j += "\"act_eeprom\":" + String(activeEepromSource) + ",";
  // EQ bands
  for (int b = 0; b < EQ_NUM_BANDS; b++) {
    j += "\"eq" + String(b) + "_f\":" + String(eqBands[b].freq, 2) + ",";
    j += "\"eq" + String(b) + "_g\":" + String(eqBands[b].gainDb, 2) + ",";
    j += "\"eq" + String(b) + "_q\":" + String(eqBands[b].q, 2) + ",";
    j += "\"eq" + String(b) + "_a\":" + String(eqBands[b].baseAddr) + ",";
  }
  // EQ XY state
  j += "\"eq_nx\":" + String(eqLastNX, 4) + ",";
  j += "\"eq_ny\":" + String(eqLastNY, 4) + ",";
  j += "\"eq_slot\":" + String(eqActiveSlot) + ",";
  // Bass
  j += "\"bass_f\":" + String(bassFreq, 2) + ",";
  j += "\"bass_b\":" + String(bassBoost, 2) + ",";
  j += "\"bass_cr\":" + String(bassCompRatio, 2) + ",";
  j += "\"bass_fa\":" + String(addrBassFreq) + ",";
  j += "\"bass_ba\":" + String(addrBassBoost) + ",";
  j += "\"bass_cra\":" + String(addrBassComp) + ",";
  // Input volumes
  j += "\"invol_bt\":" + String(inputVolBT, 2) + ",";
  j += "\"invol_li\":" + String(inputVolLineIn, 2) + ",";
  j += "\"invol_st\":" + String(inputVolSineTone, 2) + ",";
  j += "\"invol_bta\":" + String(addrInputVolBT) + ",";
  j += "\"invol_lia\":" + String(addrInputVolLineIn) + ",";
  j += "\"invol_sta\":" + String(addrInputVolSineTone) + ",";
  // VU
  j += "\"vu_l_a\":" + String(addrVuL) + ",";
  j += "\"vu_r_a\":" + String(addrVuR) + ",";
  // Sine Tone
  j += "\"st_lm\":" + String(addrSineLMask) + ",";
  j += "\"st_li\":" + String(addrSineLFreq) + ",";
  j += "\"st_lo\":" + String(addrSineLIson) + ",";
  j += "\"st_rm\":" + String(addrSineRMask) + ",";
  j += "\"st_ri\":" + String(addrSineRFreq) + ",";
  j += "\"st_ro\":" + String(addrSineRIson);
  j += "}";
  return j;
}

// ── GET /backup — descargar archivo .rcbak ─────────────────────

void sendBackup() {
  String nvs = buildNvsJson();
  uint32_t nvsLen = nvs.length();

  // Enumerar archivos SPIFFS a incluir
  const char* candidates[] = {
    "/p0.json", "/p1.json", "/p2.json", "/p3.json", "/p4.json",
    "/schema_0.bin", "/schema_0.json",
    "/schema_1.bin", "/schema_1.json",
    "/schema_2.bin", "/schema_2.json",
    "/schema_3.bin", "/schema_3.json"
  };
  const int NUM_CANDIDATES = 13;

  String fNames[13];
  uint32_t fSizes[13];
  int fileCount = 0;

  uint32_t totalSize = 4 + 4 + nvsLen + 1;  // magic + nvsLen + nvs + fileCount byte

  for (int i = 0; i < NUM_CANDIDATES; i++) {
    if (SPIFFS.exists(candidates[i])) {
      File f = SPIFFS.open(candidates[i], FILE_READ);
      if (f) {
        fNames[fileCount] = candidates[i];
        fSizes[fileCount] = f.size();
        totalSize += 1 + strlen(candidates[i]) + 4 + f.size();
        fileCount++;
        f.close();
      }
    }
  }

  httpServer.sendHeader("Content-Disposition", "attachment; filename=\"radiocassete_backup.rcbak\"");
  httpServer.setContentLength(totalSize);
  httpServer.send(200, "application/octet-stream", "");

  WiFiClient cl = httpServer.client();

  // Magic
  cl.write((uint8_t*)"RCBK", 4);

  // NVS JSON
  writeLE32(cl, nvsLen);
  cl.print(nvs);

  // File count
  cl.write((uint8_t)fileCount);

  // Files
  uint8_t buf[256];
  for (int i = 0; i < fileCount; i++) {
    uint8_t nameLen = fNames[i].length();
    cl.write(nameLen);
    cl.print(fNames[i]);
    writeLE32(cl, fSizes[i]);

    File f = SPIFFS.open(fNames[i], FILE_READ);
    while (f.available()) {
      int n = f.read(buf, sizeof(buf));
      cl.write(buf, n);
    }
    f.close();
  }

  Serial.printf("[BACKUP] Descargado: NVS %u B + %d archivos SPIFFS\n", nvsLen, fileCount);
}

// ── POST /restore — subir archivo .rcbak ────────────────────────

static File _restoreTmp;
static bool _restoreUploadOk = false;

// Restaurar NVS desde JSON
static void restoreNvs(const String& j) {
  // Parseo manual — mismo estilo que schema_manager.ino

  auto getStr = [&](const char* key) -> String {
    String needle = String("\"") + key + "\":\"";
    int i = j.indexOf(needle);
    if (i < 0) return String();
    int start = i + needle.length();
    String result;
    for (int p = start; p < (int)j.length(); p++) {
      if (j[p] == '\\' && p + 1 < (int)j.length()) {
        result += j[p + 1]; p++;
      } else if (j[p] == '"') {
        break;
      } else {
        result += j[p];
      }
    }
    return result;
  };

  auto getNum = [&](const char* key, float defVal) -> float {
    String needle = String("\"") + key + "\":";
    int i = j.indexOf(needle);
    if (i < 0) return defVal;
    int start = i + needle.length();
    int end = start;
    while (end < (int)j.length() && (j[end] == '-' || j[end] == '.' || (j[end] >= '0' && j[end] <= '9')))
      end++;
    return j.substring(start, end).toFloat();
  };

  auto getBool = [&](const char* key) -> bool {
    String needle = String("\"") + key + "\":";
    int i = j.indexOf(needle);
    if (i < 0) return false;
    return j.substring(i + needle.length(), i + needle.length() + 4) == "true";
  };

  auto hasKey = [&](const char* key) -> bool {
    return j.indexOf(String("\"") + key + "\":") >= 0;
  };

  prefs.begin("tcpi", false);

  // Strings
  String s;
  s = getStr("ssid");     if (s.length()) prefs.putString("ssid", s);
  s = getStr("password"); if (s.length()) prefs.putString("password", s);
  s = getStr("hostname"); if (s.length()) prefs.putString("hostname", s);
  s = getStr("ap_ssid");  if (s.length()) prefs.putString("ap_ssid", s);
  s = getStr("ap_pass");  if (s.length()) prefs.putString("ap_pass", s);
  if (hasKey("ota_pass"))  prefs.putString("ota_pass", getStr("ota_pass"));

  // Network
  if (hasKey("tcp_port"))  prefs.putUInt("tcp_port",  (uint32_t)getNum("tcp_port", 8086));
  if (hasKey("dsp_addr"))  prefs.putUChar("dsp_addr", (uint8_t)getNum("dsp_addr", 0x34));
  if (hasKey("vu_win"))    prefs.putUInt("vu_win",    (uint32_t)getNum("vu_win", 250));

  // Pins
  if (hasKey("pin_scl"))      prefs.putInt("pin_scl",      (int)getNum("pin_scl", 17));
  if (hasKey("pin_sda"))      prefs.putInt("pin_sda",      (int)getNum("pin_sda", 16));
  if (hasKey("pin_reset"))    prefs.putInt("pin_reset",    (int)getNum("pin_reset", 21));
  if (hasKey("pin_selfboot")) prefs.putInt("pin_selfboot", (int)getNum("pin_selfboot", 19));
  if (hasKey("pin_led"))      prefs.putInt("pin_led",      (int)getNum("pin_led", 2));

  // Bools
  if (hasKey("eq_boot"))  prefs.putBool("eq_boot",  getBool("eq_boot"));
  if (hasKey("dsp_lock")) prefs.putBool("dsp_lock", getBool("dsp_lock"));

  // Active sources
  if (hasKey("act_ram"))    prefs.putInt("act_ram",    (int)getNum("act_ram", -1));
  if (hasKey("act_eeprom")) prefs.putInt("act_eeprom", (int)getNum("act_eeprom", -1));

  // EQ bands
  for (int b = 0; b < EQ_NUM_BANDS; b++) {
    char kf[12], kg[12], kq[12], ka[12];
    snprintf(kf, sizeof(kf), "eq%d_f", b);
    snprintf(kg, sizeof(kg), "eq%d_g", b);
    snprintf(kq, sizeof(kq), "eq%d_q", b);
    snprintf(ka, sizeof(ka), "eq%d_a", b);
    if (hasKey(kf)) prefs.putFloat(kf, getNum(kf, 0));
    if (hasKey(kg)) prefs.putFloat(kg, getNum(kg, 0));
    if (hasKey(kq)) prefs.putFloat(kq, getNum(kq, 1));
    if (hasKey(ka)) prefs.putUInt(ka, (uint32_t)getNum(ka, 0));
  }

  // EQ XY
  if (hasKey("eq_nx"))   prefs.putFloat("eq_nx", getNum("eq_nx", 0));
  if (hasKey("eq_ny"))   prefs.putFloat("eq_ny", getNum("eq_ny", 0));
  if (hasKey("eq_slot")) prefs.putInt("eq_slot", (int)getNum("eq_slot", -1));

  // Bass
  if (hasKey("bass_f"))   prefs.putFloat("bass_f",  getNum("bass_f", 40));
  if (hasKey("bass_b"))   prefs.putFloat("bass_b",  getNum("bass_b", 9));
  if (hasKey("bass_cr"))  prefs.putFloat("bass_cr", getNum("bass_cr", 10));
  if (hasKey("bass_fa"))  prefs.putUInt("bass_fa",  (uint32_t)getNum("bass_fa", 0));
  if (hasKey("bass_ba"))  prefs.putUInt("bass_ba",  (uint32_t)getNum("bass_ba", 0));
  if (hasKey("bass_cra")) prefs.putUInt("bass_cra", (uint32_t)getNum("bass_cra", 0));

  // Input volumes
  if (hasKey("invol_bt"))  prefs.putFloat("invol_bt", getNum("invol_bt", 0));
  if (hasKey("invol_li"))  prefs.putFloat("invol_li", getNum("invol_li", 0));
  if (hasKey("invol_st"))  prefs.putFloat("invol_st", getNum("invol_st", 0));
  if (hasKey("invol_bta")) prefs.putUInt("invol_bta", (uint32_t)getNum("invol_bta", 0));
  if (hasKey("invol_lia")) prefs.putUInt("invol_lia", (uint32_t)getNum("invol_lia", 0));
  if (hasKey("invol_sta")) prefs.putUInt("invol_sta", (uint32_t)getNum("invol_sta", 0));

  // VU
  if (hasKey("vu_l_a")) prefs.putUInt("vu_l_a", (uint32_t)getNum("vu_l_a", 0));
  if (hasKey("vu_r_a")) prefs.putUInt("vu_r_a", (uint32_t)getNum("vu_r_a", 0));

  // Sine Tone
  if (hasKey("st_lm")) prefs.putUInt("st_lm", (uint32_t)getNum("st_lm", 0));
  if (hasKey("st_li")) prefs.putUInt("st_li", (uint32_t)getNum("st_li", 0));
  if (hasKey("st_lo")) prefs.putUInt("st_lo", (uint32_t)getNum("st_lo", 0));
  if (hasKey("st_rm")) prefs.putUInt("st_rm", (uint32_t)getNum("st_rm", 0));
  if (hasKey("st_ri")) prefs.putUInt("st_ri", (uint32_t)getNum("st_ri", 0));
  if (hasKey("st_ro")) prefs.putUInt("st_ro", (uint32_t)getNum("st_ro", 0));

  prefs.end();
  Serial.println("[RESTORE] NVS restaurado");
}

// Procesar el archivo temporal de restore
static bool processRestore() {
  File f = SPIFFS.open("/restore.tmp", FILE_READ);
  if (!f) { Serial.println("[RESTORE] No se pudo abrir /restore.tmp"); return false; }

  // Verificar magic
  uint8_t magic[4];
  if (f.read(magic, 4) != 4 || memcmp(magic, "RCBK", 4) != 0) {
    Serial.println("[RESTORE] Magic incorrecto");
    f.close(); return false;
  }

  // Leer NVS JSON
  uint32_t nvsLen = readLE32(f);
  if (nvsLen > 8192) {
    Serial.printf("[RESTORE] NVS JSON demasiado grande: %u\n", nvsLen);
    f.close(); return false;
  }

  char* nvsBuf = (char*)malloc(nvsLen + 1);
  if (!nvsBuf) {
    Serial.println("[RESTORE] Sin memoria para NVS JSON");
    f.close(); return false;
  }
  f.read((uint8_t*)nvsBuf, nvsLen);
  nvsBuf[nvsLen] = 0;
  String nvsJson = String(nvsBuf);
  free(nvsBuf);

  // Restaurar NVS
  restoreNvs(nvsJson);

  // Leer y restaurar archivos SPIFFS
  uint8_t fileCount = 0;
  f.read(&fileCount, 1);
  Serial.printf("[RESTORE] %d archivos SPIFFS\n", fileCount);

  uint8_t buf[256];
  for (int i = 0; i < fileCount; i++) {
    // Nombre
    uint8_t nameLen = 0;
    f.read(&nameLen, 1);
    char name[64];
    if (nameLen >= sizeof(name)) nameLen = sizeof(name) - 1;
    f.read((uint8_t*)name, nameLen);
    name[nameLen] = 0;

    // Tamaño
    uint32_t dataLen = readLE32(f);
    Serial.printf("[RESTORE]   %s (%u bytes)\n", name, dataLen);

    // Escribir archivo
    File out = SPIFFS.open(name, FILE_WRITE);
    uint32_t remaining = dataLen;
    while (remaining > 0) {
      uint32_t toRead = remaining < sizeof(buf) ? remaining : sizeof(buf);
      int got = f.read(buf, toRead);
      if (got <= 0) break;
      if (out) out.write(buf, got);
      remaining -= got;
    }
    if (out) out.close();
  }

  f.close();
  SPIFFS.remove("/restore.tmp");
  Serial.println("[RESTORE] Completado!");
  return true;
}

// Handler de respuesta HTTP (se ejecuta tras completar el upload)
void restoreHandler() {
  if (!_restoreUploadOk) {
    httpServer.send(500, "text/plain", "Error en la subida del backup");
    return;
  }

  bool ok = processRestore();
  if (ok) {
    // Forzar DSP Lock ON tras restore para que el ESP no escriba
    // al DSP con direcciones que pueden no coincidir con el programa
    // actualmente cargado en la EEPROM/RAM del ADAU1701.
    prefs.begin("tcpi", false);
    prefs.putBool("dsp_lock", true);
    prefs.end();
    Serial.println("[RESTORE] DSP Lock forzado ON (seguridad post-restore)");

    httpServer.send(200, "text/plain", "Backup restaurado! DSP Lock ON. Reiniciando...");
    delay(1000);
    ESP.restart();
  } else {
    httpServer.send(500, "text/plain", "Error procesando backup");
  }
}

// Handler de datos del upload (se ejecuta durante la subida)
void restoreUploadData() {
  HTTPUpload& up = httpServer.upload();

  if (up.status == UPLOAD_FILE_START) {
    _restoreUploadOk = false;
    _restoreTmp = SPIFFS.open("/restore.tmp", FILE_WRITE);
    if (!_restoreTmp) {
      Serial.println("[RESTORE] Error creando /restore.tmp");
      return;
    }
    Serial.printf("[RESTORE] Upload start: %s\n", up.filename.c_str());
  }
  else if (up.status == UPLOAD_FILE_WRITE) {
    if (_restoreTmp) {
      _restoreTmp.write(up.buf, up.currentSize);
    }
  }
  else if (up.status == UPLOAD_FILE_END) {
    if (_restoreTmp) {
      _restoreTmp.close();
      _restoreUploadOk = true;
      Serial.printf("[RESTORE] Upload done: %u bytes\n", up.totalSize);
    }
  }
}

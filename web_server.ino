// =============================================================
// web_server.ino -- Servidor HTTP: sistema, SSE, OTA HTTP
// =============================================================
//
// Estructura del modulo web:
//   web_html.h            -- HTML/CSS/JS embebido en PROGMEM
//   web_routes_eq.ino     -- Rutas /eq/*, /vu, /input/vol
//   web_routes_config.ino -- Rutas /config/*, /save_*, /factory_reset
//   web_server.ino        -- SSE, estado del sistema, OTA HTTP
//
// Rutas registradas en este archivo:
//   /            GET        -- sirve la SPA (INDEX_HTML)
//   /events      GET        -- SSE stream (estado en tiempo real)
//   /status      GET        -- snapshot JSON del estado del sistema
//   /save_eeprom POST       -- escribe program RAM en EEPROM selfboot
//   /reset_dsp   POST       -- reset + recarga del ADAU1701
//   /reboot_esp  POST       -- reinicia el ESP32
//   /toggle_log  POST       -- activa/desactiva log serie
//   /toggle_eq_boot POST    -- activa/desactiva carga EQ al arrancar
//   /toggle_dsp_lock POST   -- activa/desactiva DSP lock
//   /log         GET        -- buffer de log en JSON
//   /update      POST       -- OTA HTTP (subir .bin)
//
// =============================================================

#include "web_html.h"

// ── JSON helpers ──────────────────────────────────────────────

String eqStateJSON() {
  String j = "{\"enabled\":";
  j += eqEnabled ? "true" : "false";
  j += ",\"nx\":"     + String(eqLastNX, 4);
  j += ",\"ny\":"     + String(eqLastNY, 4);
  j += ",\"active\":" + String(eqActiveSlot);
  j += ",\"slots\":[";
  for (int i = 0; i < EQ_MEM_SLOTS; i++) {
    if (i) j += ",";
    j += memoryHasData(i) ? "true" : "false";
  }
  j += "],\"bands\":[";
  for (int b = 0; b < EQ_NUM_BANDS; b++) {
    if (b) j += ",";
    j += "{\"freq\":"  + String(eqBands[b].freq,    1);
    j += ",\"gain\":"  + String(eqBands[b].gainDb,  2);
    j += ",\"q\":"     + String(eqBands[b].q,        2);
    j += ",\"addr\":"  + String(eqBands[b].baseAddr) + "}";
  }
  j += "]";
  j += ",\"bassFreq\":"           + String(bassFreq, 1);
  j += ",\"bassBoost\":"          + String(bassBoost, 2);
  j += ",\"bassCompRatio\":"      + String(bassCompRatio, 2);
  j += ",\"addrBassFreq\":"       + String(addrBassFreq);
  j += ",\"addrBassBoost\":"      + String(addrBassBoost);
  j += ",\"addrBassComp\":"       + String(addrBassComp);
  j += ",\"inputVolBT\":"         + String(inputVolBT, 1);
  j += ",\"inputVolLineIn\":"     + String(inputVolLineIn, 1);
  j += ",\"inputVolSineTone\":"   + String(inputVolSineTone, 1);
  j += ",\"addrInputVolBT\":"     + String(addrInputVolBT);
  j += ",\"addrInputVolLineIn\":" + String(addrInputVolLineIn);
  j += ",\"addrInputVolSineTone\":" + String(addrInputVolSineTone);
  j += ",\"addrVuL\":"            + String(addrVuL);
  j += ",\"addrVuR\":"            + String(addrVuR);
  j += ",\"addrSineLMask\":"      + String(addrSineLMask);
  j += ",\"addrSineLFreq\":"      + String(addrSineLFreq);
  j += ",\"addrSineLIson\":"      + String(addrSineLIson);
  j += ",\"addrSineRMask\":"      + String(addrSineRMask);
  j += ",\"addrSineRFreq\":"      + String(addrSineRFreq);
  j += ",\"addrSineRIson\":"      + String(addrSineRIson);
  j += "}";
  return j;
}

// ── SSE (Server-Sent Events) ──────────────────────────────────

WiFiClient sseClient;

void ssePush(bool full) {
  if (!sseClient || !sseClient.connected()) return;
  if (!full) {
    String j = "data:{\"vuL\":" + String(vuLevelL, 4) + ",\"vuR\":" + String(vuLevelR, 4) + "}\n\n";
    sseClient.print(j);
    return;
  }
  String ip = apMode ? WiFi.softAPIP().toString() : WiFi.localIP().toString();
  String j  = "data:{\"dspRunning\":"    + String(dspRunning    ? "true" : "false");
  j += ",\"tcpConnected\":"              + String((client && client.connected()) ? "true" : "false");
  j += ",\"captureReady\":"             + String(captureReady  ? "true" : "false");
  j += ",\"captureLen\":"               + String(captureLen);
  j += ",\"eqEnabled\":"                + String(eqEnabled     ? "true" : "false");
  j += ",\"eqBootEnabled\":"            + String(eqBootEnabled ? "true" : "false");
  j += ",\"logEnabled\":"               + String(logEnabled    ? "true" : "false");
  j += ",\"dspLocked\":"                + String(dspLocked     ? "true" : "false");
  j += ",\"dspMuted\":"                 + String(dspMuted      ? "true" : "false");
  j += ",\"lineMuted\":"               + String(lineMuted     ? "true" : "false");
  j += ",\"ip\":\""                     + ip + "\"";
  j += ",\"ssid\":\""                   + savedSSID + "\"";
  j += ",\"hostname\":\""               + deviceHostname + ".local\"";
  j += ",\"vuL\":"                      + String(vuLevelL, 4);
  j += ",\"vuR\":"                      + String(vuLevelR, 4);
  j += ",\"activeRam\":"                + String(activeRamSource);
  j += ",\"activeEeprom\":"             + String(activeEepromSource);
  j += ",\"sleepPending\":"             + String(sleepPending   ? "true" : "false");
  j += ",\"sleepCountdown\":"           + String(sleepCountdown) + "}";
  j += "\n\n";
  sseClient.print(j);
}

// ── HTTP setup ────────────────────────────────────────────────

void setupHTTP() {

  // ── Pagina principal (SPA) ──────────────────────────────────
  httpServer.on("/",[]() {
    httpServer.send_P(200, "text/html", INDEX_HTML);
  });

  // ── SSE stream ─────────────────────────────────────────────
  httpServer.on("/events", []() {
    sseClient = httpServer.client();
    sseClient.println("HTTP/1.1 200 OK");
    sseClient.println("Content-Type: text/event-stream");
    sseClient.println("Cache-Control: no-cache");
    sseClient.println("Connection: keep-alive");
    sseClient.println("Access-Control-Allow-Origin: *");
    sseClient.println();
    sseClient.flush();
    ssePush(true);  // estado inmediato al conectar
  });

  // ── Estado del sistema ─────────────────────────────────────
  httpServer.on("/status",[]() {
    String ip = apMode ? WiFi.softAPIP().toString() : WiFi.localIP().toString();
    String j  = "{\"dspRunning\":"   + String(dspRunning    ? "true" : "false");
    j += ",\"eqEnabled\":"           + String(eqEnabled     ? "true" : "false");
    j += ",\"eqBootEnabled\":"       + String(eqBootEnabled ? "true" : "false");
    j += ",\"logEnabled\":"          + String(logEnabled    ? "true" : "false");
    j += ",\"dspLocked\":"           + String(dspLocked     ? "true" : "false");
    j += ",\"dspMuted\":"            + String(dspMuted      ? "true" : "false");
    j += ",\"lineMuted\":"          + String(lineMuted     ? "true" : "false");
    j += ",\"apMode\":"              + String(apMode        ? "true" : "false");
    j += ",\"captureReady\":"        + String(captureReady  ? "true" : "false");
    j += ",\"captureLen\":"          + String(captureLen);
    j += ",\"tcpConnected\":"        + String((client && client.connected()) ? "true" : "false");
    j += ",\"ip\":\""                + ip + "\"";
    j += ",\"ssid\":\""              + savedSSID + "\"";
    j += ",\"hostname\":\""          + deviceHostname + "\"";
    j += ",\"apSSID\":\""            + apSSID + "\"";
    j += ",\"tcpPort\":"             + String(tcpPort);
    j += ",\"dspI2cAddr\":"          + String(dspI2cAddr);
    j += ",\"vuWindowMs\":"          + String(vuWindowMs);
    j += ",\"activeRam\":"          + String(activeRamSource);
    j += ",\"activeEeprom\":"       + String(activeEepromSource);
    j += ",\"fwVersion\":\"" + String(FW_VERSION) + "\"";
    j += ",\"fwDate\":\"" + String(FW_DATE) + "\"" + "}";
    httpServer.send(200, "application/json", j);
  });

  // ── Control del DSP ────────────────────────────────────────
  httpServer.on("/save_eeprom", HTTP_POST,[]() {
    if (!captureReady) { httpServer.send(400, "text/plain", "No capture"); return; }
    bool ok = writeEEPROM();
    prefs.begin("tcpi", false); prefs.putBool("eeprom_ok", ok); prefs.end();
    httpServer.send(200, "text/plain", ok ? "OK" : "ERROR");
  });

  // ── Leer EEPROM directamente por I2C (backup) ────────────
  httpServer.on("/read_eeprom", HTTP_POST,[]() {
    bool ok = readEEPROM();
    if (ok) {
      httpServer.send(200, "text/plain", "EEPROM leida: " + String(captureLen) + " bytes");
      ssePush(true);
    } else {
      httpServer.send(500, "text/plain", "Error leyendo EEPROM por I2C");
    }
  });

  httpServer.on("/reset_dsp", HTTP_POST,[]() {
    httpServer.send(200, "text/plain", "Reset OK");
    extern bool pendingDspReset;
    pendingDspReset = true;
  });

  httpServer.on("/reboot_esp", HTTP_POST,[]() {
    httpServer.send(200, "text/plain", "Rebooting");
    delay(1000);
    ESP.restart();
  });

  // ── Toggles de sistema ─────────────────────────────────────
  httpServer.on("/toggle_log", HTTP_POST,[]() {
    logEnabled = !logEnabled;
    Serial.printf("[LOG] -> %s\n", logEnabled ? "ON" : "OFF");
    httpServer.send(200, "text/plain", logEnabled ? "Log ON" : "Log OFF");
  });

  httpServer.on("/toggle_eq_boot", HTTP_POST,[]() {
    eqBootEnabled = !eqBootEnabled;
    saveEqBootEnabled();
    Serial.printf("[EQ] Boot load -> %s\n", eqBootEnabled ? "ON" : "OFF");
    httpServer.send(200, "text/plain", eqBootEnabled ? "EQ Boot ON" : "EQ Boot OFF");
  });

  httpServer.on("/toggle_dsp_lock", HTTP_POST,[]() {
    dspLocked = !dspLocked;
    saveDspLock();
    Serial.printf("[DSP] Lock -> %s\n", dspLocked ? "ON" : "OFF");
    httpServer.send(200, "text/plain", dspLocked ? "DSP Lock ON" : "DSP Lock OFF");
  });

  // ── Mute DAC ──────────────────────────────────────────────
  httpServer.on("/toggle_mute", HTTP_POST,[]() {
    extern void directWrite(uint8_t i2cAddr, uint16_t regAddr, uint8_t* data, uint16_t dataLen);
    dspMuted = !dspMuted;
    if (dspMuted) {
      lastCoreCtrl[1] &= ~0x08;          // clear bit 3 → DAC mute
    } else {
      lastCoreCtrl[1] |= 0x08;           // set bit 3 → DAC unmute
    }
    uint8_t cmd[2] = {lastCoreCtrl[0], (uint8_t)(lastCoreCtrl[1] | 0x04)};
    directWrite(dspI2cAddr, 0x081C, cmd, 2);
    Serial.printf("[MUTE] DAC -> %s\n", dspMuted ? "MUTED" : "UNMUTED");
    ssePush(true);
    httpServer.send(200, "text/plain", dspMuted ? "MUTED" : "UNMUTED");
  });

  // ── Mute Line In (ADC) ──────────────────────────────────────
  httpServer.on("/toggle_line_mute", HTTP_POST,[]() {
    extern void directWrite(uint8_t i2cAddr, uint16_t regAddr, uint8_t* data, uint16_t dataLen);
    lineMuted = !lineMuted;
    if (lineMuted) {
      lastCoreCtrl[1] &= ~0x10;          // clear bit 4 → ADC mute
    } else {
      lastCoreCtrl[1] |= 0x10;           // set bit 4 → ADC unmute
    }
    uint8_t cmd[2] = {lastCoreCtrl[0], (uint8_t)(lastCoreCtrl[1] | 0x04)};
    directWrite(dspI2cAddr, 0x081C, cmd, 2);
    Serial.printf("[MUTE] Line In -> %s\n", lineMuted ? "MUTED" : "UNMUTED");
    ssePush(true);
    httpServer.send(200, "text/plain", lineMuted ? "MUTED" : "UNMUTED");
  });

  // ── Log serie ──────────────────────────────────────────────
  httpServer.on("/log",[]() {
    String j = "[";
    int count = logBufCount;
    int start = (logBufHead - count + LOG_BUF_LINES) % LOG_BUF_LINES;
    for (int i = 0; i < count; i++) {
      int idx = (start + i) % LOG_BUF_LINES;
      if (i > 0) j += ",";
      j += "\"";
      for (const char* p = logBuf[idx]; *p; p++) {
        if      (*p == '"')  j += "\\\"";
        else if (*p == '\\') j += "\\\\";
        else                 j += *p;
      }
      j += "\"";
    }
    j += "]";
    httpServer.send(200, "application/json", j);
  });

  // ── OTA HTTP (subir .bin desde navegador) ──────────────────
  httpServer.on("/update", HTTP_POST,[]() {
    bool ok = !Update.hasError();
    httpServer.sendHeader("Connection", "close");
    httpServer.send(ok ? 200 : 500, "text/plain", ok ? "OK" : Update.errorString());
    delay(500);
    if (ok) ESP.restart();
  },[]() {
    HTTPUpload& upload = httpServer.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("[OTA-HTTP] Start: %s (%u bytes)\n",
        upload.filename.c_str(), upload.totalSize);
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
        Serial.printf("[OTA-HTTP] begin error: %s\n", Update.errorString());
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Serial.printf("[OTA-HTTP] write error: %s\n", Update.errorString());
      }
      Serial.printf("[OTA-HTTP] %u bytes\r", upload.totalSize);
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) {
        Serial.printf("\n[OTA-HTTP] OK: %u bytes\n", upload.totalSize);
      } else {
        Serial.printf("\n[OTA-HTTP] end error: %s\n", Update.errorString());
      }
    }
  });

  // ── Sine Tone (Autosoner sweep) ────────────────────────────
  //   GET /tone?on=1&freq=1000  → activa tono a 1 kHz
  //   GET /tone?on=0            → desactiva tono
  //   GET /tone?freq=440        → cambia frecuencia (sin tocar on/off)
  httpServer.on("/tone", HTTP_GET, []() {
    if (httpServer.hasArg("on")) {
      bool on = httpServer.arg("on").toInt() != 0;
      setSineToneEnable(on);
      if (!on) {
        httpServer.send(200, "application/json", "{\"ok\":true,\"tone\":\"off\"}");
        return;
      }
    }
    if (httpServer.hasArg("freq")) {
      float freq = httpServer.arg("freq").toFloat();
      setSineToneFreq(freq);
      LOG("[TONE] %.1f Hz\n", freq);
    }
    httpServer.send(200, "application/json", "{\"ok\":true}");
  });

  // ── Modulos de rutas adicionales ───────────────────────────
  registerEqRoutes();      // web_routes_eq.ino
  registerConfigRoutes();  // web_routes_config.ino

  httpServer.on("/schema/list",     HTTP_GET,  sendSchemaList);
  httpServer.on("/schema/save",     HTTP_POST, saveSchema);
  httpServer.on("/schema/load",     HTTP_POST, loadSchema);
  httpServer.on("/schema/download", HTTP_GET,  downloadSchema);
  httpServer.on("/schema/upload",   HTTP_POST, uploadSchemaHandler, uploadSchemaData);

  httpServer.on("/backup",          HTTP_GET,  sendBackup);
  httpServer.on("/restore",         HTTP_POST, restoreHandler, restoreUploadData);

  httpServer.enableCORS(true); // Permitir peticiones cross-origin (CORS) desde el nuevo "sender"
  httpServer.begin();
}

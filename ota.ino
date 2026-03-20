// =============================================================
// ota.ino — OTA firmware update
//
// ArduinoOTA : upload desde Arduino IDE por WiFi (puerto 3232)
//              Tools → Port → adau1701-tcpi.local
//
// HTTP OTA   : endpoint POST /update — sube .bin desde la web
//              Compilar en Arduino IDE:
//              Sketch → Export Compiled Binary → sube el .bin
// =============================================================

void setupOTA() {
  // ── ArduinoOTA ────────────────────────────────────────────
  ArduinoOTA.setHostname(deviceHostname.c_str());
  if (otaPassword.length() > 0)
    ArduinoOTA.setPassword(otaPassword.c_str());

  ArduinoOTA.onStart([]() {
    String type = (ArduinoOTA.getCommand() == U_FLASH) ? "firmware" : "filesystem";
    Serial.println("[OTA] Start: " + type);
    // Detener TCP y Telnet durante el update para liberar recursos
    if (client && client.connected()) client.stop();
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\n[OTA] End — reiniciando...");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("[OTA] %u%%\r", progress * 100 / total);
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("[OTA] Error[%u]: ", error);
    switch (error) {
      case OTA_AUTH_ERROR:    Serial.println("Auth Failed");    break;
      case OTA_BEGIN_ERROR:   Serial.println("Begin Failed");   break;
      case OTA_CONNECT_ERROR: Serial.println("Connect Failed"); break;
      case OTA_RECEIVE_ERROR: Serial.println("Receive Failed"); break;
      case OTA_END_ERROR:     Serial.println("End Failed");     break;
    }
  });

  ArduinoOTA.begin();
  Serial.printf("[OTA] ArduinoOTA listo  hostname:%s  pass:%s\n",
    deviceHostname.c_str(), otaPassword.length() > 0 ? otaPassword.c_str() : "(none)");
}

// ── HTTP OTA — registrado en setupHTTP() de web_server.ino ───
// El endpoint /update y /update/progress están ahí para
// mantener toda la lógica HTTP en un solo archivo.

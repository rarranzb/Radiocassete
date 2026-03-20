// =============================================================
// web_routes_config.ino -- Rutas HTTP: Configuracion persistente
// =============================================================
//
// Registra los endpoints de configuracion del dispositivo:
//   /config/pins     GET   -- pines GPIO actuales en JSON
//   /save_wifi       POST  -- guarda SSID/Password y reinicia
//   /save_network    POST  -- guarda hostname/AP/OTA/TCP port y reinicia
//   /save_pins       POST  -- guarda asignacion de pines y reinicia
//   /save_eq_addrs   POST  -- guarda direcciones param RAM + DSP addr + VU window
//   /factory_reset   POST  -- borra NVS y reinicia en AP mode
//
// =============================================================

void registerConfigRoutes() {

  // GET /config/pins -- devuelve los pines GPIO configurados
  httpServer.on("/config/pins",[]() {
    String j = "{\"scl\":" + String(pinSCL);
    j += ",\"sda\":"  + String(pinSDA);
    j += ",\"rst\":"  + String(pinRESET);
    j += ",\"sb\":"   + String(pinSELFBOOT);
    j += ",\"led\":"  + String(pinLED) + "}";
    httpServer.send(200, "application/json", j);
  });

  // POST /save_wifi -- actualiza credenciales WiFi STA y reinicia
  httpServer.on("/save_wifi", HTTP_POST,[]() {
    if (!httpServer.hasArg("ssid") || httpServer.arg("ssid").isEmpty()) {
      httpServer.send(400, "text/plain", "Missing SSID"); return;
    }
    String newSSID = httpServer.arg("ssid");
    String newPass = httpServer.arg("pass");
    if (newPass.isEmpty()) newPass = savedPassword;
    saveWiFi(newSSID, newPass);
    WiFi.mode(WIFI_AP_STA); WiFi.setHostname(deviceHostname.c_str());
    WiFi.begin(newSSID.c_str(), newPass.c_str());
    int tries = 0;
    while (WiFi.status() != WL_CONNECTED && tries++ < 20) delay(500);
    httpServer.send(200, "text/plain",
      WiFi.status() == WL_CONNECTED ? "OK:" + WiFi.localIP().toString() : "FAIL");
    delay(1500); ESP.restart();
  });

  // POST /save_network -- guarda hostname, AP SSID/pass, OTA pass, TCP port
  httpServer.on("/save_network", HTTP_POST,[]() {
    if (httpServer.hasArg("hostname") && !httpServer.arg("hostname").isEmpty())
      deviceHostname = httpServer.arg("hostname");
    if (httpServer.hasArg("ap_ssid") && !httpServer.arg("ap_ssid").isEmpty())
      apSSID = httpServer.arg("ap_ssid");
    if (httpServer.hasArg("ap_pass") && !httpServer.arg("ap_pass").isEmpty())
      apPassword = httpServer.arg("ap_pass");
    if (httpServer.hasArg("ota_pass"))
      otaPassword = httpServer.arg("ota_pass");   // vacío = sin contraseña
    if (httpServer.hasArg("tcp_port")) {
      int p = httpServer.arg("tcp_port").toInt();
      if (p > 0 && p < 65536) tcpPort = (uint16_t)p;
    }
    saveNetworkConfig();
    httpServer.send(200, "text/plain", "Red guardada — reiniciando...");
    delay(1000); ESP.restart();
  });

  // POST /save_pins -- valida y guarda nueva asignacion de pines GPIO
  httpServer.on("/save_pins", HTTP_POST,[]() {
    int scl=httpServer.arg("scl").toInt(), sda=httpServer.arg("sda").toInt();
    int rst=httpServer.arg("rst").toInt(), sb=httpServer.arg("sb").toInt();
    int led=httpServer.arg("led").toInt();
    bool ok = scl>0 && sda>0 && rst>=0 && sb>=0 && led>=0
           && scl!=sda && scl!=rst && scl!=sb && scl!=led
           && sda!=rst && sda!=sb  && sda!=led
           && rst!=sb  && rst!=led && sb!=led;
    for (int p:{scl,sda,rst,sb,led})
      if (p>=6 && p<=11) ok=false;  // GPIO 6-11: flash SPI interno
    if (!ok) { httpServer.send(400, "text/plain", "Pins invalidos"); return; }
    savePins(scl,sda,rst,sb,led);
    httpServer.send(200, "text/plain", "OK");
    delay(1000); ESP.restart();
  });

  // POST /save_eq_addrs -- guarda direcciones del ADAU1701
  // Param RAM (a0-a7, bfa, bba, ivbt, ivli): rango 0-1023 (10 bits)
  // Program RAM byte offsets (vul, vur):      rango 0-65535 (16 bits)
  httpServer.on("/save_eq_addrs", HTTP_POST,[]() {
    bool changed = false;
    for (int b = 0; b < EQ_NUM_BANDS; b++) {
      String key = "a" + String(b);
      if (httpServer.hasArg(key)) {
        int addr = httpServer.arg(key).toInt();
        if (addr >= 0 && addr <= 1023) { eqBands[b].baseAddr = (uint16_t)addr; changed = true; }
      }
    }
    if (httpServer.hasArg("bfa")) {
      int addr = httpServer.arg("bfa").toInt();
      if (addr >= 0 && addr <= 1023) { addrBassFreq = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("bba")) {
      int addr = httpServer.arg("bba").toInt();
      if (addr >= 0 && addr <= 1023) { addrBassBoost = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("bca")) {
      int addr = httpServer.arg("bca").toInt();
      if (addr >= 0 && addr <= 1023) { addrBassComp = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("ivbt")) {
      int addr = httpServer.arg("ivbt").toInt();
      if (addr >= 0 && addr <= 1023) { addrInputVolBT = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("ivli")) {
      int addr = httpServer.arg("ivli").toInt();
      if (addr >= 0 && addr <= 1023) { addrInputVolLineIn = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("ivst")) {
      int addr = httpServer.arg("ivst").toInt();
      if (addr >= 0 && addr <= 1023) { addrInputVolSineTone = (uint16_t)addr; changed = true; }
    }
    // VU: byte offsets en program RAM -- rango hasta 0xFFFF (no 1023)
    if (httpServer.hasArg("vul")) {
      int addr = httpServer.arg("vul").toInt();
      if (addr >= 0 && addr <= 0xFFFF) { addrVuL = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("vur")) {
      int addr = httpServer.arg("vur").toInt();
      if (addr >= 0 && addr <= 0xFFFF) { addrVuR = (uint16_t)addr; changed = true; }
    }
    // DSP I2C address (0x34–0x37)
    if (httpServer.hasArg("dsp_addr")) {
      int a = httpServer.arg("dsp_addr").toInt();
      if (a >= 0x34 && a <= 0x37) { dspI2cAddr = (uint8_t)a; changed = true; }
    }
    // VU meter window (50–2000 ms)
    if (httpServer.hasArg("vu_win")) {
      int w = httpServer.arg("vu_win").toInt();
      if (w >= 50 && w <= 2000) { vuWindowMs = (uint32_t)w; changed = true; }
    }
    // Sine Tone L/R (Autosoner sweep) — 3 params por canal: mask, increment, ison
    if (httpServer.hasArg("stlm")) {
      int addr = httpServer.arg("stlm").toInt();
      if (addr >= 0 && addr <= 1023) { addrSineLMask = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("stli")) {
      int addr = httpServer.arg("stli").toInt();
      if (addr >= 0 && addr <= 1023) { addrSineLFreq = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("stlo")) {
      int addr = httpServer.arg("stlo").toInt();
      if (addr >= 0 && addr <= 1023) { addrSineLIson = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("strm")) {
      int addr = httpServer.arg("strm").toInt();
      if (addr >= 0 && addr <= 1023) { addrSineRMask = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("stri")) {
      int addr = httpServer.arg("stri").toInt();
      if (addr >= 0 && addr <= 1023) { addrSineRFreq = (uint16_t)addr; changed = true; }
    }
    if (httpServer.hasArg("stro")) {
      int addr = httpServer.arg("stro").toInt();
      if (addr >= 0 && addr <= 1023) { addrSineRIson = (uint16_t)addr; changed = true; }
    }
    if (changed) { saveEqAddrs(); saveDspConfig(); }
    httpServer.send(200, "text/plain", "Guardado");
  });

  // POST /factory_reset -- borra NVS + SPIFFS y reinicia en AP mode
  httpServer.on("/factory_reset", HTTP_POST,[]() {
    // 1. Aislar DSP: no tocar registros a partir de ahora
    dspLocked = true;

    // 2. Borrar NVS completa
    prefs.begin("tcpi", false); prefs.clear(); prefs.end();

    // 3. Borrar presets EQ (p0..p4.json)
    for (int i = 0; i < EQ_MEM_SLOTS; i++) {
      String path = "/p" + String(i) + ".json";
      if (SPIFFS.exists(path)) SPIFFS.remove(path);
    }

    // 4. Borrar esquemas DSP (schema_0..3.bin/.json)
    for (int i = 0; i < 4; i++) {
      String bin = "/schema_" + String(i) + ".bin";
      String jsn = "/schema_" + String(i) + ".json";
      if (SPIFFS.exists(bin)) SPIFFS.remove(bin);
      if (SPIFFS.exists(jsn)) SPIFFS.remove(jsn);
    }

    // 5. Borrar posible temporal de restore
    if (SPIFFS.exists("/restore.tmp")) SPIFFS.remove("/restore.tmp");

    Serial.println("[FACTORY] NVS + SPIFFS borrados, DSP aislado");
    httpServer.send(200, "text/plain", "Borrado total -- AP mode");
    delay(1000); ESP.restart();
  });
}

// =============================================================
// hardware.ino — Hardware: I2C, WiFi, LED, scan, DSP reset
// =============================================================

void initHardware() {
  pinMode(pinLED,          OUTPUT); digitalWrite(pinLED,      LOW);
  pinMode(pinSELFBOOT,     OUTPUT); digitalWrite(pinSELFBOOT, LOW);
  pinMode(pinRESET,        OUTPUT); digitalWrite(pinRESET,    HIGH);
  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);
  Wire.setBufferSize(2048);
  Wire.begin(pinSDA, pinSCL, 400000);
  Wire.setTimeOut(10);   // 10 ms — evita bloqueos largos si el DSP no responde
  Serial.printf("[I2C] SCL=%d SDA=%d 400kHz  timeout:10ms\n", pinSCL, pinSDA);
}

bool connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(100);

  // Intentamos primero SOLO con nuestro Router (Modo Estacion / STA)
  WiFi.mode(WIFI_STA);
  delay(100);

  WiFi.begin(savedSSID.c_str(), savedPassword.c_str());
  Serial.printf("[WiFi] Buscando router '%s'", savedSSID.c_str());

  for (int t = 0; t < 20 && WiFi.status() != WL_CONNECTED; t++) {
    delay(500); 
    Serial.print(".");
  }

  // ¿Nos hemos conectado con éxito al router de casa?
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("\n[WiFi] ÉXITO! STA IP: %s\n", WiFi.localIP().toString().c_str());
    if (MDNS.begin(deviceHostname.c_str())) {
      Serial.printf("[mDNS] htpp://%s.local\n", deviceHostname.c_str());
    }
    apMode = false;
    // Si la conexión triunfa, terminamos aquí. ¡No encendemos el AP!
    return true; 
  }

  // === FALLO DE CONEXIÓN AL ROUTER ===
  // Si llegamos hasta aquí, han pasado 10 segundos y no ha encontrado el wifi configurado
  Serial.println("\n[WiFi] ERROR: Router no encontrado. Levantando el AP de emergencia...");

  WiFi.mode(WIFI_AP);
  delay(100);

  WiFi.softAPConfig(
    IPAddress(192,168,4,1), 
    IPAddress(192,168,4,1), 
    IPAddress(255,255,255,0)
  );

  bool apOk = WiFi.softAP(apSSID.c_str(), apPassword.c_str());
  delay(500);
  
  Serial.printf("[AP] Red creada %s SSID:'%s' IP:192.168.4.1\n", apOk ? "OK" : "FAIL", apSSID.c_str());
  apMode = true;
  return false;
}

void startAP() {
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  apMode = true;
}

void resetDSP() {
  dspRunning = false;

  extern void directWrite(uint8_t i2cAddr, uint16_t regAddr, uint8_t* data, uint16_t dataLen);

  // Parar el procesador primero por I2C (provoca el silencio inmediato/mute)
  uint8_t stopCmd[] = {0x00, 0x00};
  directWrite(dspI2cAddr, 0x081C, stopCmd, 2);
  delay(10);

  // SELFBOOT = HIGH: al soltar el RESET el ADAU1701 carga el
  // programa desde la EEPROM externa en lugar de esperar I2C.
  // Requiere haber grabado la EEPROM previamente con SigmaStudio
  // mediante el botón "Write EEPROM — Selfboot".
  digitalWrite(pinSELFBOOT, HIGH);
  delay(5);
  digitalWrite(pinRESET, LOW);
  delay(20);
  digitalWrite(pinRESET, HIGH);   // DSP comienza a leer EEPROM

  // La carga de la EEPROM tarda ~300 ms a 400 kHz.
  // Esperamos 450 ms para dar margen.
  delay(450);
  digitalWrite(pinSELFBOOT, LOW);
  delay(30);

  // Por si el pin_reset físico no estaba bien cableado, forzamos el encendido por I2C
  uint8_t runCmd[] = {lastCoreCtrl[0], lastCoreCtrl[1] | 0x04};
  directWrite(dspI2cAddr, 0x081C, runCmd, 2);

  // Re-aplicar la configuración de param RAM por encima de los
  // valores por defecto que vinieron de la EEPROM.
  for (int b = 0; b < EQ_NUM_BANDS; b++) writeEqBand(b);
  updateBassDSP();
  writeInputVol(addrInputVolBT,     inputVolBT);
  writeInputVol(addrInputVolLineIn, inputVolLineIn);
  writeInputVol(addrInputVolSineTone, inputVolSineTone);

  dspRunning = true;
  Serial.println("[DSP] Reset+selfboot OK — param RAM re-aplicado");
}

void scanI2C() {
  Serial.println("[I2C] Scanning:");
  for (uint8_t a = 1; a < 127; a++) {
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0)
      Serial.printf("  Found 0x%02X\n", a);
  }
}

void blinkLED(int n) {
  bool wasOn = (digitalRead(pinLED) == HIGH);
  for (int i = 0; i < n; i++) {
    digitalWrite(pinLED, HIGH); delay(100);
    digitalWrite(pinLED, LOW);  delay(100);
  }
  if (wasOn || (!apMode && client && client.connected()))
    digitalWrite(pinLED, HIGH);
}

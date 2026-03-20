// =============================================================
// config_nvs.ino — Persistencia NVS (Preferences)
// =============================================================

void loadConfig() {
  prefs.begin("tcpi", true);
  savedSSID      = prefs.getString("ssid",       FACTORY_SSID);
  savedPassword  = prefs.getString("password",   FACTORY_PASSWORD);
  deviceHostname = prefs.getString("hostname",   HOSTNAME);
  apSSID         = prefs.getString("ap_ssid",    AP_SSID);
  apPassword     = prefs.getString("ap_pass",    AP_PASSWORD);
  otaPassword    = prefs.getString("ota_pass",   OTA_PASSWORD);
  tcpPort        = prefs.getUInt("tcp_port",     TCP_PORT);
  dspI2cAddr     = prefs.getUChar("dsp_addr",   DSP_I2C_ADDR);
  vuWindowMs     = prefs.getUInt("vu_win",       VU_WINDOW_MS);
  pinSCL        = prefs.getInt("pin_scl",        DEFAULT_SCL);
  pinSDA        = prefs.getInt("pin_sda",        DEFAULT_SDA);
  pinRESET      = prefs.getInt("pin_reset",      DEFAULT_RESET);
  pinSELFBOOT   = prefs.getInt("pin_selfboot",   DEFAULT_SELFBOOT);
  pinLED        = prefs.getInt("pin_led",        DEFAULT_LED);
  eqBootEnabled = prefs.getBool("eq_boot",  true);
  dspLocked     = prefs.getBool("dsp_lock", false);
  activeRamSource    = prefs.getInt("act_ram",    -1);
  activeEepromSource = prefs.getInt("act_eeprom", -1);
  prefs.end();
  Serial.printf("[NVS] SSID:%s  SCL:%d SDA:%d RST:%d SB:%d LED:%d\n",
    savedSSID.c_str(), pinSCL, pinSDA, pinRESET, pinSELFBOOT, pinLED);
}

void saveEqBootEnabled() {
  prefs.begin("tcpi", false);
  prefs.putBool("eq_boot", eqBootEnabled);
  prefs.end();
}

void saveDspLock() {
  prefs.begin("tcpi", false);
  prefs.putBool("dsp_lock", dspLocked);
  prefs.end();
}

void saveWiFi(const String& ssid, const String& pass) {
  prefs.begin("tcpi", false);
  prefs.putString("ssid",     ssid);
  prefs.putString("password", pass);
  prefs.end();
}

void saveNetworkConfig() {
  prefs.begin("tcpi", false);
  prefs.putString("hostname", deviceHostname);
  prefs.putString("ap_ssid",  apSSID);
  prefs.putString("ap_pass",  apPassword);
  prefs.putString("ota_pass", otaPassword);
  prefs.putUInt("tcp_port",   tcpPort);
  prefs.end();
}

void saveDspConfig() {
  prefs.begin("tcpi", false);
  prefs.putUChar("dsp_addr", dspI2cAddr);
  prefs.putUInt("vu_win",    vuWindowMs);
  prefs.end();
}

void savePins(int scl, int sda, int rst, int sb, int led) {
  prefs.begin("tcpi", false);
  prefs.putInt("pin_scl",      scl);
  prefs.putInt("pin_sda",      sda);
  prefs.putInt("pin_reset",    rst);
  prefs.putInt("pin_selfboot", sb);
  prefs.putInt("pin_led",      led);
  prefs.end();
}

void saveEqBand(int band) {
  char kf[12], kg[12], kq[12];
  snprintf(kf, sizeof(kf), "eq%d_f", band);
  snprintf(kg, sizeof(kg), "eq%d_g", band);
  snprintf(kq, sizeof(kq), "eq%d_q", band);
  prefs.begin("tcpi", false);
  prefs.putFloat(kf, eqBands[band].freq);
  prefs.putFloat(kg, eqBands[band].gainDb);
  prefs.putFloat(kq, eqBands[band].q);
  prefs.end();
}

void loadEqBands() {
  prefs.begin("tcpi", true);
  for (int b = 0; b < EQ_NUM_BANDS; b++) {
    char kf[12], kg[12], kq[12], ka[12];
    snprintf(kf, sizeof(kf), "eq%d_f", b);
    snprintf(kg, sizeof(kg), "eq%d_g", b);
    snprintf(kq, sizeof(kq), "eq%d_q", b);
    snprintf(ka, sizeof(ka), "eq%d_a", b);
    eqBands[b].freq     = prefs.getFloat(kf, eqBands[b].freq);
    eqBands[b].gainDb   = prefs.getFloat(kg, eqBands[b].gainDb);
    eqBands[b].q        = prefs.getFloat(kq, eqBands[b].q);
    eqBands[b].baseAddr = prefs.getUInt(ka,  eqBands[b].baseAddr);
  }
  eqLastNX     = prefs.getFloat("eq_nx",  0.0f);
  eqLastNY     = prefs.getFloat("eq_ny",  0.0f);
  eqActiveSlot = prefs.getInt("eq_slot", -1);
  
  bassFreq      = prefs.getFloat("bass_f",   DEFAULT_BASS_FREQ);
  bassBoost     = prefs.getFloat("bass_b",   DEFAULT_BASS_BOOST);
  bassCompRatio = prefs.getFloat("bass_cr",  DEFAULT_BASS_COMP);
  addrBassFreq  = prefs.getUInt("bass_fa",   DEFAULT_ADDR_BASS_F);
  addrBassBoost = prefs.getUInt("bass_ba",   DEFAULT_ADDR_BASS_B);
  addrBassComp  = prefs.getUInt("bass_cra",  DEFAULT_ADDR_BASS_C);

  inputVolBT         = prefs.getFloat("invol_bt",  DEFAULT_INVOL_BT);
  inputVolLineIn     = prefs.getFloat("invol_li",  DEFAULT_INVOL_LI);
  inputVolSineTone   = prefs.getFloat("invol_st",  DEFAULT_INVOL_ST);
  addrInputVolBT     = prefs.getUInt("invol_bta",  DEFAULT_ADDR_INVOL_BT);
  addrInputVolLineIn = prefs.getUInt("invol_lia",  DEFAULT_ADDR_INVOL_LI);
  addrInputVolSineTone = prefs.getUInt("invol_sta", DEFAULT_ADDR_INVOL_ST);
  addrVuL            = prefs.getUInt("vu_l_a",     DEFAULT_ADDR_VU_L);
  addrVuR            = prefs.getUInt("vu_r_a",     DEFAULT_ADDR_VU_R);

  addrSineLMask      = prefs.getUInt("st_lm",     SINE_TONE_L_MASK_ADDR);
  addrSineLFreq      = prefs.getUInt("st_li",     SINE_TONE_L_FREQ_ADDR);
  addrSineLIson      = prefs.getUInt("st_lo",     SINE_TONE_L_ISON_ADDR);
  addrSineRMask      = prefs.getUInt("st_rm",     SINE_TONE_R_MASK_ADDR);
  addrSineRFreq      = prefs.getUInt("st_ri",     SINE_TONE_R_FREQ_ADDR);
  addrSineRIson      = prefs.getUInt("st_ro",     SINE_TONE_R_ISON_ADDR);

  prefs.end();
  Serial.println("[NVS] EQ, Bass Boost y Sine Tone restaurados");
}

void saveEqAddrs() {
  prefs.begin("tcpi", false);
  for (int b = 0; b < EQ_NUM_BANDS; b++) {
    char ka[12];
    snprintf(ka, sizeof(ka), "eq%d_a", b);
    prefs.putUInt(ka, eqBands[b].baseAddr);
  }
  prefs.putUInt("bass_fa",  addrBassFreq);
  prefs.putUInt("bass_ba",  addrBassBoost);
  prefs.putUInt("bass_cra", addrBassComp);
  prefs.putUInt("invol_bta", addrInputVolBT);
  prefs.putUInt("invol_lia", addrInputVolLineIn);
  prefs.putUInt("invol_sta", addrInputVolSineTone);
  prefs.putUInt("vu_l_a",    addrVuL);
  prefs.putUInt("vu_r_a",    addrVuR);
  prefs.putUInt("st_lm",     addrSineLMask);
  prefs.putUInt("st_li",     addrSineLFreq);
  prefs.putUInt("st_lo",     addrSineLIson);
  prefs.putUInt("st_rm",     addrSineRMask);
  prefs.putUInt("st_ri",     addrSineRFreq);
  prefs.putUInt("st_ro",     addrSineRIson);
  prefs.end();
}

void saveEqXYSlot() {
  prefs.begin("tcpi", false);
  prefs.putFloat("eq_nx",  eqLastNX);
  prefs.putFloat("eq_ny",  eqLastNY);
  prefs.putInt("eq_slot",  eqActiveSlot);
  prefs.end();
}

void saveActiveSources() {
  prefs.begin("tcpi", false);
  prefs.putInt("act_ram",    activeRamSource);
  prefs.putInt("act_eeprom", activeEepromSource);
  prefs.end();
}

void saveBassParams() {
  prefs.begin("tcpi", false);
  prefs.putFloat("bass_f",  bassFreq);
  prefs.putFloat("bass_b",  bassBoost);
  prefs.putFloat("bass_cr", bassCompRatio);
  prefs.end();
}

void saveInputVols() {
  prefs.begin("tcpi", false);
  prefs.putFloat("invol_bt", inputVolBT);
  prefs.putFloat("invol_li", inputVolLineIn);
  prefs.putFloat("invol_st", inputVolSineTone);
  prefs.end();
}

void resetEqDefaults() {
  // ── NUEVA CONFIGURACIÓN GEMINI OPTIMIZADA PARA TU CAJA DE 20 cm ─────────────
  const float NEW_FREQ[EQ_NUM_BANDS] = {
    55.0f,    // 1. Punch / subgrave real
    150.0f,   // 2. Limpieza anti-barro
    400.0f,   // 3. Autoridad y pecho de voz
    1000.0f,  // 4. Banda media honesta
    2500.0f,  // 5. Presencia (punto mágico)
    5000.0f,  // 6. Brillo y consonantes
    10000.0f, // 7. Aire y elegancia
    16000.0f  // 8. Apertura sutil
  };

  const float NEW_Q[EQ_NUM_BANDS] = {
    0.78f,   // Low Shelf (suave y musical)
    1.32f,   // 150 Hz - selectivo contra el barro
    1.38f,   // 400 Hz - autoridad natural
    1.50f,   // 1 kHz - equilibrado
    2.05f,   // 2.5 kHz - presencia quirúrgica
    1.68f,   // 5 kHz - brillo controlado
    1.28f,   // 10 kHz - aire amplio
    0.71f    // High Shelf (elegante y clásico)
  };

  for (int b = 0; b < EQ_NUM_BANDS; b++) {
    eqBands[b].freq   = NEW_FREQ[b];
    eqBands[b].gainDb = EQ_DEFAULT_GAIN[b];   // plano por defecto
    eqBands[b].q      = NEW_Q[b];

    // ← Mantenemos exactamente los Shelves del original
    if (b == 0) {
      eqBands[b].type = EQ_LOW_SHELF;
    } else if (b == 7) {
      eqBands[b].type = EQ_HIGH_SHELF;
    }
    // Las bandas del medio ya eran parametric → no las tocamos

    saveEqBand(b);
    writeEqBand(b);
  }

  eqLastNX = 0.0f; 
  eqLastNY = 0.0f;
  eqActiveSlot = -1;
  saveEqXYSlot();
  
  bassFreq = 35.0f;
  bassBoost = 6.0f;
  saveBassParams();
  updateBassDSP();
  
  LOGLN("[EQ] Reset a configuración Gemini (55LS → 16kHS + Q ajustado)");
}
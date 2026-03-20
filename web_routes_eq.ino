// =============================================================
// web_routes_eq.ino -- Rutas HTTP: EQ, VU meter, Input Volume
// =============================================================
//
// Registra todos los endpoints relacionados con el DSP:
//   /eq/state        GET   -- estado completo del EQ en JSON
//   /eq/set          GET   -- escribe una banda (freq/gain/Q)
//   /eq/bass         GET   -- ajusta bass boost
//   /eq/xy           GET   -- posicion del pad XY
//   /eq/toggle       GET   -- activa/desactiva el EQ
//   /eq/reset        GET   -- resetea bandas a valores por defecto
//   /eq/mem/save     GET   -- guarda preset en slot M1-M5
//   /eq/mem/load     GET   -- carga preset desde slot
//   /eq/mem/clear    POST  -- borra todos los presets
//   /vu              GET   -- niveles VU en JSON
//   /vu_scan         GET   -- escanea rango de program RAM (debug)
//   /vu_debug        GET   -- dos snapshots y diff (debug)
//   /input/vol       GET   -- volumen de entrada BT / Line In
//
// =============================================================

void registerEqRoutes() {

  httpServer.on("/eq/state",[]() {
    httpServer.send(200, "application/json", eqStateJSON());
  });

  httpServer.on("/vu",[]() {
    String j = "{\"l\":" + String(vuLevelL, 4) + ",\"r\":" + String(vuLevelR, 4) + "}";
    httpServer.send(200, "application/json", j);
  });

  // GET /vu_scan?from=0x0700&to=0x0730
  // Devuelve JSON array con {pc, raw, float} para cada instruccion del rango.
  // Llama dos veces (silencio / con senal) y compara cuales cambian.
  httpServer.on("/vu_scan",[]() {
    uint16_t from = 0x0700, to = 0x0730;
    if (httpServer.hasArg("from")) {
      String s = httpServer.arg("from");
      from = (uint16_t)(s.startsWith("0x")||s.startsWith("0X") ? strtol(s.c_str(),nullptr,16) : s.toInt());
    }
    if (httpServer.hasArg("to")) {
      String s = httpServer.arg("to");
      to = (uint16_t)(s.startsWith("0x")||s.startsWith("0X") ? strtol(s.c_str(),nullptr,16) : s.toInt());
    }
    if (to < from || (to - from) > 64) { httpServer.send(400,"text/plain","Rango max 64"); return; }
    String j = "[";
    for (uint16_t pc = from; pc <= to; pc++) {
      Wire.beginTransmission(DSP_I2C_ADDR);
      Wire.write((DATA_CAPTURE_REG >> 8) & 0xFF);
      Wire.write(DATA_CAPTURE_REG & 0xFF);
      Wire.write((pc >> 8) & 0xFF);
      Wire.write(pc & 0xFF);
      Wire.endTransmission(true);
      delayMicroseconds(50);
      Wire.beginTransmission(DSP_I2C_ADDR);
      Wire.write((DATA_CAPTURE_REG >> 8) & 0xFF);
      Wire.write(DATA_CAPTURE_REG & 0xFF);
      Wire.endTransmission(false);
      int got = Wire.requestFrom((int)DSP_I2C_ADDR, 4);
      uint8_t b0=0,b1=0,b2=0,b3=0;
      if (got==4){b0=Wire.read();b1=Wire.read();b2=Wire.read();b3=Wire.read();}
      int32_t raw = ((int32_t)b0<<24)|((int32_t)b1<<16)|((int32_t)b2<<8)|b3;
      float fv = (float)raw / (float)(1<<23);
      char entry[80];
      snprintf(entry, sizeof(entry), "%s{\"pc\":\"0x%04X\",\"raw\":\"0x%02X%02X%02X%02X\",\"f\":%.5f}",
        pc==from?"":","  , pc, b0,b1,b2,b3, fv);
      j += entry;
    }
    j += "]";
    httpServer.send(200, "application/json", j);
  });

  // GET /vu_debug -- dos snapshots separados 800ms, devuelve solo celdas que cambiaron.
  httpServer.on("/vu_debug",[]() {
    const uint16_t N = 64;
    int32_t s1[N], s2[N];
    auto readCell = [](uint16_t a) -> int32_t {
      Wire.beginTransmission(DSP_I2C_ADDR);
      Wire.write((a>>8)&0xFF); Wire.write(a&0xFF);
      Wire.endTransmission(false);
      int g = Wire.requestFrom((int)DSP_I2C_ADDR, 4);
      uint8_t b0=0,b1=0,b2=0,b3=0;
      if(g==4){b0=Wire.read();b1=Wire.read();b2=Wire.read();b3=Wire.read();}
      return ((int32_t)b0<<24)|((int32_t)b1<<16)|((int32_t)b2<<8)|b3;
    };
    for(uint16_t a=0;a<N;a++) s1[a]=readCell(a);
    delay(800);
    for(uint16_t a=0;a<N;a++) s2[a]=readCell(a);
    String j="{\"changed\":[";
    bool first=true;
    for(uint16_t a=0;a<N;a++){
      int32_t d=s2[a]-s1[a]; if(d<0)d=-d;
      if(d>2048){
        float f1=(float)s1[a]/(float)(1<<23);
        float f2=(float)s2[a]/(float)(1<<23);
        char e[80]; snprintf(e,sizeof(e),"%s{\"a\":%d,\"f1\":%.4f,\"f2\":%.4f}",first?"":",",a,f1,f2);
        j+=e; first=false;
      }
    }
    j+="],\"snapshot\":[";
    for(uint16_t a=0;a<N;a++){
      float f=(float)s2[a]/(float)(1<<23);
      char e[60]; snprintf(e,sizeof(e),"%s{\"a\":%d,\"f\":%.5f}",a==0?"":",",a,f);
      j+=e;
    }
    j+="]}";
    httpServer.send(200,"application/json",j);
  });

  httpServer.on("/eq/bass",[]() {
    if (httpServer.hasArg("f") && httpServer.hasArg("b")) {
      bassFreq  = httpServer.arg("f").toFloat();
      bassBoost = httpServer.arg("b").toFloat();
      if (httpServer.hasArg("c"))
        bassCompRatio = constrain(httpServer.arg("c").toFloat(), 1.0f, 20.0f);
      updateBassDSP();
      saveBassParams();
      httpServer.send(200, "text/plain", "OK");
    } else {
      httpServer.send(400, "text/plain", "Missing args");
    }
  });

  httpServer.on("/eq/set",[]() {
    if (!httpServer.hasArg("band") || !httpServer.hasArg("freq") ||
        !httpServer.hasArg("gain") || !httpServer.hasArg("q")) {
      httpServer.send(400, "text/plain", "Missing args"); return;
    }
    int   band = httpServer.arg("band").toInt();
    float freq = httpServer.arg("freq").toFloat();
    float gain = httpServer.arg("gain").toFloat();
    float q    = httpServer.arg("q").toFloat();
    if (band < 0 || band >= EQ_NUM_BANDS) { httpServer.send(400, "text/plain", "Bad band"); return; }
    eqBands[band].freq   = freq;
    eqBands[band].gainDb = gain;
    eqBands[band].q      = q;
    writeEqBand(band);
    saveEqBand(band);
    httpServer.send(200, "text/plain", "OK");
  });

  httpServer.on("/eq/xy",[]() {
    if (!httpServer.hasArg("nx") || !httpServer.hasArg("ny")) {
      httpServer.send(400, "text/plain", "Missing nx/ny"); return;
    }
    float xv = constrain(httpServer.arg("nx").toFloat(), -1.0f, 1.0f);
    float yv = constrain(httpServer.arg("ny").toFloat(), -1.0f, 1.0f);
    applyXY(xv, yv);
    httpServer.send(200, "text/plain", "OK");
  });

  httpServer.on("/eq/toggle",[]() {
    eqEnabled = !eqEnabled;
    Serial.printf("[EQ] eqEnabled -> %s\n", eqEnabled ? "ON" : "OFF");
    httpServer.send(200, "text/plain", eqEnabled ? "EQ activado" : "EQ desactivado");
  });

  httpServer.on("/eq/reset",[]() {
    resetEqDefaults();
    httpServer.send(200, "text/plain", "EQ reseteado");
  });

  httpServer.on("/eq/mem/save",[]() {
    if (!httpServer.hasArg("slot")) { httpServer.send(400, "text/plain", "Missing slot"); return; }
    int slot = httpServer.arg("slot").toInt();
    saveEqMemory(slot);
    httpServer.send(200, "text/plain", "Guardado en M" + String(slot+1));
  });

  httpServer.on("/eq/mem/load",[]() {
    if (!httpServer.hasArg("slot")) { httpServer.send(400, "text/plain", "Missing slot"); return; }
    int slot = httpServer.arg("slot").toInt();
    if (!memoryHasData(slot)) {
      httpServer.send(200, "text/plain", "Slot M" + String(slot+1) + " vacio"); return;
    }
    loadEqMemory(slot);
    httpServer.send(200, "text/plain", "Cargado M" + String(slot+1));
  });

  httpServer.on("/eq/mem/clear", HTTP_POST,[]() {
    clearMemorySlots();
    httpServer.send(200, "text/plain", "Presets borrados");
  });

  httpServer.on("/input/vol",[]() {
    if (!httpServer.hasArg("ch") || !httpServer.hasArg("v")) {
      httpServer.send(400, "text/plain", "Missing args"); return;
    }
    String ch = httpServer.arg("ch");
    float db = constrain(httpServer.arg("v").toFloat(), -30.0f, 6.0f);
    if (ch == "bt") {
      inputVolBT = db;
      writeInputVol(addrInputVolBT, db);
      saveInputVols();
      httpServer.send(200, "text/plain", "BT Vol " + String(db, 1) + " dB");
    } else if (ch == "li") {
      inputVolLineIn = db;
      writeInputVol(addrInputVolLineIn, db);
      saveInputVols();
      httpServer.send(200, "text/plain", "Line In Vol " + String(db, 1) + " dB");
    } else if (ch == "st") {
      inputVolSineTone = db;
      writeInputVol(addrInputVolSineTone, db);
      saveInputVols();
      httpServer.send(200, "text/plain", "Sine Tone Vol " + String(db, 1) + " dB");
    } else {
      httpServer.send(400, "text/plain", "Unknown channel");
    }
  });
}

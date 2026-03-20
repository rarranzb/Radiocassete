// =============================================================
// presets_spiffs.ino — Presets M1-M5 en SPIFFS (archivos JSON)
// =============================================================

String presetPath(int slot) {
  return "/p" + String(slot) + ".json";
}

void saveEqMemory(int slot) {
  if (slot < 0 || slot >= EQ_MEM_SLOTS) return;

  File f = SPIFFS.open(presetPath(slot), FILE_WRITE);
  if (!f) {
    LOG("[MEM] ERROR abriendo %s\n", presetPath(slot).c_str());
    return;
  }
  f.printf("{\"nx\":%.4f,\"ny\":%.4f,\"bf\":%.1f,\"bb\":%.2f,\"bc\":%.2f,\"b\":[", eqLastNX, eqLastNY, bassFreq, bassBoost, bassCompRatio);
  for (int b = 0; b < EQ_NUM_BANDS; b++) {
    if (b > 0) f.print(",");
    f.printf("{\"f\":%.1f,\"g\":%.4f,\"q\":%.4f}",
      eqBands[b].freq, eqBands[b].gainDb, eqBands[b].q);
  }
  f.print("]}");
  f.close();

  eqActiveSlot = slot;
  saveEqXYSlot();
  LOG("[MEM] Guardada M%d  nx=%.3f ny=%.3f\n", slot+1, eqLastNX, eqLastNY);
}

void loadEqMemory(int slot) {
  if (slot < 0 || slot >= EQ_MEM_SLOTS) return;

  String path = presetPath(slot);
  if (!SPIFFS.exists(path)) {
    LOG("[MEM] M%d vacío\n", slot+1);
    return;
  }
  File f = SPIFFS.open(path, FILE_READ);
  if (!f) return;
  String j = f.readString();
  f.close();

  auto getVal = [&](const String& key) -> float {
    int i = j.indexOf("\"" + key + "\":");
    if (i < 0) return 0.0f;
    return j.substring(i + key.length() + 3).toFloat();
  };

  eqLastNX = getVal("nx");
  eqLastNY = getVal("ny");
  
  float parsedBF = getVal("bf");
  bassFreq = (parsedBF >= 20.0f) ? parsedBF : 60.0f;
  bassBoost = getVal("bb");
  float parsedBC = getVal("bc");
  bassCompRatio = (parsedBC >= 1.0f) ? parsedBC : DEFAULT_BASS_COMP;

  int pos = j.indexOf("\"b\":[");
  if (pos >= 0) {
    pos += 5;
    for (int b = 0; b < EQ_NUM_BANDS; b++) {
      int fb = j.indexOf("\"f\":", pos);
      int gb = j.indexOf("\"g\":", pos);
      int qb = j.indexOf("\"q\":", pos);
      if (fb < 0 || gb < 0 || qb < 0) break;
      eqBands[b].freq   = j.substring(fb+4).toFloat();
      eqBands[b].gainDb = j.substring(gb+4).toFloat();
      eqBands[b].q      = j.substring(qb+4).toFloat();
      pos = j.indexOf("}", pos) + 1;
    }
  }

  for (int b = 0; b < EQ_NUM_BANDS; b++) { saveEqBand(b); writeEqBand(b); }
  
  saveBassParams();
  updateBassDSP();
  
  eqActiveSlot = slot;
  saveEqXYSlot();
  LOG("[MEM] Cargada M%d\n", slot+1);
}

bool memoryHasData(int slot) {
  return SPIFFS.exists(presetPath(slot));
}

void clearMemorySlots() {
  for (int s = 0; s < EQ_MEM_SLOTS; s++) {
    String p = presetPath(s);
    if (SPIFFS.exists(p)) SPIFFS.remove(p);
  }
  eqActiveSlot = -1;
  saveEqXYSlot();
  LOGLN("[MEM] Presets borrados");
}
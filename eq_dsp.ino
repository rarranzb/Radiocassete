// =============================================================
// eq_dsp.ino — Biquad EQ: cálculo coeficientes + safeload DSP
// =============================================================

void writeEqBand(int band) {
  if (band < 0 || band >= EQ_NUM_BANDS) return;

  float  f   = eqBands[band].freq;
  float  g   = eqBands[band].gainDb;
  float  q   = eqBands[band].q;
  EqType typ = eqBands[band].type;

  float A  = powf(10.0f, g / 40.0f);
  float w0 = 2.0f * M_PI * f / EQ_SAMPLE_RATE;
  float sn = sinf(w0);
  float cs = cosf(w0);
  float b0, b1, b2, a0, a1, a2;

  if (typ == EQ_LOW_SHELF) {
    float al = sn / 2.0f * sqrtf((A + 1.0f/A) * (1.0f/q - 1.0f) + 2.0f);
    b0 =       A * ((A+1) - (A-1)*cs + 2*sqrtf(A)*al);
    b1 =  2.0f*A * ((A-1) - (A+1)*cs);
    b2 =       A * ((A+1) - (A-1)*cs - 2*sqrtf(A)*al);
    a0 =           (A+1) + (A-1)*cs + 2*sqrtf(A)*al;
    a1 =  -2.0f * ((A-1) + (A+1)*cs);
    a2 =           (A+1) + (A-1)*cs - 2*sqrtf(A)*al;
  } else if (typ == EQ_HIGH_SHELF) {
    float al = sn / 2.0f * sqrtf((A + 1.0f/A) * (1.0f/q - 1.0f) + 2.0f);
    b0 =       A * ((A+1) + (A-1)*cs + 2*sqrtf(A)*al);
    b1 = -2.0f*A * ((A-1) + (A+1)*cs);
    b2 =       A * ((A+1) + (A-1)*cs - 2*sqrtf(A)*al);
    a0 =           (A+1) - (A-1)*cs + 2*sqrtf(A)*al;
    a1 =   2.0f * ((A-1) - (A+1)*cs);
    a2 =           (A+1) - (A-1)*cs - 2*sqrtf(A)*al;
  } else {
    float al = sn / (2.0f * q);
    b0 =  1.0f + al * A;  b1 = -2.0f * cs;  b2 =  1.0f - al * A;
    a0 =  1.0f + al / A;  a1 = -2.0f * cs;  a2 =  1.0f - al / A;
  }

  b0/=a0; b1/=a0; b2/=a0;
  a1/=a0; a2/=a0;
  a1=-a1; a2=-a2;

  auto toFixed =[](float v) -> int32_t { return (int32_t)(v * (float)(1 << 23)); };
  int32_t coefs[5] = { toFixed(b0), toFixed(b1), toFixed(b2), toFixed(a1), toFixed(a2) };
  uint8_t data[20];
  for (int i = 0; i < 5; i++) {
    data[i*4+0] = (coefs[i] >> 24) & 0xFF;
    data[i*4+1] = (coefs[i] >> 16) & 0xFF;
    data[i*4+2] = (coefs[i] >>  8) & 0xFF;
    data[i*4+3] = (coefs[i]      ) & 0xFF;
  }

  if (dspLocked)  return;
  if (!eqEnabled) return;
  safeloadChunk(eqBands[band].baseAddr, data, 5);
}

void applyXY(float nx, float ny) {
  float gains[EQ_NUM_BANDS] = {
     ny * 7.0f,  ny * 5.0f - nx * 2.0f,
    -nx * 3.0f, -nx * 4.0f,
     nx * 4.0f,  nx * 3.0f,
    -ny * 4.0f + nx * 2.0f, -ny * 7.0f
  };
  for (int b = 0; b < EQ_NUM_BANDS; b++) {
    float g = gains[b];
    if (g >  12.0f) g =  12.0f;
    if (g < -12.0f) g = -12.0f;
    eqBands[b].gainDb = g;
    writeEqBand(b);
  }
  eqLastNX = nx; eqLastNY = ny;
  eqActiveSlot = -1;
  saveEqXYSlot();
}

// ── Input Volume -> DSP ───────────────────────────────────────
void writeInputVol(uint16_t addr, float dB) {
  if (dspLocked) return;
  float linear = powf(10.0f, dB / 20.0f);
  int32_t fixed = (int32_t)(linear * (float)(1 << 23));
  uint8_t data[4] = {
    (uint8_t)((fixed >> 24) & 0xFF),
    (uint8_t)((fixed >> 16) & 0xFF),
    (uint8_t)((fixed >>  8) & 0xFF),
    (uint8_t)((fixed      ) & 0xFF)
  };
  safeloadChunk(addr, data, 1);
}

// ── Dynamic Bass Boost -> DSP ─────────────────────────────────
void updateBassDSP() {
  if (dspLocked)  return;
  if (!eqEnabled) return;

  auto write33 = [](uint16_t addr, float val) {
    int32_t fixed = (int32_t)(val * (float)(1 << 23));
    uint8_t data[132];
    for (int i = 0; i < 33; i++) {
      data[i*4+0] = (fixed >> 24) & 0xFF;
      data[i*4+1] = (fixed >> 16) & 0xFF;
      data[i*4+2] = (fixed >>  8) & 0xFF;
      data[i*4+3] = (fixed      ) & 0xFF;
    }
    int offset = 0;
    while (offset < 33) {
      int words = min(33 - offset, 5);
      safeloadChunk(addr + offset, data + offset * 4, words);
      offset += words;
    }
  };

  // 1. Compression ratio: 1/sqrt(ratio) replicado 33 veces
  write33(addrBassComp, 1.0f / sqrtf(bassCompRatio));

  // 2. Boost: 10^(-dB/20) replicado 33 veces
  write33(addrBassBoost, powf(10.0f, -bassBoost / 20.0f));

  // 3. Bass Freq: omega = 2*PI*f/fs
  float omega = 2.0f * M_PI * bassFreq / EQ_SAMPLE_RATE;
  int32_t fixed_w = (int32_t)(omega * (float)(1 << 23));
  uint8_t data_w[4] = {
    (uint8_t)((fixed_w >> 24) & 0xFF),
    (uint8_t)((fixed_w >> 16) & 0xFF),
    (uint8_t)((fixed_w >>  8) & 0xFF),
    (uint8_t)((fixed_w      ) & 0xFF)
  };
  safeloadChunk(addrBassFreq, data_w, 1);
}
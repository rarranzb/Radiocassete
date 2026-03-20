// =============================================================
// vu_meter.ino — VU Meter via Data Capture (ADAU1701)
// =============================================================
//
// Máquina de estados — NO bloquea el loop principal:
//
//   Cada llamada a updateVU() (cada 20 ms) hace UNA sola
//   transacción I2C y devuelve el control inmediatamente.
//
//   Estado 0 → escribe dirección L en 0x081A  (solo write)
//   Estado 1 → lee valor L, escribe dirección R (read + write)
//   Estado 2 → lee valor R, publica ventana de pico (read)
//
//   La lectura se hace 20 ms después de la escritura, dando al
//   DSP ~960 ciclos de audio para capturar el valor. No se
//   necesita delayMicroseconds() entre write y read.
//
// Cómo obtener el byte offset tras recompilar en SigmaStudio:
//   - Abre NombreProyecto_IC_1.h (generado al compilar).
//   - Busca MOD_VUMETROL_READBACK_ADDR  → ese es el WORD address.
//   - Byte offset = word_address × 4.
//   - Actualiza los campos en la pestaña Config de la web.
//
// =============================================================

#define DATA_CAPTURE_REG  0x081A

static float         vuMaxL        = 0.0f;
static float         vuMaxR        = 0.0f;
static unsigned long vuWindowStart = 0;
static uint8_t       vuState       = 0;   // 0=writeL  1=readL+writeR  2=readR
static float         vuTrackerL    = 0.0f;
static float         vuTrackerR    = 0.0f;

// ── Escribe la dirección de captura en 0x081A ─────────────────
static bool vuWriteAddr(uint16_t offset) {
  Wire.beginTransmission(dspI2cAddr);
  Wire.write((DATA_CAPTURE_REG >> 8) & 0xFF);
  Wire.write(DATA_CAPTURE_REG & 0xFF);
  Wire.write((offset >> 8) & 0xFF);
  Wire.write(offset & 0xFF);
  return Wire.endTransmission(true) == 0;
}

// ── Lee 3 bytes del resultado de 0x081A ───────────────────────
// Devuelve -1.0 si hay error I2C.
static float vuReadValue() {
  Wire.beginTransmission(dspI2cAddr);
  Wire.write((DATA_CAPTURE_REG >> 8) & 0xFF);
  Wire.write(DATA_CAPTURE_REG & 0xFF);
  if (Wire.endTransmission(false) != 0) return -1.0f;
  if (Wire.requestFrom((int)dspI2cAddr, 3) < 3) return -1.0f;

  // 3 bytes → 24 bits en formato 5.19 signed
  int32_t raw = ((int32_t)(uint8_t)Wire.read() << 16) |
                ((int32_t)(uint8_t)Wire.read() <<  8) |
                 (uint8_t)Wire.read();
  if (raw & 0x800000) raw |= 0xFF000000;   // extender signo 24→32 bits

  float val = fabsf((float)raw / (float)(1 << 19));
  return (val > 2.0f) ? 2.0f : val;
}

// ── Llamada desde loop() cada 15 ms ──────────────────────────
void updateVU() {
  if (!dspRunning) return;   // DSP apagado → no intentar I2C

  // Decaimiento rápido de envolvente (cae al 80% cada 15ms)
  // Permite que el destello aguante lo suficiente para verse, reteniendo el pico un instante.
  vuTrackerL *= 0.80f;
  vuTrackerR *= 0.80f;

  // ── Canal Izquierdo (L) ──
  vuWriteAddr(addrVuL);
  delayMicroseconds(50);     // Margen de seguridad > 2 frames
  float vL = vuReadValue();
  if (vL >= 0.0f) {
    if (vL > vuTrackerL) vuTrackerL = vL;
    vuLevelL = vuTrackerL;
  }

  // Si ambos canales miden lo mismo, evitamos la segunda lectura
  // asegurando un sincronismo ABSOLUTO y perfecto al 100%.
  if (addrVuL == addrVuR) {
    vuTrackerR = vuTrackerL;
    vuLevelR = vuLevelL;
  } else {
    // ── Canal Derecho (R) ──
    vuWriteAddr(addrVuR);
    delayMicroseconds(50);
    float vR = vuReadValue();
    if (vR >= 0.0f) {
      if (vR > vuTrackerR) vuTrackerR = vR;
      vuLevelR = vuTrackerR;
    }
  }
}



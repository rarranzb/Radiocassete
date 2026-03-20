// =============================================================
// sine_tone.ino — Control del módulo Sine Tone del ADAU1701
// =============================================================
//
// Cada módulo "Tone (Lookup)" de SigmaStudio tiene 3 parámetros:
//
//   [mask]      → constante 0x000000FF (lookup table mask)
//   [increment] → freq / Fs  en formato 5.23 fixed-point
//   [ison]      → 0x00800000 = ON, 0x00000000 = OFF
//
// SigmaStudio escribe los 3 cada vez que cambia freq o on/off.
// Replicamos ese comportamiento para máxima compatibilidad.
//
// Direcciones configurables via Sender.html → NVS.
// =============================================================

// Direcciones runtime (Sender.html → /save_eq_addrs → NVS)
uint16_t addrSineLMask = SINE_TONE_L_MASK_ADDR;
uint16_t addrSineLFreq = SINE_TONE_L_FREQ_ADDR;
uint16_t addrSineLIson = SINE_TONE_L_ISON_ADDR;
uint16_t addrSineRMask = SINE_TONE_R_MASK_ADDR;
uint16_t addrSineRFreq = SINE_TONE_R_FREQ_ADDR;
uint16_t addrSineRIson = SINE_TONE_R_ISON_ADDR;

// Estado interno
static float    sineToneCurrentFreq = 10.0f;
static bool     sineToneIsOn        = false;
static int32_t  sineToneIncFixed    = 0;

// Constante mask del módulo Tone (Lookup): siempre 0x000000FF
static const uint8_t SINE_MASK_DATA[4] = { 0x00, 0x00, 0x00, 0xFF };

/**
 * Escribe los 3 parámetros (mask + increment + ison) a un canal.
 * Replica el comportamiento exacto de SigmaStudio.
 */
static void writeToneChannel(uint16_t maskAddr, uint16_t freqAddr,
                             uint16_t isonAddr, int32_t incFixed, bool on) {
  // 1. mask (constante 0xFF)
  safeloadChunk(maskAddr, (uint8_t*)SINE_MASK_DATA, 1);

  // 2. increment (freq / Fs en 5.23)
  uint8_t incData[4] = {
    (uint8_t)((incFixed >> 24) & 0xFF),
    (uint8_t)((incFixed >> 16) & 0xFF),
    (uint8_t)((incFixed >>  8) & 0xFF),
    (uint8_t)((incFixed      ) & 0xFF)
  };
  safeloadChunk(freqAddr, incData, 1);

  // 3. ison (0x00800000 = ON, 0x00000000 = OFF)
  int32_t isonVal = on ? 0x00800000 : 0x00000000;
  uint8_t isonData[4] = {
    (uint8_t)((isonVal >> 24) & 0xFF),
    (uint8_t)((isonVal >> 16) & 0xFF),
    (uint8_t)((isonVal >>  8) & 0xFF),
    (uint8_t)((isonVal      ) & 0xFF)
  };
  safeloadChunk(isonAddr, isonData, 1);
}

/**
 * Establece la frecuencia del tono senoidal en ambos canales.
 * @param hz  Frecuencia en Hz (1 .. 23000)
 */
void setSineToneFreq(float hz) {
  if (dspLocked) return;
  if (hz < 1.0f)     hz = 1.0f;
  if (hz > 23000.0f) hz = 23000.0f;

  sineToneCurrentFreq = hz;
  sineToneIncFixed = (int32_t)((hz / SINE_TONE_FS) * (float)(1 << 23));

  // Escribir los 3 params a ambos canales (como hace SigmaStudio)
  writeToneChannel(addrSineLMask, addrSineLFreq, addrSineLIson,
                   sineToneIncFixed, sineToneIsOn);
  writeToneChannel(addrSineRMask, addrSineRFreq, addrSineRIson,
                   sineToneIncFixed, sineToneIsOn);
}

/**
 * Activa o desactiva el tono senoidal en ambos canales.
 * @param on  true = tono activo, false = silencio
 */
void setSineToneEnable(bool on) {
  if (dspLocked) return;

  sineToneIsOn = on;

  // Escribir los 3 params a ambos canales (como hace SigmaStudio)
  writeToneChannel(addrSineLMask, addrSineLFreq, addrSineLIson,
                   sineToneIncFixed, sineToneIsOn);
  writeToneChannel(addrSineRMask, addrSineRFreq, addrSineRIson,
                   sineToneIncFixed, sineToneIsOn);
}

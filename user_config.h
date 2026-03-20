// =============================================================
// user_config.h — Parámetros configurables del proyecto
// =============================================================
//
// Edita SOLO este archivo para adaptar el firmware a tu
// hardware y a tu esquema de SigmaStudio.
//
// Los valores marcados con (*) también se pueden cambiar en
// tiempo real desde la pestaña Config de la interfaz web,
// y se guardan en NVS (persisten tras reinicio).
// Los valores de fábrica aquí definidos se usan únicamente
// la primera vez que arranca el ESP32 (o tras borrar NVS).
//
// =============================================================


// ── Red ───────────────────────────────────────────────────────

// Nombre del dispositivo en la red local.
// Acceso web: http://HOSTNAME.local
// También usado como hostname ArduinoOTA.
#define HOSTNAME          "radiocassete"

// Credenciales WiFi de fábrica. Se usan al flashear por primera
// vez o si se borra la NVS. Cambiables después desde Config.
#define FACTORY_SSID      "TU_SSID"
#define FACTORY_PASSWORD  "TU_PASSWORD"

// Punto de acceso propio cuando no hay red WiFi disponible.
#define AP_SSID           "Radiocassete"
#define AP_PASSWORD       "adau1701"

// Contraseña para subir firmware por ArduinoOTA (Arduino IDE WiFi).
#define OTA_PASSWORD      "adau1701"

// Puerto TCP para la comunicación con SigmaStudio (protocolo TCPi).
// Debe coincidir con el configurado en SigmaStudio → USBi Settings.
#define TCP_PORT          8086


// ── GPIO — Pines ESP32 ↔ ADAU1701 ────────────────────────────
// Ajusta según tu PCB. No usar GPIO 6–11 (flash SPI interno).
// Cambiables después desde la pestaña Config de la web. (*)

#define DEFAULT_SCL       17    // I2C Clock
#define DEFAULT_SDA       16    // I2C Data
#define DEFAULT_RESET     21    // ADAU1701 /RESET  (activo en bajo)
#define DEFAULT_SELFBOOT  19    // ADAU1701 SELFBOOT (LOW = esclavo I2C)
#define DEFAULT_LED        2    // LED de estado (GPIO2 = builtin en muchas placas)


// ── DSP — Dirección I2C ───────────────────────────────────────
// Dirección I2C del ADAU1701 según los pines ADDR0/ADDR1:
//   ADDR1=0 ADDR0=0 → 0x34 (más común)
//   ADDR1=0 ADDR0=1 → 0x35
//   ADDR1=1 ADDR0=0 → 0x36
//   ADDR1=1 ADDR0=1 → 0x37
#define DSP_I2C_ADDR      0x34


// ── Posiciones de memoria — Bandas EQ ────────────────────────
// Dirección base del filtro biquad en param RAM del ADAU1701.
// Cada banda ocupa 5 palabras consecutivas (b0, b1, b2, a1, a2).
// Cómo encontrarla: SigmaStudio → columna "Address" del bloque
// de filtro tras hacer Link → Compile.
// Cambiables desde la pestaña Config de la web. (*)

#define EQ_BAND0_ADDR     0x00A7   // Banda 1 — Low Shelf   40 Hz
#define EQ_BAND1_ADDR     0x00AC   // Banda 2 — Bell       100 Hz
#define EQ_BAND2_ADDR     0x00B1   // Banda 3 — Bell       250 Hz
#define EQ_BAND3_ADDR     0x00B6   // Banda 4 — Bell       800 Hz
#define EQ_BAND4_ADDR     0x00BB   // Banda 5 — Bell      2500 Hz
#define EQ_BAND5_ADDR     0x00C0   // Banda 6 — Bell      5000 Hz
#define EQ_BAND6_ADDR     0x00C5   // Banda 7 — Bell     10000 Hz
#define EQ_BAND7_ADDR     0x00CA   // Banda 8 — High Shelf 16 kHz


// ── Posiciones de memoria — Bass Boost ───────────────────────
// Bloque shelving de graves. Busca el bloque en SigmaStudio
// y anota la dirección del primer coeficiente.
// Cambiables desde la pestaña Config de la web. (*)

#define DEFAULT_ADDR_BASS_F   0x000A   // Coeficientes de frecuencia de corte
#define DEFAULT_ADDR_BASS_B   0x0010   // Coeficientes de ganancia (boost)
#define DEFAULT_ADDR_BASS_C   0x0010   // Tabla compression ratio (33 words)

// Valores de fábrica del bass boost (primera vez sin NVS).
#define DEFAULT_BASS_FREQ     40.0f    // Hz  — frecuencia de corte
#define DEFAULT_BASS_BOOST     9.0f    // dB  — ganancia máxima
#define DEFAULT_BASS_COMP     10.0f    // ratio X:1 — compression ratio


// ── Posiciones de memoria — Volumen de entrada ───────────────
// Dirección del coeficiente multiplicador (Single Multiplier)
// en param RAM. Un coeficiente por entrada.
// Cambiables desde la pestaña Config de la web. (*)

#define DEFAULT_ADDR_INVOL_BT    0x0002   // Entrada Bluetooth
#define DEFAULT_ADDR_INVOL_LI    0x0001   // Entrada Line In
#define DEFAULT_ADDR_INVOL_ST    0x0009   // Sine Tone (generador)

// Nivel de volumen de fábrica. 0 dB = sin atenuar ni amplificar.
#define DEFAULT_INVOL_BT         0.0f     // dB  (rango: -30 .. +6)
#define DEFAULT_INVOL_LI         0.0f     // dB  (rango: -30 .. +6)
#define DEFAULT_INVOL_ST         0.0f     // dB  (rango: -30 .. +6)


// ── Posiciones de memoria — VU Meter ─────────────────────────
// Byte offset del bloque ReadBack en program RAM del ADAU1701.
//
// Cómo encontrarlo tras recompilar en SigmaStudio:
//   1. Abre el archivo IC_1_Param.h generado en la carpeta
//      del proyecto SigmaStudio.
//   2. Busca el módulo ReadBack de cada canal (L y R).
//   3. El valor dentro de SIGMASTUDIOTYPE_SPECIAL(0xXXXX)
//      es directamente el byte offset — cópialo aquí.
//
// Cambiables sin recompilar desde la pestaña Config de la web. (*)

#define DEFAULT_ADDR_VU_L    0x0D1E   // ReadBack canal izquierdo (TCPi14)
#define DEFAULT_ADDR_VU_R    0x0D12   // ReadBack canal derecho   (TCPi14)


// ── VU Meter — Ventana de integración de pico ─────────────────
// El ESP32 muestrea el ReadBack del DSP cada 20 ms, acumula el
// máximo de cada canal por separado y publica el pico al navegador
// cada VU_WINDOW_MS milisegundos (~25 muestras a 20 ms).
//
// Valores más bajos → respuesta más rápida (más nerviosa).
// Valores más altos → pico más representativo (más estable).
// Rango recomendado: 300–800 ms.

#define VU_WINDOW_MS   250


// ── Sine Tone — Módulo generador de tono (Autosoner sweep) ────
//
// Para usar el barrido del Autosoner2000 con el ADAU1701:
//
//   1. Abre tu proyecto en SigmaStudio.
//   2. Añade un módulo "Tone (Lookup)" por canal (Tone_L, Tone_R).
//   3. Conéctalo a la salida (a través de un Mux o directo).
//   4. Compila (Link → Compile → Download).
//   5. Usa Sender.html para extraer las direcciones automáticamente,
//      o busca en IC_1_PARAM.h:
//        MOD_TONE_L1_ALG0_MASK_ADDR      → mask (constante 0xFF)
//        MOD_TONE_L1_ALG0_INCREMENT_ADDR → frecuencia (freq/Fs)
//        MOD_TONE_L1_ALG0_ISON_ADDR      → on/off (0x800000/0x000000)
//   6. Graba la EEPROM (Write EEPROM — Selfboot).
//
// Cada módulo Tone (Lookup) tiene 3 parámetros consecutivos:
//   [mask]  → siempre 0x000000FF (constante, escrita al activar)
//   [increment] → freq / Fs en formato 5.23 fixed-point
//   [ison] → 0x00800000 = ON, 0x00000000 = OFF
//
// Cambiables desde la pestaña Config de la web o via Sender.html. (*)

#define SINE_TONE_L_MASK_ADDR  0x0004   // ← RELLENAR (o usar Sender.html)
#define SINE_TONE_L_FREQ_ADDR  0x0005   // ← RELLENAR
#define SINE_TONE_L_ISON_ADDR  0x0006   // ← RELLENAR
#define SINE_TONE_R_MASK_ADDR  0x0001   // ← RELLENAR
#define SINE_TONE_R_FREQ_ADDR  0x0002   // ← RELLENAR
#define SINE_TONE_R_ISON_ADDR  0x0003   // ← RELLENAR
#define SINE_TONE_FS           48000.0f // Sample rate del ADAU1701

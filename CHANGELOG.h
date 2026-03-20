// =============================================================
// CHANGELOG — Historial de versiones del firmware
// =============================================================
// Este archivo se actualiza automáticamente con cada sesión
// de desarrollo. No se compila; es solo documentación.
//
// Formato:  [version] (fecha) — resumen
//           • detalle
//
// =============================================================

// [2.7.0] (2026-03-20)
//   • Mute Line In (ADC): botón en tarjeta Line In, bit 4 del core register 0x081C
//   • Estado lineMuted sincronizado vía SSE en tiempo real
//   • Eliminado botón EQ de la fila de presets (redundante con aislar DSP)
//   • Importador _PARAM.h integrado: carga el archivo de SigmaStudio
//     directamente desde Config, rellena todos los campos automáticamente
//     (reemplaza la necesidad de Sender.html externo)
//   • Corregidas regex del parser (doble escape) y añadidos params faltantes
//     (ivst, Sine Tone L/R)
//
// [2.6.0] (2026-03-20)
//   • Mute general DAC: botón en barra de pestañas con pulsación roja
//   • Escribe directamente al core register 0x081C del ADAU1701 (bit 3)
//   • Estado mute sincronizado vía SSE en tiempo real
//   • Umbral mínimo del mini VU de cabecera bajado a -36 dB
//
// [2.5.0] (2026-03-20)
//   • Sistema completo de backup/restore (.rcbak) con NVS + SPIFFS
//   • Factory Reset extendido: borra NVS + SPIFFS + aísla DSP
//   • DSP Lock: bloquea controles ESP32 pero permite SigmaStudio y EEPROM
//   • Reorganización de pestañas Status / Config / Update
//   • Mini VU vertical con LEDs redondos en la cabecera (siempre visible)
//   • VU Gain movido de Status a Advanced
//   • Fix scroll en goBand() + destello tras scroll
//   • Etiqueta de versión del firmware en UI
//
// [2.4.0] (anterior)
//   • Versión base con EQ 8 bandas, esquemas DSP, presets
//   • Control TCP/SigmaStudio, EEPROM selfboot
//   • VU meter con SSE, sine tone generator
//   • Modo AP + STA, OTA, deep sleep

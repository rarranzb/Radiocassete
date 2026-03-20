# Radiocassete 8 Bandas - Firmware ESP32

Este es el código fuente del firmware para el controlador de audio basado en ESP32 y ADAU1701.

## Guía de Botones y Ajustes

### Botones Físicos
- **BOOT (GPIO 0)**: Pulsación prolongada (>50ms) realiza un **Reset del DSP**. Reinicia el chip ADAU1701 y vuelve a cargar los parámetros del ecualizador y volúmenes guardados.
- **WAKE/SLEEP (GPIO 4)**: 
  - Si el pin está en **ALTO**, se inicia una cuenta atrás de 90 segundos visible en la consola web. Al terminar, el ESP32 entra en modo *Deep Sleep*.
  - Si el pin vuelve a **BAJO** antes de que termine la cuenta atrás, se cancela el apagado.
  - Al despertar del reposo (o encender), el sistema realiza un selfboot del DSP automáticamente.

### Ajustes en la Interfaz Web (radiocassete.local)
- **EQ (Pestaña Principal)**:
  - **Pad XY**: Arrastra el punto para moldear el sonido (Calidez, Brillo, Energía).
  - **Bass Boost**: Ajusta el refuerzo de graves (Frecuencia, Ganancia y Compresión).
  - **Memorias (M1-M5)**: Pulsa para cargar; "Save" + M1-M5 para guardar.
- **Advanced (Ajustes Detallados)**:
  - **Bandas EQ**: Cada una de las 8 bandas se puede ajustar de forma independiente (Frecuencia, Ganancia y Factor Q).
  - **Input Volume**: Volúmenes de Bluetooth, Entrada de Línea y Generador de tonos.
  - **Mute**: Silencia el DAC o la entrada de línea.
- **Status (Estado y Gestión)**:
  - **DSP Lock**: Bloquea los cambios desde la web para proteger el sonido.
  - **Reset DSP**: Fuerza un reinicio completo del DSP por hardware.
  - **Bancos DSP**: Permite alternar entre diferentes esquemas de SigmaStudio guardados.
- **Config**: 
  - Permite cambiar credenciales WiFi, nombre del dispositivo y mapeo de pines GPIO.
  - **Importador Param**: Botón para cargar el archivo `.h` de SigmaStudio y configurar automáticamente todas las direcciones de memoria.

---
Proyecto desarrollado por **robertocreaciones**.

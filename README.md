# Radiocassete 8 Bandas - Firmware ESP32

![Interfaz Ecualizador](screenshots/ui_eq.png)

Este es el código fuente del firmware para el controlador de audio basado en ESP32 y ADAU1701.

![Estado del Sistema](screenshots/ui_status.png)

## Instalación desde el navegador

Puedes flashear el firmware directamente desde **Google Chrome** o **Microsoft Edge** sin necesidad de instalar ningún software:

**[Instalar Firmware](https://rarranzb.github.io/Radiocassete/)**

Solo necesitas conectar el ESP32 por USB y pulsar el botón de instalación.

## Project Status & Support

This project has been developed with the assistance of Artificial Intelligence for logic and coding. While it is fully functional and stable for its intended use, please note the following:

No Expert Support: I am not a DSP or SigmaStudio expert. I will not be able to provide deep technical support, resolve complex bugs, or answer low-level architectural questions.

As-Is Basis: The repository is shared "as-is" as a reference, template, or inspiration for other "restomod" and vintage audio projects.

Contributions: You are welcome to fork the project and improve it, but please do not expect active maintenance or troubleshooting from my side.

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

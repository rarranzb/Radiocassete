// telnet_log.ino — Telnet desactivado (sustituido por consola web)
// logWrite() se mantiene definida aquí para compatibilidad con LOG/LOGLN macros

WiFiClient telnetClient;  // dummy para que no fallen refs en otros .ino

void setupTelnet() {}
void handleTelnet() {}

void logWrite(const char* msg) {
  if (logEnabled) Serial.print(msg);
  // Siempre acumular en buffer circular para consola web
  static char partial[LOG_BUF_LEN];
  static int  plen = 0;
  for (const char* p = msg; *p; p++) {
    if (*p == '\n' || plen >= LOG_BUF_LEN - 1) {
      partial[plen] = '\0';
      strncpy(logBuf[logBufHead], partial, LOG_BUF_LEN - 1);
      logBuf[logBufHead][LOG_BUF_LEN - 1] = '\0';
      logBufHead = (logBufHead + 1) % LOG_BUF_LINES;
      if (logBufCount < LOG_BUF_LINES) logBufCount++;
      plen = 0;
    } else {
      partial[plen++] = *p;
    }
  }
}

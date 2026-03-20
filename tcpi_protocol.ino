// =============================================================
// tcpi_protocol.ino — Protocolo SigmaStudio TCPi
// =============================================================

int processBuffer(uint8_t* buf, int len) {
  int pos = 0;
  while (pos < len) {
    uint8_t ctrl = buf[pos];

    if (ctrl == CTRL_WRITE) {
      if (pos + 10 > len) break;
      uint8_t  safeload = buf[pos + 1];
      uint16_t totalLen = (buf[pos + 3] << 8) | buf[pos + 4];
      uint8_t  chipAddr = buf[pos + 5];
      uint16_t dataLen  = (buf[pos + 6] << 8) | buf[pos + 7];
      uint16_t address  = (buf[pos + 8] << 8) | buf[pos + 9];
      if (pos + totalLen > len) { LOG("[TCP] Frag %d/%d\n", len-pos, totalLen); break; }
      uint8_t* payload  = buf + pos + 10;
      LOG("[W] 0x%04X len=%d sl=%d |", address, dataLen, safeload);
      for (int d = 0; d < min((int)dataLen, 8); d++) LOG(" %02X", payload[d]);
      LOGLN("");
      handleWrite(chipAddr, address, payload, dataLen, safeload);
      pos += totalLen;

    } else if (ctrl == CTRL_READ_REQ) {
      if (pos + 8 > len) break;
      uint16_t totalLen = (buf[pos+1]<<8)|buf[pos+2];
      uint8_t  chipAddr = buf[pos+3];
      uint16_t dataLen  = (buf[pos+4]<<8)|buf[pos+5];
      uint16_t address  = (buf[pos+6]<<8)|buf[pos+7];
      if (pos + totalLen > len) break;
      handleRead(chipAddr, address, dataLen);
      pos += totalLen;

    } else {
      pos++;
    }
  }
  return pos;
}

void handleWrite(uint8_t chipAddr, uint16_t address, uint8_t* data,
                 uint16_t dataLen, uint8_t safeload) {
  bool isDSP      = (chipAddr == 0x01 || chipAddr == dspI2cAddr);
  bool isParamRAM = (address <= PARAM_RAM_END);

  uint8_t i2cAddr = (chipAddr == 0x01) ? dspI2cAddr  :
                    (chipAddr == 0x02) ? EEPROM_I2C_ADDR : chipAddr;

  if (isDSP && safeload == 0 && !captureReady)
    captureWrite(address, data, dataLen);

  if (isDSP && address == 0x081C && dataLen >= 2) {
    lastCoreCtrl[0] = data[dataLen - 2];
    lastCoreCtrl[1] = data[dataLen - 1];
    bool wasRunning = dspRunning;
    dspRunning = (lastCoreCtrl[1] & 0x04) != 0;
    if (!wasRunning && dspRunning) {
      captureReady = true;
      activeRamSource = 99;  // SigmaStudio
      saveActiveSources();
      LOG("[DSP] Running! Capture ready: %d bytes\n", captureLen);
      if (eqEnabled) {
        delay(300);
        LOGLN("[EQ] Recargando bandas al DSP...");
        for (int b = 0; b < EQ_NUM_BANDS; b++) writeEqBand(b);
        updateBassDSP();
      }
    }
  }

  // Segmentación del Safeload gestionada correctamente por la rutina
  if (isDSP && isParamRAM && dspRunning && safeload == 1) {
    int totalWords = dataLen / 4, offset = 0, nChunks = 0;
    while (offset < totalWords) {
      int words = min(totalWords - offset, 5);
      safeloadChunk(address + offset, data + offset * 4, words);
      offset += words; 
      nChunks++;
    }
    LOG("[SAFELOAD] 0x%04X %d words %d ISTs\n", address, totalWords, nChunks);
  } else {
    directWrite(i2cAddr, address, data, dataLen);
  }
}

void safeloadChunk(uint16_t address, uint8_t* data, int words) {
  // 1. Cargar datos en registros
  for (int i = 0; i < words; i++) {
    uint16_t reg = SAFELOAD_DATA_0 + i;
    uint8_t* w   = data + (i * 4);
    Wire.beginTransmission(dspI2cAddr);
    Wire.write((reg>>8)&0xFF); Wire.write(reg&0xFF);
    Wire.write(0x00);
    Wire.write(w[0]); Wire.write(w[1]); Wire.write(w[2]); Wire.write(w[3]);
    Wire.endTransmission(true);
  }
  // 2. Cargar direcciones destino
  for (int i = 0; i < words; i++) {
    uint16_t reg  = SAFELOAD_ADDR_0 + i;
    uint16_t dest = address + i;
    Wire.beginTransmission(dspI2cAddr);
    Wire.write((reg>>8)&0xFF); Wire.write(reg&0xFF);
    Wire.write((dest>>8)&0xFF); Wire.write(dest&0xFF);
    Wire.endTransmission(true);
  }
  // 3. Activar IST
  Wire.beginTransmission(dspI2cAddr);
  Wire.write(0x08); Wire.write(0x1C);
  Wire.write(lastCoreCtrl[0]);
  Wire.write(lastCoreCtrl[1] | IST_BIT);
  Wire.endTransmission(true);

  // LA SOLUCIÓN DE HARDWARE: El ADAU1701 tarda 21 microsegundos en procesar 
  // la orden de safeload. Si no esperamos, el ESP32 sobreescribe los registros 
  // con la siguiente ronda y el DSP pierde las tablas, generando ruido y chasquidos.
  delayMicroseconds(30); 
}

void directWrite(uint8_t i2cAddr, uint16_t regAddr, uint8_t* data, uint16_t dataLen) {
  int wordSize = 4;
  if (regAddr >= PROG_RAM_START && regAddr <= PROG_RAM_END) wordSize = 5;
  else if (regAddr >= CTRL_REG_START) wordSize = 2;

  int chunkBytes = 30 * wordSize, offset = 0;
  while (offset < dataLen) {
    int      bytes = min(dataLen - offset, chunkBytes);
    uint16_t addr  = regAddr + (offset / wordSize);
    Wire.beginTransmission(i2cAddr);
    Wire.write((addr>>8)&0xFF); Wire.write(addr&0xFF);
    Wire.write(data + offset, bytes);
    uint8_t err = Wire.endTransmission(true);
    if (err != 0) {
      LOG("[I2C] ERR 0x%04X len=%d err=%d\n", addr, bytes, err);
      Wire.end(); delay(5);
      Wire.setBufferSize(2048);
      Wire.begin(pinSDA, pinSCL, 400000);
      Wire.setTimeOut(10);
    }
    offset += bytes;
  }
}

void handleRead(uint8_t chipAddr, uint16_t address, uint16_t nBytes) {
  LOG("[READ REQ] chip=0x%02X addr=0x%04X bytes=%d\n", chipAddr, address, nBytes);

  uint8_t i2cAddr = (chipAddr == 0x01) ? dspI2cAddr :
                    (chipAddr == 0x02) ? EEPROM_I2C_ADDR : chipAddr;

  // Lectura I2C
  Wire.beginTransmission(i2cAddr);
  Wire.write((address >> 8) & 0xFF);
  Wire.write(address & 0xFF);
  Wire.endTransmission(false);

  Wire.requestFrom((int)i2cAddr, (int)nBytes, true);

  uint8_t rd[256] = {0};
  int idx = 0;
  while (Wire.available() && idx < (int)nBytes && idx < 256) {
    rd[idx++] = Wire.read();
  }

  // Logging de los primeros bytes que devuelve el DSP (útil para debugging)
  LOG("[READ RSP] %d bytes devueltos: ", idx);
  for (int i = 0; i < min(idx, 8); i++) LOG("%02X ", rd[i]);
  LOGLN("");

  // Respuesta exacta que espera SigmaStudio TCPi
  uint8_t resp[270];
  int sz = 9 + idx;
  resp[0] = CTRL_READ_RESP;           // normalmente 0x03
  resp[1] = (sz >> 8) & 0xFF;
  resp[2] = sz & 0xFF;
  resp[3] = chipAddr;
  resp[4] = (idx >> 8) & 0xFF;
  resp[5] = idx & 0xFF;
  resp[6] = (address >> 8) & 0xFF;
  resp[7] = address & 0xFF;
  resp[8] = 0x01;                     // Status = OK

  memcpy(resp + 9, rd, idx);

  if (client && client.connected()) {
    size_t written = client.write(resp, sz);
    client.flush();                   // ← CRUCIAL para que los meters se actualicen en tiempo real
    LOG("[TCP] Enviados %d bytes (flush)\n", written);
  } else {
    LOG("[TCP] Cliente desconectado, no se envía respuesta\n");
  }
}
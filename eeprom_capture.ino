// =============================================================
// eeprom_capture.ino — Captura SigmaStudio → EEPROM selfboot
// =============================================================

void captureWrite(uint16_t address, uint8_t* data, uint16_t dataLen) {
  int wordSize = 4;
  if (address >= PROG_RAM_START && address <= PROG_RAM_END) wordSize = 5;
  else if (address >= CTRL_REG_START) wordSize = 2;

  int maxWords  = 32;
  int chunkSize = maxWords * wordSize;
  int offset    = 0;

  while (offset < dataLen) {
    int      bytes = min(dataLen - offset, chunkSize);
    uint16_t addr  = address + (offset / wordSize);
    uint8_t* chunk = data + offset;

    int needed = 6 + bytes;
    if (captureLen + needed + 2 > CAPTURE_MAX_SIZE) {
      Serial.println("[CAP] Buffer full, skipping");
      return;
    }

    uint16_t count = bytes + 3;
    captureBuffer[captureLen++] = 0x01;
    captureBuffer[captureLen++] = (count >> 8) & 0xFF;
    captureBuffer[captureLen++] = count & 0xFF;
    captureBuffer[captureLen++] = 0x00;
    captureBuffer[captureLen++] = (addr >> 8) & 0xFF;
    captureBuffer[captureLen++] = addr & 0xFF;
    memcpy(captureBuffer + captureLen, chunk, bytes);
    captureLen += bytes;
    offset     += bytes;
  }
}

bool writeEEPROM() {
  if (captureLen == 0) {
    Serial.println("[EEPROM] Nothing captured");
    return false;
  }
  captureBuffer[captureLen++] = 0x00;
  captureBuffer[captureLen++] = 0x00;

  Serial.printf("[EEPROM] Writing %d bytes to 0x%02X...\n", captureLen, EEPROM_I2C_ADDR);

  int offset = 0;
  while (offset < captureLen) {
    int pageOffset = offset % EEPROM_PAGE_SIZE;
    int bytes      = min(captureLen - offset, EEPROM_PAGE_SIZE - pageOffset);
    if (!eepromWritePage(offset, captureBuffer + offset, bytes)) {
      Serial.printf("[EEPROM] Write failed at offset %d\n", offset);
      return false;
    }
    offset += bytes;
    if (offset % 1024 == 0)
      Serial.printf("[EEPROM] %d / %d bytes\n", offset, captureLen);
  }
  Serial.println("[EEPROM] Done!");
  return true;
}

// ── Leer EEPROM completa por I2C al captureBuffer ──────────
// Lee byte a byte hasta encontrar el terminador 0x00 0x00
// o alcanzar EEPROM_MAX_SIZE. Deja captureReady = true.
bool readEEPROM() {
  Serial.printf("[EEPROM] Leyendo desde 0x%02X...\n", EEPROM_I2C_ADDR);
  captureLen   = 0;
  captureReady = false;

  // Leer en bloques de 32 bytes para mayor velocidad
  const int BLOCK = 32;
  uint8_t   buf[BLOCK];
  int       totalRead = 0;
  bool      foundEnd  = false;

  while (totalRead < EEPROM_MAX_SIZE && totalRead < CAPTURE_MAX_SIZE) {
    uint16_t addr = (uint16_t)totalRead;
    int toRead = min(BLOCK, min(EEPROM_MAX_SIZE - totalRead, CAPTURE_MAX_SIZE - captureLen));

    // Posicionar la dirección de lectura
    Wire.beginTransmission(EEPROM_I2C_ADDR);
    Wire.write((addr >> 8) & 0xFF);
    Wire.write(addr & 0xFF);
    if (Wire.endTransmission(false) != 0) {
      Serial.printf("[EEPROM] I2C error posicionando addr 0x%04X\n", addr);
      return false;
    }

    int got = Wire.requestFrom((uint8_t)EEPROM_I2C_ADDR, (uint8_t)toRead);
    if (got <= 0) {
      Serial.printf("[EEPROM] I2C read error at 0x%04X\n", addr);
      return false;
    }

    for (int i = 0; i < got; i++) {
      uint8_t b = Wire.read();
      captureBuffer[captureLen++] = b;
    }
    totalRead += got;

    // Buscar terminador 0x00 0x00 dentro del selfboot stream
    // El terminador puede aparecer en cualquier posicion tras un record completo
    // Solo buscamos si ya hemos leido al menos unos bytes
    if (captureLen >= 2) {
      // Comprobar si los dos ultimos bytes del buffer total son 0x00 0x00
      // y estamos fuera de un record activo (el byte antes del terminador
      // cierra el ultimo record)
      if (captureBuffer[captureLen - 2] == 0x00 && captureBuffer[captureLen - 1] == 0x00) {
        // Verificar que no estamos en medio de datos validos:
        // recorrer el stream para asegurar integridad
        int pos = 0;
        bool valid = true;
        while (pos < captureLen - 2) {
          if (captureBuffer[pos] == 0x01) {
            uint16_t count = (captureBuffer[pos + 1] << 8) | captureBuffer[pos + 2];
            int recordLen = 3 + count;  // header(1) + count(2) + payload(count)
            if (pos + recordLen > captureLen) { valid = false; break; }
            pos += recordLen;
          } else if (captureBuffer[pos] == 0x00) {
            // Llegamos al terminador en el stream
            foundEnd = true;
            break;
          } else {
            valid = false;
            break;
          }
        }
        if (foundEnd) break;
      }
    }

    if (totalRead % 1024 == 0)
      Serial.printf("[EEPROM] Leidos %d bytes\n", totalRead);
  }

  if (!foundEnd) {
    // No encontramos terminador, pero tenemos datos — puede ser EEPROM llena
    // o sin formato selfboot. Guardamos igualmente lo leido.
    Serial.printf("[EEPROM] Leidos %d bytes (sin terminador encontrado)\n", captureLen);
  }

  // Quitar el terminador 0x00 0x00 del captureLen (writeEEPROM lo añade)
  if (foundEnd && captureLen >= 2) {
    captureLen -= 2;
  }

  captureReady = true;
  Serial.printf("[EEPROM] Lectura completa: %d bytes (captureReady)\n", captureLen);
  return true;
}

bool eepromWritePage(uint16_t memAddr, uint8_t* data, int len) {
  Wire.beginTransmission(EEPROM_I2C_ADDR);
  Wire.write((memAddr >> 8) & 0xFF);
  Wire.write(memAddr & 0xFF);
  Wire.write(data, len);
  uint8_t err = Wire.endTransmission(true);
  if (err != 0) {
    Serial.printf("[EEPROM] I2C err=%d at 0x%04X\n", err, memAddr);
    return false;
  }
  delay(6);
  return true;
}

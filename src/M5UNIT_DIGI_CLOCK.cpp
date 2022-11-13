#include "M5UNIT_DIGI_CLOCK.h"

bool M5UNIT_DIGI_CLOCK::begin(TwoWire *wire, uint8_t sda, uint8_t scl,
                             uint8_t addr) {
    _wire = wire;
    _addr = addr;
    _sda  = sda;
    _scl  = scl;
    _wire->begin((int)_sda, (int)_scl);
    delay(10);
    _wire->beginTransmission((uint8_t) _addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

bool M5UNIT_DIGI_CLOCK::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                                  uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->write(buffer, length);
    if (_wire->endTransmission() == 0) return true;
    return false;
}

bool M5UNIT_DIGI_CLOCK::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                                 uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission();
    if (_wire->requestFrom(addr, length)) {
        for (uint8_t i = 0; i < length; i++) {
            buffer[index++] = _wire->read();
        }
        return true;
    }
    return false;
}

bool M5UNIT_DIGI_CLOCK::setBrightness(uint8_t brightness) {
    return writeBytes(_addr, M5UNIT_DIGI_CLOCK_BRIGHTNESS_REG, &brightness, 1);
}

bool M5UNIT_DIGI_CLOCK::setASCII(char *str) {
    if (strlen(str) > 9) {
        return false;
    }
    return writeBytes(_addr, M5UNIT_DIGI_CLOCK_ASCII_REG, (uint8_t *)str,
                      strlen(str));
}

bool M5UNIT_DIGI_CLOCK::setASCII(uint8_t index, char asicc) {
    return writeBytes(_addr, M5UNIT_DIGI_CLOCK_ASCII_REG + index,
                      (uint8_t *)&asicc, 1);
}

bool M5UNIT_DIGI_CLOCK::setSegments(uint8_t index, uint8_t map) {
    return writeBytes(_addr, M5UNIT_DIGI_CLOCK_NUMBER_REG + index, &map, 1);
};

bool M5UNIT_DIGI_CLOCK::setSegments(uint8_t map1, uint8_t map2, uint8_t map3,
                                   uint8_t map4, bool colon) {
    uint8_t data[5] = {0};
    data[0]         = map1;
    data[1]         = map2;
    data[2]         = colon ? 1 : 0;
    data[3]         = map3;
    data[4]         = map4;
    return writeBytes(_addr, M5UNIT_DIGI_CLOCK_NUMBER_REG, data, 5);
}

bool M5UNIT_DIGI_CLOCK::setString(char *str) {
    if (strlen(str) > 9) {
        return false;
    }
    return writeBytes(_addr, M5UNIT_DIGI_CLOCK_STRING_REG, (uint8_t *)str,
                      strlen(str));
}

uint8_t M5UNIT_DIGI_CLOCK::getVersion() {
    uint8_t data = 0;
    readBytes(_addr, M5UNIT_DIGI_CLOCK_FW_VERSION_REG, &data, 1);
    return data;
}

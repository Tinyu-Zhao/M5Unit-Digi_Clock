#ifndef _M5_DIGITAL_CLOCK_H_
#define _M5_DIGITAL_CLOCK_H_

#include <Arduino.h>
#include <Wire.h>

#define M5_DIGITAL_CLOCK_DEFAULT_ADDR   0x30
#define M5_DIGITAL_CLOCK_NUMBER_REG     0x00
#define M5_DIGITAL_CLOCK_ASCII_REG      0x10
#define M5_DIGITAL_CLOCK_STRING_REG     0x20
#define M5_DIGITAL_CLOCK_BRIGHTNESS_REG 0x30

#define M5_DIGITAL_CLOCK_FW_VERSION_REG 0xFE

class M5_DIGITAL_CLOCK {
   private:
    uint8_t _addr;
    TwoWire *_wire;
    uint8_t _sda;
    uint8_t _scl;
    bool writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    bool readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t sda = 21, uint8_t scl = 22,
               uint8_t addr = M5_DIGITAL_CLOCK_DEFAULT_ADDR);

    bool setBrightness(uint8_t brightness);

    bool setASCII(char *str);
    bool setASCII(uint8_t index, char asicc);
    bool setSegments(uint8_t index, uint8_t map);

    bool setSegments(uint8_t map1, uint8_t map2, uint8_t map3, uint8_t map4,
                     bool colon);

    bool setString(char *str);
    uint8_t getVersion();
};

#endif

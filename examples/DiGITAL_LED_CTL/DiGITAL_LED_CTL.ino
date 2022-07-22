
#include <M5Stack.h>
#include "M5_DIGITAL_CLOCK.h"

M5_DIGITAL_CLOCK unit;

void setup() {
    M5.begin();  // Init M5Stack.  初始化M5Stack
    while (!unit.begin(&Wire, 21, 22, M5_DIGITAL_CLOCK_DEFAULT_ADDR)) {
        Serial.println("M5 DIGITAL CLOCK INIT ERROR");
        M5.Lcd.println("M5 DIGITAL CLOCK INIT ERROR");
        delay(1000);
    };
    Serial.println("M5 DIGITAL CLOCK INIT SUCCESS");
    unit.setBrightness(8);
    unit.setASCII("a.b.:c.d.");
    // unit.setASCII(0, "a");
}

void loop() {
    bool status = false;
    for (uint8_t i = 0; i < 8; i++) {
        status = !status;
        unit.setSegments(1 << i, 1 << i, 1 << i, 1 << i, status);
        delay(150);
    }

    unit.setString("12:34");
    delay(500);
    unit.setString("ab:cd");
    delay(500);

    unit.setSegments(0xff, 0xff, 0xff, 0xff, true);

    for (uint8_t i = 8; i > 0; i--) {
        unit.setBrightness(i);
        delay(50);
    }
    for (uint8_t i = 0; i < 9; i++) {
        unit.setBrightness(i);
        delay(50);
    }

    // unit.setString("ab:cd");
    // delay(1000);
    // unit.setString("-3.14");
    // delay(1000);
    // unit.setString("1.2.:3.4.");
    // delay(1000);
    // unit.setString("0003");
    // delay(1000);
    // unit.setString("3.141");
    // delay(1000);
    // unit.setString("3.ab.1");
    // delay(1000);
}

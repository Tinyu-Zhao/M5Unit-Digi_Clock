#include "M5Stack.h"
#include "M5_DIGITAL_CLOCK.h"

M5_DIGITAL_CLOCK Digiclock;

void setup() {
    M5.begin(1, 0, 1);
    M5.dis.fillpix(0XFFFFFF);
    delay(50);
    M5.dis.fillpix(0X000000);
    delay(500);

    /* Digital clock init */
    if (Digiclock.begin(&Wire, 26, 32)) {
        Serial.println("Digital clock init successful");
        M5.dis.fillpix(0x00FF00);
    } else {
        Serial.println("Digital clock init error");
        M5.dis.fillpix(0XFF0000);
        while (1);
    }
    char buff[] = "    ";
    Digiclock.setString(buff);
    delay(2000);
}

void loop() {
        char buff[] = "8.8.:8.8.";
    Digiclock.setString(buff);

    for (int i = 0; i < 5; i++) {
        Digiclock.setBrightness(9);
        delay(150);
        Digiclock.setBrightness(0);
        delay(150);
    }
    delay(100);

    for (int i = 0; i < 4; i++) {
        for (uint8_t i = 0; i < 9; i++) {
            Digiclock.setBrightness(i);
            delay(20);
        }
        for (uint8_t i = 8; i > 0; i--) {
            Digiclock.setBrightness(i);
            delay(20);
        }
    }
    delay(100);

    Digiclock.setBrightness(9);
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 10; i++) {
            sprintf(buff, "%d.%d.:%d.%d.", i, i, i, i);
            Digiclock.setString(buff);
            Serial.println(buff);
            delay(200);
        }
    }
    delay(500);
}


#include "Wire.h"
#include "M5UNIT_DIGI_CLOCK.h"

/* For M5Stack Basic */
#define SDA 21
#define SCL 22

/* For M5Atom Lite/Matrix */
// #define SDA 26
// #define SCL 32

M5UNIT_DIGI_CLOCK Digiclock;

void setup() 
{
    delay(2000);
    Serial.begin(115200);
    Wire.begin(SDA, SCL);

    /* Digital clock init */
    if (Digiclock.begin(&Wire, SDA, SCL)) 
    {
        Serial.println("Digital clock init successful");
    } 
    else 
    {
        Serial.println("Digital clock init error");
        while (1);
    }
    char buff[] = "    ";
    Digiclock.setString(buff);
    delay(2000);
}

void loop() 
{
    char buff[] = "8.8.:8.8.";
    Digiclock.setString(buff);

    for (int i = 0; i < 5; i++) 
    {
        Digiclock.setBrightness(9);
        delay(150);
        Digiclock.setBrightness(0);
        delay(150);
    }
    delay(100);

    for (int i = 0; i < 4; i++) 
    {
        for (uint8_t i = 0; i < 9; i++) 
        {
            Digiclock.setBrightness(i);
            delay(20);
        }
        for (uint8_t i = 8; i > 0; i--) 
        {
            Digiclock.setBrightness(i);
            delay(20);
        }
    }
    delay(100);

    Digiclock.setBrightness(9);
    for (int j = 0; j < 3; j++) 
    {
        for (int i = 0; i < 10; i++) 
        {
            sprintf(buff, "%d.%d.:%d.%d.", i, i, i, i);
            Digiclock.setString(buff);
            Serial.println(buff);
            delay(200);
        }
    }
    delay(100);

    Digiclock.setBrightness(9);
    for (;;) 
    {
        char *buff2 = "12:00";
        Digiclock.setString(buff2);
        Serial.println(buff2);
        delay(1000);
        char *buff3 = "1200";
        Digiclock.setString(buff3);
        Serial.println(buff3);
        delay(1000);
    }
    delay(100);
}

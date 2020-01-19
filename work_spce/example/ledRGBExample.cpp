#include <Arduino.h>
#include "HCRL_Edu.h"

HCRL_Edu hcrl;

void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.LedRGB.begin();

    hcrl.LedRGB.setBrightness(10);
}

void loop()
{
    for (int i = 0; i < 3; i++)
    {
        hcrl.LedRGB.setPixelsColor(i, random(255), random(255), random(255));
    }
    randomSeed(millis());
    hcrl.update(); //Update Data
}
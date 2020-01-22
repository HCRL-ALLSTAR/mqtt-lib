#include <Arduino.h>
#include "HCRL_EDU.h"

HCRL_EDU hcrl;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.RGB_STRIP.begin();
    hcrl.RGB_STRIP.setBrightness(10);
}

void loop()
{
    for (int i = 0; i < 10; i++)
    {
        hcrl.RGB_STRIP.setPixelsColor(i, random(255), random(255), random(255));
    }
    randomSeed(millis());
    hcrl.update(); //Update Data
}
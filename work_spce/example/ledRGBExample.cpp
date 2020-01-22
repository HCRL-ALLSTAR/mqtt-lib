#include <Arduino.h>
#include "HCRL_EDU.h"
millisDelay ledRand;
HCRL_EDU hcrl;

void setup()
{
    Serial.begin(115200);

    hcrl.RGB_LED.begin();
    hcrl.RGB_LED.setBrightness(50);

    hcrl.RGB_STRIP.begin();
    hcrl.RGB_STRIP.setBrightness(255);
}

void loop()
{
    if (ledRand.justFinished())
    {
        for (int i = 0; i < RGB_LED_PIXELS; i++)
        {
            hcrl.RGB_LED.setPixelsColor(i, random(255), random(255), random(255));
        }
        for (int i = 0; i < RGB_STRIP_PIXELS; i++)
        {
            hcrl.RGB_STRIP.setPixelsColor(i, random(255), random(255), random(255));
        }
        ledRand.repeat();
    }
    hcrl.update();
}
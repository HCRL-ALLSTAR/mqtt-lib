#include <Arduino.h>
#include "HCRL_Edu.h"

HCRL_Edu hcrl;

void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.baterry.begin();
}

void loop()
{
    Sprintln("Current Battery : " + String(hcrl.baterry.getLevel()));
    hcrl.update(); //Update Data
}
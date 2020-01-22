#include <Arduino.h>
#include "HCRL_EDU.h"

HCRL_EDU hcrl;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.ANGLE.begin();
}

void loop()
{
    //print details
    Sprintln("Current ANGLE : " + String(hcrl.ANGLE.getValue()));
    hcrl.update();
}
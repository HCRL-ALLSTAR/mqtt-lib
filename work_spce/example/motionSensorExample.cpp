#include <Arduino.h>
#include "HCRL_EDU.h"

HCRL_EDU hcrl;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.MOTION.begin();
}

void loop()
{
    //print details
    Sprintln("Current Angle : " + String(hcrl.MOTION.getValue()));
    hcrl.update();
}
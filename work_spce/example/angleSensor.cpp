#include <Arduino.h>
#include "HCRL_Edu.h"

HCRL_Edu hcrl;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.Angle.begin();
}

void loop()
{
    //print details
    Sprintln("Current Angle : " + String(hcrl.Angle.getValue()));
    hcrl.update();
}
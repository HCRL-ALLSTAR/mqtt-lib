
#include <Arduino.h>
#include "HCRL_Edu.h"

HCRL_Edu hcrl;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.ENV.Begin();

    //print Details
    Sprintln("Temperature : " + String(hcrl.ENV.GetTemp()));
    Sprintln("Humidity : " + String(hcrl.ENV.GetHumi()));
    Sprintln("Pressure : " + String(hcrl.ENV.GetPressure()));
}

void loop()
{
    hcrl.Update();
}
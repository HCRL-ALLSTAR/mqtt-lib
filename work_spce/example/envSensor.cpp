
#include <Arduino.h>
#include "HCRL_Edu.h"

HCRL_Edu hcrl;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.ENV.begin();
}

void loop()
{
    //print Details
    Sprintln("Temperature : " + String(hcrl.ENV.getTemp()));
    Sprintln("Humidity : " + String(hcrl.ENV.getHumi()));
    Sprintln("Pressure : " + String(hcrl.ENV.getPressure()));
    hcrl.update();
}

#include <Arduino.h>
#include "HCRL_Edu.h"

HCRL_Edu hcrl;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.WiFi.Begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS); //Begin WiFi Connect
}

void loop()
{
    hcrl.Update();
}
#include <Arduino.h>
#include "HCRL_EDU.h"

HCRL_EDU hcrl;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.WiFi.begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS); //Begin WiFi Connect
    //print wifi Details
    Sprintln("WiFi SSID : " + String(hcrl.WiFi.getSSID()));
    Sprintln("WiFi Status : " + String(hcrl.WiFi.getStatus()));
}

void loop()
{
    hcrl.update();
}
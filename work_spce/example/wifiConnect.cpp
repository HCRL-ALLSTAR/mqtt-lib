
#include <Arduino.h>
#include "HCRL_Edu.h"

HCRL_Edu hcrl;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.WiFi.Begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS); //Begin WiFi Connect
    //print wifi Details
    Sprintln("WiFi SSID : " + String(hcrl.WiFi.getSSID()));
    Sprintln("WiFi Password : " + String(hcrl.WiFi.getPASSWORD()));
    Sprintln("WiFi Status : " + String(hcrl.WiFi.getStatus()));
}

void loop()
{
    hcrl.update();
}
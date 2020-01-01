#include <Arduino.h>
#include "System/SystemDefaults.hpp"
#include "WiFi/WiFiWrapper/WiFiWrapper.h"

WiFiWrapper myWiFI;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    myWiFI.Begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS);
}

void loop()
{
}
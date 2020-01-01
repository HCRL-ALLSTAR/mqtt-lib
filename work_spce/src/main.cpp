#include <Arduino.h>
#include "System/SystemDefaults.hpp"
#include "WiFi/WiFiTask.h"

WiFiTask wifiTask;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    wifiTask.Begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS);
}

void loop()
{
    TaskDelay(delay_Time);
}
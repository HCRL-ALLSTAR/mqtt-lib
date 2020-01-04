#include <Arduino.h>
#include "HCRL_Edu.h"

HCRL_Edu edu;
void callback(char *Topic, byte *Paylaod, unsigned int Length)
{
    Paylaod[Length] = '\0';
    String topic_str = Topic, payload_str = (char *)Paylaod;
    //Serial.println("[" + topic_str + "]: " + payload_str);
}

void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    edu.LedRGB.Begin();
    edu.StripRGB.Begin();
    //edu.ENV.Begin();
    //edu.Motion.Begin();
    // edu.Angle.Begin();
    // edu.WiFi.Begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS);
    // edu.MQTT.Begin(HCRL_MQTT_SERVER, HCRL_MQTT_PORT, callback);
    // edu.MQTT.StartSubscribe("/Test");
    // edu.MQTT.StartSubscribe("/Test3");
    // edu.MQTT.StartSubscribe("/Test4");
    // edu.MQTT.PrintSubscribeTopic();
    randomSeed(millis());
}

void loop()
{
    for (int i = 0; i < 10; i++)
    {
        edu.StripRGB.setPixelsColor(i, random(255), random(255), random(255));
    }

    edu.LedRGB.setPixelsColor(0, random(255), random(255), random(255));
    edu.LedRGB.setPixelsColor(1, random(255), random(255), random(255));
    edu.LedRGB.setPixelsColor(2, random(255), random(255), random(255));
    // Sprintln(String(edu.ENV.GetHumi()));
    // Sprintln(String(edu.ENV.GetTemp()));
    // Sprintln(String(edu.ENV.GetPressure()));
    // //Sprintln(String(edu.Motion.GetValue()));
    // Sprintln(String(edu.Angle.GetValue()));
    // Sprintln("===========================");

    TaskDelay(1000);
}
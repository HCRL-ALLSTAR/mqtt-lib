#include <Arduino.h>
#include "HCRL_EDU.h"

millisDelay pubDelay;

HCRL_EDU hcrl;
// Default Callback Function
void callback(char *Topic, byte *Paylaod, unsigned int Length)
{
    Paylaod[Length] = '\0';
    String topic_str = Topic, payload_str = (char *)Paylaod;
    Serial.println("[" + topic_str + "]: " + payload_str);
}

void setup()
{
    Serial.begin(115200);
    hcrl.WiFi.begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS);
    hcrl.MQTT.begin(HCRL_MQTT_SERVER, HCRL_MQTT_PORT, callback);
    hcrl.MQTT.startSubscribe("/test");

    //Get Status
    Sprintln("WiFi SSID : " + String(hcrl.WiFi.getSSID()));
    Sprintln("WiFi Status : " + String(hcrl.WiFi.getStatus()));

    Sprintln("MQTT Server : " + String(hcrl.MQTT.getServer()));
    Sprintln("MQTT Port : " + String(hcrl.MQTT.getPort()));
    Sprintln("MQTT Username : " + String(hcrl.MQTT.getUsername()));
    Sprintln("MQTT Status : " + String(hcrl.MQTT.getStatus()));

    pubDelay.start(Sec2MS(3));
}

void loop()
{
    if (pubDelay.justFinished())
    {
        hcrl.MQTT.publish("/testPub", "Hello world");
        pubDelay.repeat();
    }
    hcrl.update();
}

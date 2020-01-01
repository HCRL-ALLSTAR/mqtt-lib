/*#include <Arduino.h>
#include "System/SystemDefaults.hpp"
#include "System/SystemMacros.hpp"
#include "WiFi/WiFiTask.h"
#include "MQTT/MqttTask.h"
#include "MQTT/MqttWrapper/MqttWrapper.h"

MqttTask mqttTask;
WiFiTask wifiTask;

void callback(char *Topic, byte *Paylaod, unsigned int Length)
{
    Paylaod[Length] = '\0';
    String topic_str = Topic, payload_str = (char *)Paylaod;
    Serial.println("[" + topic_str + "]: " + payload_str);
}

void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    wifiTask.Begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS);
    mqttTask.Begin(HCRL_MQTT_SERVER, HCRL_MQTT_PORT, callback);
    mqttTask.Subscribe("/Test");
}

void loop()
{
    TaskDelay(delay_Time);
}
*/

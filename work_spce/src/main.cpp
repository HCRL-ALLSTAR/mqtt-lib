#include <Arduino.h>
#include "System/SystemDefaults.hpp"
#include "System/SystemMacros.hpp"
#include "MQTT/MqttWrapper/MqttWrapper.h"
#include "WiFi/WiFiWrapper/WiFiWrapper.h"
MqttWrapper wrapper;
WiFiWrapper wifiWrapper;

void callback(char *Topic, byte *Paylaod, unsigned int Length)
{
    Paylaod[Length] = '\0';
    String topic_str = Topic, payload_str = (char *)Paylaod;
    Serial.println("[" + topic_str + "]: " + payload_str);
}

void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    wifiWrapper.Begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS);
    wrapper.Begin(HCRL_MQTT_SERVER, HCRL_MQTT_PORT, callback);
    wrapper.Subscribe("/Test");
    wrapper.Subscribe("/Test2");
    wrapper.PrintTopic();
}

void loop()
{
    wrapper.Update();
}
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

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <WiFi.h>

#include "WiFi/WiFiTask.h"
#include "WiFi/WiFiWrapper/WiFiWrapper.h"
#include "MQTT/MqttWrapper/MqttWrapper.h"
#include "System/SystemDefaults.hpp"
#include "System/SystemMacros.hpp"

WiFiClient client;
PubSubClient mqtt(client);
WiFiTask wifi;
MqttWrapper<PubSubClient> wrapper(&mqtt);

void callback(char *Topic, byte *Paylaod, unsigned int Length)
{
    Paylaod[Length] = '\0';
    String topic_str = Topic, payload_str = (char *)Paylaod;
    Serial.println("[" + topic_str + "]: " + payload_str);
}

void UpdateCode(void *pv)
{
    for (;;)
    {
        wrapper.Update();
        TaskDelay(delay_Time);
    }
}

void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    wifi.Begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS);
    wrapper.Begin(HCRL_MQTT_SERVER, HCRL_MQTT_PORT, callback);
    xTaskCreate(UpdateCode, "Update code", Default_Task_Stack, NULL, 1, NULL);
}

void loop()
{

    // TaskDelay(1000);
}
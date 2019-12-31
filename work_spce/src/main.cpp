#include <TASK_LIB.h>
#include "Default_Value/Default_Value.hpp"
TASK_LIB myTask;
char list[512];

void callback(char *topic, byte *payload, unsigned int length)
{
    payload[length] = '\0';
    String topic_str = topic, payload_str = (char *)payload;
    Serial.println("[" + topic_str + "]: " + payload_str);
}
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    myTask.WiFi.Begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS);
    myTask.MQTT.Begin(HCRL_MQTT_SERVER, HCRL_MQTT_PORT, callback);
    myTask.MQTT.Subscribe("Test");
}
void loop()
{

    TaskDelay(delay_Time);
}
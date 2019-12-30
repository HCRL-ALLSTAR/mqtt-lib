#include "wifiWrapper.hpp"
#include "mqttWrapper.hpp"
#include <WiFi.h>
#include <Arduino.h>
#include <PubSubClient.h>
#define Topic_SUB "/Test1"
#define Topic_PUB "/Test2"

#define mqttServer "161.246.6.147"
#define mqttPort 1883
#define SSID "HCRL-Edu"
#define PASSWORD "Hybrid-6Zero7"

WiFiClient client;
PubSubClient mqtt(client);

void callBack(char *topic, byte *payload, unsigned int length)
{
  // Print the topic
  Serial.print("Topic: ");
  Serial.println(topic);

  // Print the message
  Serial.print("Message: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print(char(payload[i]));
  }

  // Print a newline
  Serial.println("");
}
String topic_list[100];
void setup()
{
  Serial.begin(115200);
  wifiBegin(&WiFi, SSID, PASSWORD);
  mqttBegin(&mqtt, mqttServer, mqttPort, callBack);
  addTopic(topic_list, Topic_SUB);
  Serial.println(topic_list[0]);
}

void loop()
{
  mqtt_loop(&mqtt, topic_list);
}
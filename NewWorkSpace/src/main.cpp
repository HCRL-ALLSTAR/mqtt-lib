#include <Arduino.h>
#include <WiFiClient.h>
#include "PubSubClient.h"
#include "mqttWrapper.hpp"
#define Server "161.246.6.147"
#define Port 1883
#define SSID "HCRL-Edu"
#define PASS "Hybrid-6Zero7"

WiFiClient client;
PubSubClient mqtt(client);

void callback(char *Topic, byte *Paylaod, unsigned int Length)
{
  Paylaod[Length] = '\0';
  String topic_str = Topic, payload_str = (char *)Paylaod;
}

void setup()
{
  Serial.begin(115200);
  MqttBegin(&mqtt, Server, Port, callback);
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}
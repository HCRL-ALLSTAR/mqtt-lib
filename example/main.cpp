#include <M5Stack.h>
#include <Arduino.h>
#include <mqttWraper.hpp>

#define SSID "DrZin"
#define Password "0985626152a"
#define Server "192.168.43.150"
#define Port 1883
#define newTopic "news"
#define newTopic2 "news2"
#define newTopic3 "news3"


void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  wifi_begin(SSID, Password);
  mqtt_begin(Server, Port, callback);
  addTopic(newTopic);
  addTopic(newTopic2);
  addTopic(newTopic3);
  print_topic_list();
}

void loop()
{
  mqtt_loop();
  
}
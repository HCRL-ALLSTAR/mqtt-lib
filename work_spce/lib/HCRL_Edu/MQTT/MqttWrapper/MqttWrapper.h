
#ifndef MQTT_WRAPPER_H
#define MQTT_WRAPPER_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

#include "System/SystemDefaults.hpp"
#include "System/SystemMacros.hpp"

class MqttWrapper
{
private:
    WiFiClient client;
    PubSubClient mqtt;

    String TopicList[100];
    char *MqttServer;
    int MqttPort;

public:
    MqttWrapper(/* args */);
    ~MqttWrapper();
    void Begin(const char *MqttServer, int MqttPort, MQTT_CALLBACK_SIGNATURE);
    void Reconnect();
    void Update();
    void Publish(const char *Topic, const char *Payload);
    void Subscribe(const char *Topic);
    void PrintTopic();
};

MqttWrapper::MqttWrapper(/* args */)
{
    this->mqtt = PubSubClient(this->client);
}

MqttWrapper::~MqttWrapper()
{
}

void MqttWrapper::Begin(const char *MqttServer, int MqttPort, MQTT_CALLBACK_SIGNATURE)
{
    this->MqttServer = (char *)MqttServer;
    this->MqttPort = MqttPort;
    this->mqtt.setServer(this->MqttServer, this->MqttPort);
    this->mqtt.setCallback(callback);
    Sprintln("MQTT Init Complete ");
}
void MqttWrapper::Reconnect()
{
    int idx = 0;
    while (!this->mqtt.connected())
    {
        Sprintln("Attempting MQTT connection...");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (this->mqtt.connect(clientId.c_str()))
        {
            Sprintln("Connected");
            this->mqtt.publish("start", "Hello world");
            this->mqtt.subscribe("intopic");
            while (this->TopicList[idx].length() != 0)
            {
                char buffer[512];
                this->TopicList[idx].toCharArray(buffer, TopicList[idx].length() + 1);
                this->mqtt.subscribe(buffer);
                Sprintln("Start Subscribe =>" + String(buffer));
                idx++;
            }
        }
        else
        {
            Sprint("failed, rc=");
            Sprint(this->mqtt.state());

            delay(100);
        }
    }
}
void MqttWrapper::Update()
{
    if (!this->mqtt.connected())
    {
        this->Reconnect();
    }
    this->mqtt.loop();
}
void MqttWrapper::Publish(const char *Topic, const char *Payload)
{
    if (!this->mqtt.connected())
    {
        this->Reconnect();
    }
    this->mqtt.publish(Topic, Payload);
}
void MqttWrapper::Subscribe(const char *Topic)
{
    boolean isAdded = false;
    int idx = 0;
    while (!isAdded)
    {
        if (this->TopicList[idx].length() == 0)
        {
            this->TopicList[idx] = Topic;
            isAdded = !isAdded;
        }
        else
        {
            idx++;
        }
    }
    Sprintln("Topic Added : " + String(this->TopicList[idx]));
}
void MqttWrapper::PrintTopic()
{
    int idx = 0;
    while (this->TopicList[idx] != '\0')
    {
        Sprintln(String(idx) + " : " + TopicList[idx]);
        idx++;
    }
}

#endif
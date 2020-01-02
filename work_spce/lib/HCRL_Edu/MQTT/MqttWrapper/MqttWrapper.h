#ifndef MQTT_WRAPPER_H
#define MQTT_WRAPPER_H
#include <Arduino.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "System/SystemDefaults.hpp"
#include "System/SystemMacros.hpp"

class MqttWrapper
{
private:
    WiFiClient client;
    PubSubClient mqtt;

    String SubscribeTopic[MAX_LIST_SIZE];
    String PublishTopic[MAX_LIST_SIZE];

    char *Server;
    int Port;

public:
    MqttWrapper(/* args */);
    ~MqttWrapper();
    void Begin(const char *Server, int Port, MQTT_CALLBACK_SIGNATURE);
    void StartSubscribe(const char *Topic);
    void Publish(const char *Topic, const char *Payload);
    void ReConnect();
    void Update();
    void PrintSubscribeTopic();
    void PrintPublishTopic();
};

MqttWrapper::MqttWrapper(/* args */)
{
    this->mqtt = PubSubClient(client);
}

MqttWrapper::~MqttWrapper()
{
}

void MqttWrapper::Begin(const char *Server, int Port, MQTT_CALLBACK_SIGNATURE)
{
    this->Server = (char *)Server;
    this->Port = Port;

    this->mqtt.setServer(this->Server, this->Port);
    this->mqtt.setCallback(callback);
}

void MqttWrapper::StartSubscribe(const char *Topic)
{
    boolean isAdded = false;
    int Index = 0;
    while (!isAdded)
    {
        if (this->SubscribeTopic[Index].length() == 0)
        {
            this->SubscribeTopic[Index] = Topic;
            isAdded = !isAdded;
        }
        else
        {
            Index++;
        }
    }
    Sprintln(String(this->SubscribeTopic[Index]) + "Added");
}

void MqttWrapper::Publish(const char *Topic, const char *Payload)
{
    this->mqtt.publish(Topic, Payload);
}

void MqttWrapper::ReConnect()
{
    int Index = 0;
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

            while (this->SubscribeTopic[Index].length() != 0)
            {
                char buffer[512];
                this->SubscribeTopic[Index].toCharArray(buffer, SubscribeTopic[Index].length() + 1);
                this->mqtt.subscribe(buffer);
                Sprintln("Start Subscribe =>" + String(buffer));
                Index++;
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
        this->ReConnect();
    }
    this->mqtt.loop();
}

void MqttWrapper::PrintSubscribeTopic()
{
}

void MqttWrapper::PrintPublishTopic()
{
}

/*
template <class H>
class MqttWrapper
{
private:
    H *host;
    String SubTopicList[100];

public:
    MqttWrapper(H *host) { this->host = host; }
    ~MqttWrapper() {}
    void Begin(const char *Server, int Port, MQTT_CALLBACK_SIGNATURE);
    void Reconnect();
    void Update();
    void Subscribe(const char *Topic);
    void Publish(const char *Topic, const char *Payload);
    bool isConnect();
};

template <class H>
void MqttWrapper<H>::Begin(const char *Server, int Port, MQTT_CALLBACK_SIGNATURE)
{
    this->host->setServer(Server, Port);
    this->host->setCallback(callback);
}

template <class H>
void MqttWrapper<H>::Reconnect()
{
    int Index = 0;
    while (!this->host->connected())
    {
        Sprintln("Attempting MQTT connection...");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);

        if (this->host->connect(clientId.c_str()))
        {
            Sprintln("Connected");

            this->host->publish("start", "Hello world");
            this->host->subscribe("intopic");

            while (this->SubTopicList[Index].length() != 0)
            {
                char buffer[512];
                this->SubTopicList[Index].toCharArray(buffer, SubTopicList[Index].length() + 1);
                this->host->subscribe(buffer);
                Sprintln("Start Subscribe =>" + String(buffer));
                Index++;
            }
        }
        else
        {
            Sprint("failed, rc=");
            Sprint(this->host->state());
            delay(100);
        }
    }
}

template <class H>
void MqttWrapper<H>::Update()
{
    if (!this->host->connected())
    {
        this->Reconnect();
    }
    this->host->loop();
}

template <class H>
void MqttWrapper<H>::Subscribe(const char *Topic)
{
    boolean isAdded = false;
    int Index = 0;
    while (!isAdded)
    {
        if (this->SubTopicList[Index].length() == 0)
        {
            this->SubTopicList[Index] = Topic;
            isAdded = !isAdded;
        }
        else
        {
            Index++;
        }
    }
    Sprintln("Topic Added : " + String(this->SubTopicList[Index]));
}

template <class H>
void MqttWrapper<H>::Publish(const char *Topic, const char *Payload)
{
    this->host->publish(Topic, Payload);
}

template <class H>
bool MqttWrapper<H>::isConnect()
{
    return this->host->connected();
}
*/
#endif
#ifndef MQTT_WRAPPER_H
#define MQTT_WRAPPER_H

#include <Arduino.h>
#include "PubSubClient/PubSubClient.h"
#include "MyMacros.hpp"
void PrintTopic(String *TopicList)
{
    int Index = 0;
    while (TopicList[Index].length() != 0)
    {
        Sprintln(String(Index) + " : " + String(TopicList[Index]));
        Index += 1;
    }
}

void AddTopic(String *TopicList, const char *Topic)
{
    int Index = 0;
    boolean isAdded = false;
    while (!isAdded)
    {
        if (!TopicList[Index].equals(Topic))
        {
            if (TopicList[Index].length() == 0)
            {
                TopicList[Index] = Topic;
                isAdded = !isAdded;
                Sprintln("Topic Added : " + String(TopicList[Index]));
            }
            else
            {
                Index += 1;
            }
        }
        else
        {
            break;
        }
    }
}

template <typename H>
void MqttBegin(H *Host, const char *Server, int Port, MQTT_CALLBACK_SIGNATURE)
{
    Host->setServer(Server, Port);
    Host->setCallback(callback);
}

template <typename H>
void MqttReconnect(H *Host, String *TopicList)
{
    int Index = 0;
    while (!Host->connected())
    {
        Sprintln("Attempting MQTT connection...");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (Host->connect(clientId.c_str()))
        {
            Sprintln("Connected");

            Host->publish("start", "Hello world");
            Host->subscribe("intopic");

            while (TopicList[Index].length() != 0)
            {
                char buffer[512];
                TopicList[Index].toCharArray(buffer, TopicList[Index].length() + 1);
                Host->subscribe(buffer);
                Sprintln("Start Subscribe =>" + String(buffer));
                Index++;
            }
        }
        else
        {
            Sprint("failed, rc=");
            Sprint(Host->state());
            delay(100);
        }
    }
}
template <typename H>
void MqttConnected(H *Host)
{
    Host->connected();
}

template <typename H>
void MqttLoop(H *Host, String *TopicList)
{
    if (!Host->connected())
    {
        MqttReconnect(Host, TopicList);
    }
    Host->loop();
}

template <typename H>
void MqttPublish(H *Host, const char *Topic, const char *Payload)
{
    Host->publish(Topic, Payload);
}
#endif
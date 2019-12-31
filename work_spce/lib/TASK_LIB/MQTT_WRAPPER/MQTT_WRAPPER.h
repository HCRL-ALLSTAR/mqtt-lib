#ifndef MQTT_WRAPPER_H
#define MQTT_WRAPPER_H
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include "Macro_Functions/Macro_Functions.hpp"

class MQTT_WRAPPER
{
private:
    WiFiClient client;
    PubSubClient mqtt;
    TaskHandle_t Subscribe_Handle;

    char *mqttServer;
    int mqttPort;
    char *currentTopic;
    String topicList[100];

    static void Subscribe_code(void *);

public:
    MQTT_WRAPPER(/* args */);
    ~MQTT_WRAPPER();
    void Begin(const char *mqttServer, int mqttPort, MQTT_CALLBACK_SIGNATURE); //Implement FreeRTOS
    void Subscribe(const char *topic);                                         //Implement FreeRtos with Delete Task
    void Publish(const char *topic, char *payload);                            //Implement FreeRtos with Delete Task
    void PrintTopic();                                                         //Implement FreeRtos with Delete Task
    void Update();                                                             // Implement FreeRTOS
};

MQTT_WRAPPER::MQTT_WRAPPER(/* args */)
{
    this->mqtt = PubSubClient(this->client);
}

MQTT_WRAPPER::~MQTT_WRAPPER()
{
}

void MQTT_WRAPPER::Begin(const char *mqttServer, int mqttPort, MQTT_CALLBACK_SIGNATURE)
{
    this->mqttServer = (char *)mqttServer;
    this->mqttPort = mqttPort;
    this->mqtt.setServer(this->mqttServer, this->mqttPort);
    this->mqtt.setCallback(callback);
}

void MQTT_WRAPPER::Subscribe(const char *topic)
{
    this->currentTopic = (char *)topic;
    xTaskCreate(Subscribe_code, "Subscribe Task", 1048, this, 2, &Subscribe_Handle);
}

void MQTT_WRAPPER::Subscribe_code(void *_this)
{
    MQTT_WRAPPER task = *(MQTT_WRAPPER *)(_this);
    boolean isAdded = false;
    int idx = 0;
    while (!isAdded)
    {
        if (task.topicList[idx].length() == 0)
        {
            task.topicList[idx] = task.currentTopic;
            isAdded = !isAdded;
        }
        else
        {
            idx++;
        }
    }
    vTaskDelete(task.Subscribe_Handle);
    for (;;)
    {
        TaskDelay(delay_Time);
    }
}
#endif

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
    TaskHandle_t Publish_Handle;
    TaskHandle_t Update_Handle;

    char *curPubTopic;
    char *curPayload;
    char *currentTopic;
    char *mqttServer;
    int mqttPort;
    String topicList[100];

    static void Subscribe_code(void *);
    static void Publis_code(void *);
    static void update_code(void *);
    void reConnect();

public:
    MQTT_WRAPPER(/* args */);
    ~MQTT_WRAPPER();
    void Begin(const char *mqttServer, int mqttPort, MQTT_CALLBACK_SIGNATURE); //Implement FreeRTOS
    void Subscribe(const char *topic);                                         //Implement FreeRtos with Delete Task
    void Publish(const char *topic, char *payload);                            //Implement FreeRtos with Delete Task
    void PrintTopic();                                                         //Implement FreeRtos with Delete Task
    void Update();
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
    this->Update();
}

void MQTT_WRAPPER::Subscribe(const char *topic)
{
    this->currentTopic = (char *)topic;
    boolean isAdded = false;
    int idx = 0;
    while (!isAdded)
    {
        if (this->topicList[idx].length() == 0)
        {
            this->topicList[idx] = this->currentTopic;
            isAdded = !isAdded;
        }
        else
        {
            idx++;
        }
    }
    Sprintln("Topic Added : " + String(this->topicList[idx]));
    this->PrintTopic();
    vTaskDelete(Update_Handle);
    this->Update();
}

void MQTT_WRAPPER::Subscribe_code(void *_this)
{
    MQTT_WRAPPER task = *(MQTT_WRAPPER *)(_this);

    for (;;)
    {
        TaskDelay(delay_Time);
    }
}

void MQTT_WRAPPER::reConnect()
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
            while (this->topicList[idx].length() != 0)
            {
                char buffer[512];
                this->topicList[idx].toCharArray(buffer, topicList[idx].length() + 1);
                this->mqtt.subscribe(buffer);
                Sprintln("Start Subscribe =>" + String(buffer));
                idx++;
            }
        }
        else
        {
            Sprint("failed, rc=");
            Sprint(this->mqtt.state());
            //Sprintln(" try again in 5 seconds");
            delay(100);
        }
    }
}

void MQTT_WRAPPER::Publish(const char *topic, char *payload)
{
    this->curPubTopic = (char *)topic;
    this->curPayload = payload;
    xTaskCreate(Publis_code, "Publish Task ", Default_WiFi_Task_Stack, this, 1, &Publish_Handle);
    vTaskDelete(this->Publish_Handle);
}

void MQTT_WRAPPER::Publis_code(void *_this)
{
    MQTT_WRAPPER task = *(MQTT_WRAPPER *)(_this);
    if (!task.mqtt.connected())
    {
        task.reConnect();
    }
    task.mqtt.publish(task.curPubTopic, task.curPayload);
    for (;;)
    {
        TaskDelay(delay_Time);
    }
}

void MQTT_WRAPPER::Update()
{
    xTaskCreate(update_code, "update Task", Default_WiFi_Task_Stack, this, 1, &Update_Handle);
}

void MQTT_WRAPPER::update_code(void *_this)
{
    MQTT_WRAPPER task = *(MQTT_WRAPPER *)(_this);
    for (;;)
    {
        if (!task.mqtt.connected())
        {

            task.reConnect();
        }
        task.mqtt.loop();
        TaskDelay(delay_Time);
    }
}

void MQTT_WRAPPER::PrintTopic()
{
    int idx = 0;
    while (this->topicList[idx] != '\0')
    {
        Sprintln(String(idx) + " : " + topicList[idx]);
        idx++;
    }
}
#endif

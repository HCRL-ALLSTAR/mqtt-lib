#ifndef MQTT_TASK_H
#define MQTT_TASK_H

// #include <Arduino.h>
// #include <PubSubClient.h>
// #include <WiFiClient.h>
// #include "System/SystemDefaults.hpp"
// #include "System/SystemMacros.hpp"

// class MqttTask
// {
// private:
//     WiFiClient client;
//     PubSubClient mqtt;

//     TaskHandle_t Update_Handle;

//     char *currentTopic;
//     char *mqttServer;
//     int mqttPort;
//     String topicList[100];

//     static void update_code(void *);
//     void reConnect();

// public:
//     MqttTask(/* args */);
//     ~MqttTask();
//     void Begin(const char *mqttServer, int mqttPort, MQTT_CALLBACK_SIGNATURE); //Implement FreeRTOS
//     void Subscribe(const char *topic);                                         //Implement FreeRtos with Delete Task
//     void Publish(const char *topic, const char *payload);                      //Implement FreeRtos with Delete Task
//     void PrintTopic();                                                         //Implement FreeRtos with Delete Task
//     void Update();
// };

// MqttTask::MqttTask(/* args */)
// {
//     this->mqtt = PubSubClient(this->client);
// }

// MqttTask::~MqttTask()
// {
// }

// void MqttTask::Begin(const char *mqttServer, int mqttPort, MQTT_CALLBACK_SIGNATURE)
// {
//     this->mqttServer = (char *)mqttServer;
//     this->mqttPort = mqttPort;
//     this->mqtt.setServer(this->mqttServer, this->mqttPort);
//     this->mqtt.setCallback(callback);
//     this->Update();
// }

// void MqttTask::Subscribe(const char *topic)
// {
//     this->currentTopic = (char *)topic;
//     boolean isAdded = false;
//     int idx = 0;
//     while (!isAdded)
//     {
//         if (this->topicList[idx].length() == 0)
//         {
//             this->topicList[idx] = this->currentTopic;
//             isAdded = !isAdded;
//         }
//         else
//         {
//             idx++;
//         }
//     }
//     Sprintln("Topic Added : " + String(this->topicList[idx]));
//     this->PrintTopic();
//     vTaskDelete(Update_Handle);
//     this->Update();
// }

// void MqttTask::reConnect()
// {
//     int idx = 0;
//     while (!this->mqtt.connected())
//     {
//         Sprintln("Attempting MQTT connection...");
//         String clientId = "ESP8266Client-";
//         clientId += String(random(0xffff), HEX);
//         if (this->mqtt.connect(clientId.c_str()))
//         {
//             Sprintln("Connected");
//             this->mqtt.publish("start", "Hello world");
//             this->mqtt.subscribe("intopic");
//             while (this->topicList[idx].length() != 0)
//             {
//                 char buffer[512];
//                 this->topicList[idx].toCharArray(buffer, topicList[idx].length() + 1);
//                 this->mqtt.subscribe(buffer);
//                 Sprintln("Start Subscribe =>" + String(buffer));
//                 idx++;
//             }
//         }
//         else
//         {
//             Sprint("failed, rc=");
//             Sprint(this->mqtt.state());
//             //Sprintln(" try again in 5 seconds");
//             delay(100);
//         }
//     }
// }

// void MqttTask::Publish(const char *topic, const char *payload)
// {
//     this->mqtt.publish(topic, payload);
// }

// void MqttTask::Update()
// {
//     xTaskCreate(update_code, "update Task", Default_Task_Stack, this, 1, &Update_Handle);
// }

// void MqttTask::update_code(void *_this)
// {
//     MqttTask task = *(MqttTask *)(_this);
//     for (;;)
//     {
//         if (!task.mqtt.connected())
//         {
//             task.reConnect();
//         }
//         task.mqtt.loop();
//         TaskDelay(delay_Time);
//     }
// }

// void MqttTask::PrintTopic()
// {
//     int idx = 0;
//     while (this->topicList[idx] != '\0')
//     {
//         Sprintln(String(idx) + " : " + topicList[idx]);
//         idx++;
//     }
// }
// */
#endif

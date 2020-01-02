#ifndef MQTT_TASK_H
#define MQTT_TASK_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "System/SystemDefaults.hpp"
#include "System/SystemMacros.hpp"
#include "MqttWrapper/MqttWrapper.h"

class MqttTask
{
private:
    WiFiClient client;
    PubSubClient mqtt;

public:
    MqttTask(/* args */);
    ~MqttTask();
};

MqttTask::MqttTask(/* args */)
{
}

MqttTask::~MqttTask()
{
}

#endif

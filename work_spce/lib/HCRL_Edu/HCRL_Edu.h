#ifndef HCRL_Edu_H
#define HCRL_Edu_H
#include <Arduino.h>

#include "MQTT/MqttTask.h"
#include "WiFi/WiFiTask.h"
#include "System/SystemDefaults.hpp"
#include "System/SystemMacros.hpp"

class HCRL_Edu
{
private:
    /* data */
public:
    HCRL_Edu(/* args */);
    ~HCRL_Edu();
    MqttTask MQTT;
    WiFiTask WiFi;
};

HCRL_Edu::HCRL_Edu(/* args */)
{
}

HCRL_Edu::~HCRL_Edu()
{
}

#endif
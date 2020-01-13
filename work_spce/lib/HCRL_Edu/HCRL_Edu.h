#ifndef HCRL_Edu_H
#define HCRL_Edu_H
#include <Arduino.h>
#include "MQTT/MqttTask.h"
#include "WiFi/WiFiTask.h"
#include "Sensors/ENVs/ENVs.h"
#include "Sensors/Angle/AngleClass.h"
#include "Sensors/MotionClass/MotionClass.h"
#include "Sensors/RGBStrip/RGBStripClass.h"
#include "Sensors/LedRGBClass/LedRGBClass.h"
#include "System/SystemDefaults.hpp"
#include "System/SystemMacros.hpp"
#include "Baterry/baterry.h"
class HCRL_Edu
{
private:
    /* data */
public:
    HCRL_Edu(/* args */);
    ~HCRL_Edu();
    // Sensors
    ENVs ENV;
    AngleClass Angle;
    LedRGBClass LedRGB;
    MotionClass Motion;
    RGBStrip StripRGB;
    //Connections
    MqttTask MQTT;
    WiFiTask WiFi;

    BaterryClass baterry;
};

HCRL_Edu::HCRL_Edu(/* args */)
{
}

HCRL_Edu::~HCRL_Edu()
{
}

#endif
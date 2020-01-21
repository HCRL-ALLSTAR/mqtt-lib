#ifndef HCRL_EDU_H
#define HCRL_EDU_H

#include <Arduino.h>
#include "WiFi/wifiWrapper.h"
#include "MQTT/mqttWrapper.h"
#include "millisDelay/millisDelay.h"
#include "UI/UI.h"
#include "UI/UI.cpp"
class HCRL_EDU
{
private:
    /* data */
public:
    HCRL_EDU(/* args */);
    ~HCRL_EDU();

    wifiWrapper WiFi;
    mqttWrapper MQTT;
    UI ui;
    void update();
};

HCRL_EDU::HCRL_EDU(/* args */)
{
}

HCRL_EDU::~HCRL_EDU()
{
}

void HCRL_EDU::update()
{
    ui.update();
    MQTT.update();
}

#endif
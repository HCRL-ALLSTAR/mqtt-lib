#ifndef WiFi_Wrapper_H
#define WiFi_Wrapper_H

#include <Arduino.h>
#include "System/SystemMacros.hpp"
#include "System/SystemDefaults.hpp"
#include "WiFiWrapper/WiFiWrapper.h"

class WiFiTask
{
private:
    WiFiWrapper wrapper;

public:
    WiFiTask(/* args */);
    ~WiFiTask();
};

WiFiTask::WiFiTask(/* args */)
{
}

WiFiTask::~WiFiTask()
{
}

#endif

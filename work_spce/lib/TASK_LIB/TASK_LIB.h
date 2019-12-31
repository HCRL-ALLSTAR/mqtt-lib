#include <WiFi.h>
#include <Arduino.h>

#ifndef TASK_LIB_H
#define TASK_LIB_H
#include "Default_Value/Default_Value.hpp"
#include "Macro_Functions/Macro_Functions.hpp"
#include "WiFi_Wrapper/WiFiWrapper.h"
class TASK_LIB
{
private:
public:
    WiFiWrapper WiFi;
    TASK_LIB(/* args */);
    ~TASK_LIB();
};

TASK_LIB::TASK_LIB(/* args */)
{
}

TASK_LIB::~TASK_LIB()
{
}

#endif

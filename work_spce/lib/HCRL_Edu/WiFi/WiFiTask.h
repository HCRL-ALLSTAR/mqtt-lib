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
    TaskHandle_t BeginHandle;
    static void BeginCode(void *pv);
    char *SSID;
    char *PASSWORD;

public:
    WiFiTask(/* args */);
    ~WiFiTask();
    void Begin(const char *SSID, const char *PASSWORD);
    boolean isConnected();
    char *getSSID();
    char *getPASSWORD();
};

WiFiTask::WiFiTask(/* args */)
{
}

WiFiTask::~WiFiTask()
{
}

void WiFiTask::BeginCode(void *pv)
{
    WiFiTask task = *(WiFiTask *)(pv);
    task.wrapper.Begin(task.SSID, task.PASSWORD);
    for (;;)
    {
        TaskDelay(delay_Time);
    }
}

void WiFiTask::Begin(const char *SSID, const char *PASSWORD)
{
    this->SSID = (char *)SSID;
    this->PASSWORD = (char *)PASSWORD;
    xTaskCreate(this->BeginCode, "Begin Task", Default_Task_Stack, this, 1, &BeginHandle);
}

boolean WiFiTask::isConnected()
{
    return this->wrapper.Connected();
}
char *WiFiTask::getSSID()
{
    return this->wrapper.getSSID();
}
char *WiFiTask::getPASSWORD()
{
    return this->wrapper.getPASSWORD();
}
#endif

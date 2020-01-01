
#include "WiFiTask.h"

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
    xTaskCreate(this->BeginCode, "Begin Task", Default_Task_Stack, this, 1, &this->BeginHandle);
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
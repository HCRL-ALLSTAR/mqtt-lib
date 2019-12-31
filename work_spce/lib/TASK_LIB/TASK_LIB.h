#include <WiFi.h>
#include <Arduino.h>

#ifndef TASK_LIB_H
#define TASK_LIB_H
#include "Default_Value/Default_Value.hpp"
#include "Macro_Functions/Macro_Functions.hpp"
class TASK_LIB
{
private:
    TaskHandle_t wifi_Handle;
    static void WiFi_Code(void *);
    char *ssid;
    char *pass;

public:
    TASK_LIB(/* args */);
    ~TASK_LIB();
    void wifi_Begin(const char *ssid, const char *pass);
};

TASK_LIB::TASK_LIB(/* args */)
{
}

TASK_LIB::~TASK_LIB()
{
}

void TASK_LIB::WiFi_Code(void *_this)
{
    TASK_LIB task = *(TASK_LIB *)(_this);
    WiFi.begin(task.ssid, task.pass);
    Sprintln("Connect to : " + String(task.ssid));
    Sprint("Start Connection => [ ");
    int startTime = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        Sprint("=");
        delay(delay_Time);
        if (millis() - startTime > 2000)
        {
            ESP.restart();
        }
    }
    Sprintln(" ] 100% ");
    Sprintln("WiFi Connected");
    Sprint("Local IP : ");
    Sprintln(WiFi.localIP());
    for (;;)
    {
        vTaskDelay(delay_Time / portTICK_PERIOD_MS);
    }
}
void TASK_LIB::wifi_Begin(const char *ssid, const char *pass)
{
    this->ssid = (char *)ssid;
    this->pass = (char *)pass;
    xTaskCreate(WiFi_Code, "WiFi Task", Default_WiFi_Task_Stack, this, 5, &wifi_Handle);
}
#endif

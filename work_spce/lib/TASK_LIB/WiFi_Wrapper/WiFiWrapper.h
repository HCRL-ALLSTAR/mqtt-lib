#include <WiFi.h>
#include "Default_Value/Default_Value.hpp"
#include "Macro_Functions/Macro_Functions.hpp"
#ifndef WIFI_WRAPPER_H
#define WIFI_WRAPPER_H
class WiFiWrapper
{
private:
    char *SSID;
    char *PASSWORD;
    TaskHandle_t wifi_Task;
    static void wifi_code(void *);

public:
    WiFiWrapper(/* args */);
    ~WiFiWrapper();
    void Begin(const char *ssid, const char *password);
};

WiFiWrapper::WiFiWrapper(/* args */)
{
}

WiFiWrapper::~WiFiWrapper()
{
}

void WiFiWrapper::wifi_code(void *_this)
{
    WiFiWrapper task = *(WiFiWrapper *)(_this);
    WiFi.begin(task.SSID, task.PASSWORD);
    Sprintln("Connect to : " + String(task.SSID));
    Sprint("Start Connection => [ ");
    int startTime = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        Sprint("=");
        delay(delay_Time);
        if (millis() - startTime > 3000)
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
void WiFiWrapper::Begin(const char *ssid, const char *pass)
{
    this->SSID = (char *)ssid;
    this->PASSWORD = (char *)pass;
    xTaskCreate(wifi_code, "WiFi Task", Default_WiFi_Task_Stack, this, 5, &wifi_Task);
}

#endif
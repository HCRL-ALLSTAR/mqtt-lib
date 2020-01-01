#ifndef WiFi_Wrapper_CPP
#define WiFi_Wrapper_CPP
#include "WiFiWrapper.h"

template <typename H>
void WiFiWrapper::Begin(H *host, const char *SSID, const char *PASSWORD)
{
    this->SSID = (char *)SSID;
    this->PASSWORD = (char *)PASSWORD;

    host->begin(this->SSID, this->PASSWORD);
    Sprintln("Connect to : " + String(this->SSID));
    Sprint("Start Connection => [ ");
    int startTime = millis();
    while (host->status() != WL_CONNECTED)
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
    Sprintln(host->localIP());
}

template <typename H>
boolean WiFiWrapper::Connected(H *host)
{
    return host->isConnected();
}

char *WiFiWrapper::getSSID()
{
    return this->SSID;
}

char *WiFiWrapper::getPASSWORD()
{
    return this->PASSWORD;
}

#endif

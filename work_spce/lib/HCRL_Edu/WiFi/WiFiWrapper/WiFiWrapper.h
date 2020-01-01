#ifndef WIFI_WRAPPER_H
#define WIFI_WRAPPER_H

#include <WiFi.h>
#include <Arduino.h>
#include "System/SystemMacros.hpp"

class WiFiWrapper
{
private:
    char *SSID;
    char *PASSWORD;

public:
    WiFiWrapper(/* args */);
    ~WiFiWrapper();

    void Begin(const char *SSID, const char *PASSWORD);
    boolean Connected();
    char *getSSID();
    char *getPASSWORD();
};

#endif
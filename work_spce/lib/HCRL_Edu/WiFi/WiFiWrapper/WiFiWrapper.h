#include "System/SystemMacros.hpp"
#ifndef WiFi_Wrapper_H
#define WiFi_Wrapper_H
#include <WiFi.h>
#include <Arduino.h>

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

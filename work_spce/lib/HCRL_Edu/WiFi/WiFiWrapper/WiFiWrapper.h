#ifndef WiFi_Wrapper_H
#define WiFi_Wrapper_H
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

    template <typename H>
    void Begin(H *host, const char *SSID, const char *PASSWORD);
    template <typename H>
    boolean Connected(H *host);
    char *getSSID();
    char *getPASSWORD();
};

WiFiWrapper::WiFiWrapper(/* args */)
{
}

WiFiWrapper::~WiFiWrapper()
{
}

#endif

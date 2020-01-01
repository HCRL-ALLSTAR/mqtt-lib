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

#endif

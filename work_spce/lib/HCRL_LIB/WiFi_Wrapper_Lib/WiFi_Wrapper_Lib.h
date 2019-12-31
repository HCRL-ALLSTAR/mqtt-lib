#include <WiFi.h>
#include <Arduino.h>

template <class W>
class WiFi_Wrapper_Lib
{
private:
    /* data */
public:
    WiFi_Wrapper_Lib(/* args */);
    ~WiFi_Wrapper_Lib();
    void begin(W *host, const char *ssid, const char *password);
};

WiFi_Wrapper_Lib::WiFi_Wrapper_Lib(/* args */)
{
}

WiFi_Wrapper_Lib::~WiFi_Wrapper_Lib()
{
}

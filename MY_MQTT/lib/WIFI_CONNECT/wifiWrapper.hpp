#include <WiFi.h>
#include <Arduino.h>
boolean show = true;

template <typename W>
void wifiBegin(W *host, const char *ssid, const char *password)
{
    int count = 0;
    delay(10);
    if (show)
    {
        // We start by connecting to a WiFi network
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);
    }

    host->begin(ssid, password);

    while (host->status() != WL_CONNECTED)
    {
        delay(500);
        if (show)
        {
            Serial.print(".");
        }
        count++;
        if (count == 5)
        {
            ESP.restart();
        }
    }

    randomSeed(micros());

    if (show)
    {

        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(host->localIP());
    }
}
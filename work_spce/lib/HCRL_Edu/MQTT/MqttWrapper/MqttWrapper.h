#ifndef MQTT_WRAPPER_H
#define MQTT_WRAPPER_H
#include <Arduino.h>
#include <PubSubClient.h>
template <class H>
class MqttWrapper
{
private:
    H *host;

public:
    MqttWrapper(H *host) { this->host = host; }
    ~MqttWrapper() {}
    void Begin(const char *Server, int Port, MQTT_CALLBACK_SIGNATURE);
};

template <class H>
void MqttWrapper<H>::Begin(const char *Server, int Port, MQTT_CALLBACK_SIGNATURE)
{
    this->host->setServer(Server, Port);
    this->host->setCallback(callback);
}

#endif
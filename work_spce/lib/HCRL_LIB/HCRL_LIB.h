#include "MQTT_CONNECT/mqttWrapper.hpp"
#include "WIFI_CONNECT/wifiWrapper.hpp"
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

class HCRL_LIB
{
private:
    WiFiClient client;
    PubSubClient mqtt;
    String topicList[100];
    char *ssid;
    char *password;
    void mqttReconnect();

public:
    HCRL_LIB(/* args */);
    ~HCRL_LIB();
    void wifiBegin(char *ssid, char *pass);
    void mqttBegin(const char *mqttServer, int mqttPort, MQTT_CALLBACK_SIGNATURE);
    void mqttAddTopic(const char *topic);
    void mqttPrintTopic();
    void mqttPublish(const char *topic, const char *payload);
    void mqttUpdate();
};

HCRL_LIB::HCRL_LIB(/* args */)
{
    this->mqtt = PubSubClient(this->client);
}

HCRL_LIB::~HCRL_LIB()
{
}

void HCRL_LIB::wifiBegin(char *ssid, char *pass)
{
    this->ssid = ssid;
    this->password = pass;
    _wifiBegin(&WiFi, this->ssid, this->password);
}

void HCRL_LIB::mqttBegin(const char *mqttServer, int mqttPort, MQTT_CALLBACK_SIGNATURE)
{
    _mqttBegin(&mqtt, mqttServer, mqttPort, callback);
}

void HCRL_LIB::mqttAddTopic(const char *topic)
{
    _addTopic(topicList, topic);
}
void HCRL_LIB::mqttPrintTopic()
{
    _print_Topic(topicList);
}

void HCRL_LIB::mqttPublish(const char *topic, const char *payload)
{
    _mqtt_publish(&mqtt, topic, payload, topicList);
}

void HCRL_LIB::mqttUpdate()
{
    _mqtt_loop(&mqtt, topicList);
}

void HCRL_LIB::mqttReconnect()
{
    _mqtt_reconnect(&mqtt, topicList);
}
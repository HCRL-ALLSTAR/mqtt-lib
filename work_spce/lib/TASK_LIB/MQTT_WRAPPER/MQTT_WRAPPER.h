#ifndef MQTT_WRAPPER_H
#define MQTT_WRAPPER_H
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

class MQTT_WRAPPER
{
private:
    WiFiClient client;
    PubSubClient mqtt;
    template <typename H>
    void __publish(H *host, const char *topic, const char *payload, String *topic_list);
    template <typename H>
    void __loop(H *host, String *topic_list);
    template <typename H>
    boolean __connected(H *host);
    template <typename H>
    void __reconnect(H *host, String *topic_list);
    template <typename H>
    void __Begin(H *host, const char *mqttServer, int mqttPort, MQTT_CALLBACK_SIGNATURE);
    void __addTopic(String *target, const char *topic);
    void __printTopic(String *topicList);

public:
    MQTT_WRAPPER(/* args */);
    ~MQTT_WRAPPER();
    void Begin();      //Implement FreeRTOS
    void Subscribe();  //Implement FreeRtos with Delete Task
    void Publish();    //Implement FreeRtos with Delete Task
    void PrintTopic(); //Implement FreeRtos with Delete Task
    void Update();     // Implement FreeRTOS
};

MQTT_WRAPPER::MQTT_WRAPPER(/* args */)
{
    this->mqtt = PubSubClient(this->client);
}

MQTT_WRAPPER::~MQTT_WRAPPER()
{
}

void MQTT_WRAPPER::Begin()
{
}
#endif

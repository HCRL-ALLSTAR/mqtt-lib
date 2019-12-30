#include "PubSubClient/PubSubClient.h"
boolean debug = true;
void print_Topic(String *topicList)
{
    int idx = 0;
    while (topicList[idx].length() != 0)
    {
        Serial.println(String(idx) + " : " + String(topicList[idx]));
        idx = idx + 1;
    }
}

void addTopic(String *target, const char *topic)
{
    boolean isAdded = false;
    int idx = 0;
    while (!isAdded)
    {
        if (target[idx].length() == 0)
        {
            target[idx] = topic;
            isAdded = !isAdded;
        }
        else
        {
            idx++;
        }
    }
}

template <typename H>
void mqttBegin(H *host, const char *mqttServer, int mqttPort, MQTT_CALLBACK_SIGNATURE)
{
    host->setServer(mqttServer, mqttPort);
    host->setCallback(callback);
}

template <typename H>
void mqtt_reconnect(H *host, String *topic_list)
{
    int idx = 0;
    // Loop until we're reconnected
    while (!host->connected())
    {
        if (debug)
        {
            Serial.print("Attempting MQTT connection...");
        }
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (host->connect(clientId.c_str()))
        {
            if (debug)
            {

                Serial.println("connected");
            }
            // Once connected, publish an announcement...
            host->publish("outTopic", "hello world");
            // ... and resubscribe
            host->subscribe("inTopic");
            while (topic_list[idx].length() != 0)
            {
                char buffer[512];
                topic_list[idx].toCharArray(buffer, topic_list[idx].length() + 1);
                host->subscribe(buffer);
                if (debug)
                {
                    Serial.println("Start Subscribe =>" + String(buffer));
                }
                idx++;
            }
        }
        else
        {
            if (debug)
            {

                Serial.print("failed, rc=");
                Serial.print(host->state());
                Serial.println(" try again in 5 seconds");
                //Wait 5 seconds before retrying
            }
            delay(5000);
        }
    }
}

template <typename H>
boolean mqtt_connected(H *host)
{
    return host->connected();
}

template <typename H>
void mqtt_loop(H *host, String *topic_list)
{
    if (!host->connected())
    {
        mqtt_reconnect(&host, &topic_list);
    }
    host->loop();
}

template <typename H>
void mqtt_publish(H *host, const char *topic, const char *payload, String *topic_list)
{
    if (!host->connected())
    {
        mqtt_reconnect(&host, &topic_list);
    }
    host->publish(topic, payload);
}
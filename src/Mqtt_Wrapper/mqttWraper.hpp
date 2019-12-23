#include <PubSubClient.h>
#include <WiFi.h>
#include <Arduino.h>

String topic_list[100];
WiFiClient espClient;
PubSubClient client(espClient);

void print_topic_list()
{
    int idx = 0;
    while (topic_list[idx].length() != 0)
    {
        Serial.println(String(idx) + " : " + String(topic_list[idx]));
        idx++;
    }
}

void addTopic(const char *topic)
{
    boolean isAdded = false;
    int idx = 0;
    while (!isAdded)
    {
        if (topic_list[idx].length() == 0)
        {
            topic_list[idx] = topic;
            isAdded = !isAdded;
        }
        else
        {
            idx++;
        }
    }
}

void wifi_begin(const char *ssid, const char *password)
{
    int count = 0;
    delay(10);
    // We start by connecting to a WiFi network
    // Serial.println();
    // Serial.print("Connecting to ");
    // Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        // Serial.print(".");
        count++;
        if (count == 5)
        {
            ESP.restart();
        }
    }

    randomSeed(micros());

    // Serial.println("");
    // Serial.println("WiFi connected");
    // Serial.println("IP address: ");
    // Serial.println(WiFi.localIP());
}

void mqtt_begin(const char *mqttServer, int mqttPort, MQTT_CALLBACK_SIGNATURE)
{
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
}

void mqtt_reconnect()
{
    int idx = 0;
    // Loop until we're reconnected
    while (!client.connected())
    {
        // Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str()))
        {
            // Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("outTopic", "hello world");
            // ... and resubscribe
            client.subscribe("inTopic");
            while (topic_list[idx].length() != 0)
            {
                char buffer[512];
                topic_list[idx].toCharArray(buffer, topic_list[idx].length() + 1);
                client.subscribe(buffer);
                // Serial.println("Start Subscribe =>" + String(buffer));
                idx++;
            }
        }
        else
        {
            // Serial.print("failed, rc=");
            // Serial.print(client.state());
            // Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

boolean mqtt_connected()
{
    return client.connected();
}

void mqtt_loop()
{
    if (!client.connected())
    {
        mqtt_reconnect();
    }
    client.loop();
}

void mqtt_publish(const char *topic, const char *payload)
{
    if (!client.connected())
    {
        mqtt_reconnect();
    }
    client.publish(topic, payload);
}

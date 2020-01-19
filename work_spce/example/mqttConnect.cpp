#include <Arduino.h>
#include "HCRL_Edu.h"

HCRL_Edu hcrl;

// Default Callback Function
void callback(char *Topic, byte *Paylaod, unsigned int Length)
{
    Paylaod[Length] = '\0';
    String topic_str = Topic, payload_str = (char *)Paylaod;
    Serial.println("[" + topic_str + "]: " + payload_str);
}

void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    hcrl.MQTT.Begin(HCRL_MQTT_SERVER, HCRL_MQTT_PORT, callback); //Start Connect to Server
    hcrl.MQTT.StartSubscribe("YOUR TOPIC");                      // Add Subscribe Topic
    //print MQTT Details
    Sprintln("MQTT Server Address : " + String(hcrl.MQTT.GetServer()));
    Sprintln("MQTT Server Port : " + String(hcrl.MQTT.GetPort()));
    Sprintln("MQTT Status : " + String(hcrl.MQTT.getStatus()));
    Sprintln("MQTT Username :  " + String(hcrl.MQTT.GetUsername()));
    Sprintln("MQTT Password : " + String(hcrl.MQTT.GetPassword()));
}

void loop()
{
    hcrl.Update();                               //Update Data
    hcrl.MQTT.Publish("YOUR TOPIC", "YOUR MSG"); //Publish MSG To Topic
}
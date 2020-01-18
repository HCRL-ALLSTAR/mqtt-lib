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
    //hcrl.MQTT.Begin(HCRL_MQTT_SERVER, HCRL_MQTT_PORT, callback); //Start Connect to Serve
    //hcrl.MQTT.StartSubscribe("YOUR TOPIC");                      // Add Subscribe Topic
}

void loop()
{
    hcrl.Update(); //Update Data
    //hcrl.MQTT.Publish("YOUR TOPIC", "YOUR MSG"); //Publish MSG To Topic
}
// #include <Arduino.h>
// #include "HCRL_Edu.h"
// #include "jsonwrapper.hpp"
// #include "ArduinoJson.h"

// HCRL_Edu edu;
// float temp;
// float humi;
// float pres;

// void SerialENV()
// {
//     temp = edu.ENV.GetTemp();
//     humi = edu.ENV.GetHumi();
//     pres = edu.ENV.GetPressure();
//     size_t size = 1024;
//     DynamicJsonDocument mainDoc(size);
//     char buffer[2048];
//     mainDoc["Temp"] = temp;
//     mainDoc["Humi"] = humi;
//     mainDoc["Pressure"] = pres;
//     serializeJson(mainDoc, buffer);
//     //Sprintln("Temp : " + String(temp) + " | Humi : " + String(humi) + " | Pres : " + String(pres));
//     //Sprintln(buffer);
//     edu.MQTT.Publish("/env", buffer);
// }
// void DummyLight()
// {
//     size_t size = 1024;
//     DynamicJsonDocument mainDoc(size);
//     char buffer[2048];
// }

// void callback(char *Topic, byte *Paylaod, unsigned int Length)
// {
//     Paylaod[Length] = '\0';
//     String topic_str = Topic, payload_str = (char *)Paylaod;
//     //Serial.println("[" + topic_str + "]: " + payload_str);
// }

// void setup()
// {
//     Serial.begin(Defalult_Baud_Rate);
//     edu.WiFi.Begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS);
//     edu.MQTT.Begin(HCRL_MQTT_SERVER, HCRL_MQTT_PORT, callback);
//     //edu.MQTT.StartSubscribe("/Test");
//     edu.ENV.Begin();

//     randomSeed(millis());
// }

// void loop()
// {
//     SerialENV();

//     TaskDelay(1000);
// }

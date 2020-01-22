#include <Arduino.h>
#include "HCRL_EDU.h"

#define PUB_LIGHT_1 "M5/light1"
#define PUB_LIGHT_2 "M5/light2"
#define PUB_LIGHT_3 "M5/light3"
#define PUB_AIR "M5/air"
#define PUB_FAN "M5/fan"
#define PUB_ENV "M5/env"
#define PUB_PIR "M5/pir"

#define SUB_LIGHT_1 "Node/light1"
#define SUB_LIGHT_2 "Node/light2"
#define SUB_LIGHT_3 "Node/light3"
#define SUB_AIR "Node/air"
#define SUB_FAN "Node/fan"

#define KEY_TEMP "temp"
#define KEY_HUMI "humi"
#define KEY_PRESSURE "pres"
#define KEY_STATUS "st"
#define KEY_LEVEL "lv"
#define KEY_R "R"
#define KEY_G "G"
#define KEY_B "B"

void SubLight(byte *payload, unsigned int length, uint8_t *lightStatus, uint16_t *);
void SubAir(byte *payload, unsigned int length);
void SubFan(byte *payload, unsigned int length);
void PubENV(const char *topic);
void PubPIR(const char *topic);
void PubLight(const char *topic, uint8_t lightStatu);
void PubAir(const char *topic);
void PubFan(const char *topic);
void callback(char *Topic, byte *Paylaod, unsigned int Length);

float temp;
float humi;
float pressure;
uint8_t motionStatus;
uint8_t light_1Status;
uint8_t light_2Status;
uint8_t light_3Status;

uint16_t light_1RGB[3];
uint16_t light_2RGB[3];
uint16_t light_3RGB[3];

uint8_t airStatus;
uint8_t airTemp;
uint8_t fanStatus;
uint8_t fanLevel;

millisDelay pubDelay;
millisDelay ledRand;
HCRL_EDU hcrl;

void setup()
{
    Serial.begin(115200);
    hcrl.WiFi.begin(HCRL_WiFi_SSID, HCRL_WiFi_PASS);
    hcrl.MQTT.begin(HCRL_MQTT_SERVER, HCRL_MQTT_PORT, callback);
    hcrl.MQTT.startSubscribe("/test");
    hcrl.MQTT.startSubscribe(SUB_AIR);
    hcrl.MQTT.startSubscribe(SUB_FAN);
    hcrl.MQTT.startSubscribe(SUB_LIGHT_1);
    hcrl.MQTT.startSubscribe(SUB_LIGHT_2);
    hcrl.MQTT.startSubscribe(SUB_LIGHT_3);

    //Get Status
    Sprintln("WiFi SSID : " + String(hcrl.WiFi.getSSID()));
    Sprintln("WiFi Status : " + String(hcrl.WiFi.getStatus()));

    Sprintln("MQTT Server : " + String(hcrl.MQTT.getServer()));
    Sprintln("MQTT Port : " + String(hcrl.MQTT.getPort()));
    Sprintln("MQTT Username : " + String(hcrl.MQTT.getUsername()));
    Sprintln("MQTT Status : " + String(hcrl.MQTT.getStatus()));

    hcrl.Ui.begin();

    //UI
    hcrl.Ui.node_init(5);
    for (int i = 0; i < 5; i++)
    {
        char buffer[50];
        sprintf(buffer, "Item %d", i);
        hcrl.Ui.node_setTitle(i, (String)buffer, "abcdefghijkl");
        hcrl.Ui.node_setTitlePic(i, "/AIR/Air_GREEN.png", "/AIR/Air_GREEN_Hover.png");
    }

    hcrl.Ui.node_setAllTitleColor(WHITE, CYAN);

    hcrl.Ui.node_setType(0, FAN);
    hcrl.Ui.node_setTitle(0, "Fan", "Near Door");
    hcrl.Ui.node_setTitlePic(0, "/FAN/Fan_BLUE.png", "/FAN/Fan_BLUE_Hover.png");

    hcrl.Ui.node_setType(1, AIR);
    hcrl.Ui.node_setTitle(1, "Air", " ");
    hcrl.Ui.node_setTitlePic(1, "/AIR/Air_RED.png", "/AIR/Air_RED_Hover.png");

    hcrl.Ui.node_setType(2, LIGHT);
    hcrl.Ui.node_setTitle(2, "LIGHT", "Overall");
    hcrl.Ui.node_setTitlePic(2, "/LIGHT/Li_YELLOW.png", "/LIGHT/Li_YELLOW_Hover.png");

    pubDelay.start(Sec2MS(3));
    ledRand.start(Sec2MS(1));

    hcrl.ANGLE.begin();
    hcrl.ENV.begin();
    hcrl.MOTION.begin();
    hcrl.RGB_LED.begin();
    hcrl.RGB_LED.setBrightness(50);

    hcrl.RGB_STRIP.begin();
    hcrl.RGB_STRIP.setBrightness(255);
}

void loop()
{
    temp = hcrl.ENV.getTemp();
    humi = hcrl.ENV.getHumi();
    pressure = hcrl.ENV.getPressure();
    motionStatus = hcrl.MOTION.getValue();
    light_1Status = random(0, 2);
    light_2Status = random(0, 2);
    light_3Status = random(0, 2);
    airStatus = random(0, 2);
    airTemp = random(25, 34);
    fanStatus = random(0, 2);
    fanLevel = random(1, 4);

    if (ledRand.justFinished())
    {
        for (int i = 0; i < RGB_LED_PIXELS; i++)
        {
            hcrl.RGB_LED.setPixelsColor(i, random(255), random(255), random(255));
        }
        for (int i = 0; i < RGB_STRIP_PIXELS; i++)
        {
            hcrl.RGB_STRIP.setPixelsColor(i, random(255), random(255), random(255));
        }
        ledRand.repeat();
    }

    if (pubDelay.justFinished())
    {
        PubAir(PUB_AIR);
        PubENV(PUB_ENV);
        PubFan(PUB_FAN);
        PubPIR(PUB_PIR);
        PubLight(PUB_LIGHT_1, light_1Status);
        PubLight(PUB_LIGHT_2, light_2Status);
        PubLight(PUB_LIGHT_3, light_3Status);
        pubDelay.repeat();
    }

    hcrl.update();
    randomSeed(millis());
}

// Default Callback Function
void callback(char *Topic, byte *Paylaod, unsigned int Length)
{
    Paylaod[Length] = '\0';
    String topic_str = Topic, payload_str = (char *)Paylaod;
    Serial.println("[" + topic_str + "]: " + payload_str);
    if (topic_str.equals(SUB_LIGHT_1))
    {
        SubLight(Paylaod, Length, &light_1Status, light_1RGB);
    }
    else if (topic_str.equals(SUB_LIGHT_2))
    {
        SubLight(Paylaod, Length, &light_2Status, light_2RGB);
    }
    else if (topic_str.equals(SUB_LIGHT_3))
    {
        SubLight(Paylaod, Length, &light_3Status, light_3RGB);
    }
    else if (topic_str.equals(SUB_AIR))
    {
        SubAir(Paylaod, Length);
    }
    else if (topic_str.equals(SUB_FAN))
    {
        SubFan(Paylaod, Length);
    }
}

/*
{
    "st": boolean,  --> status of eachlight 
    "R": number,	--> Red
    "G": number,	--> Green
    "B": number		--> Blue
}
*/
void SubLight(byte *payload, unsigned int length, uint8_t *lightStatus, uint16_t *lightRGB)
{
    StaticJsonDocument<1024> doc;
    deserializeJson(doc, payload, length);
    *lightStatus = doc[KEY_STATUS];
    lightRGB[0] = doc[KEY_R];
    lightRGB[1] = doc[KEY_G];
    lightRGB[2] = doc[KEY_B];
}

/*
{
    "st": boolean,	--> Status of each air conditioner
    "temp" : number	--> Target temperature
}
*/
void SubAir(byte *payload, unsigned int length)
{
    StaticJsonDocument<1024> doc;
    deserializeJson(doc, payload, length);
    airStatus = doc[KEY_STATUS];
    airTemp = doc[KEY_TEMP];
}

/*
{
    "st": boolean,	--> Status of each fan
    "level": number	--> Fan level
}
*/
void SubFan(byte *payload, unsigned int length)
{
    StaticJsonDocument<1024> doc;
    deserializeJson(doc, payload, length);
    fanStatus = doc[KEY_STATUS];
    fanLevel = doc[KEY_LEVEL];
}

/*
{
    "temp": number,		--> Current Temperature
    "humi": number,		--> Curremt HUmidity
    "pressure":number	--> Current Pressure
}
*/
void PubENV(const char *topic)
{
    size_t size = 1024;
    DynamicJsonDocument docJson(size);
    char json[1024];
    docJson[KEY_TEMP] = temp;
    docJson[KEY_HUMI] = humi;
    docJson[KEY_PRESSURE] = pressure;
    serializeJson(docJson, json);
    //Sprintln(String(topic) + " : " + String(json));
    hcrl.MQTT.publish(topic, json);
}

/*
{
    "st": boolean	--> Current Value of Motion Sensor
}
*/
void PubPIR(const char *topic)
{
    size_t size = 1024;
    DynamicJsonDocument docJson(size);
    char json[1024];
    docJson[KEY_STATUS] = motionStatus;
    serializeJson(docJson, json);
    //Sprintln(String(topic) + " : " + String(json));
    hcrl.MQTT.publish(topic, json);
}

/*
{
    "st": boolean	-->light status
}
*/
void PubLight(const char *topic, uint8_t lightStatus)
{
    size_t size = 1024;
    DynamicJsonDocument docJson(size);
    char json[1024];
    docJson[KEY_STATUS] = lightStatus;
    serializeJson(docJson, json);
    //Sprintln(String(topic) + " : " + String(json));
    hcrl.MQTT.publish(topic, json);
}

/*
{
    "st": boolean,	--> Status of each air conditioner
    "temp" : number	--> Target temperature
}
*/
void PubAir(const char *topic)
{
    size_t size = 1024;
    DynamicJsonDocument docJson(size);
    char json[1024];
    docJson[KEY_STATUS] = airStatus;
    docJson[KEY_TEMP] = airTemp;
    serializeJson(docJson, json);
    //Sprintln(String(topic) + " : " + String(json));
    hcrl.MQTT.publish(topic, json);
}

/*
{
    "st": boolean,	--> Status of each fan
    "level": number	--> Fan level
}
*/
void PubFan(const char *topic)
{
    size_t size = 1024;
    DynamicJsonDocument docJson(size);
    char json[1024];
    docJson[KEY_STATUS] = fanStatus;
    docJson[KEY_LEVEL] = fanLevel;
    serializeJson(docJson, json);
    //Sprintln(String(topic) + " : " + String(json));
    hcrl.MQTT.publish(topic, json);
}

// void wifi_task_code(void *p)
// {
//     Serial.println("In wifi Task use core : " + String(xPortGetCoreID()));

//     WiFi.begin(ssid, password);
//     int timeCounter = millis();
//     while (WiFi.status() != WL_CONNECTED)
//     {
//

//         if (millis() - timeCounter >= 2000)
//         {
//             ESP.restart();
//         }
//     }
//     Serial.println("WiFi connected");
//     Serial.print("IP address is ");
//     Serial.println(WiFi.localIP());
//     for (;;)
//     {
//

// }

#include <M5Stack.h>
#include <FastLED.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <mqttWraper.hpp>
#include <DHT12.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Prototype Function
void FastLEDshowTask(void *pvParameters);
void RGB_LEDshowTask(void *pvParameters);
void Angle_LEDshowTask(void *pvParameters);
void ENV_showTask(void *pvParameters);
void Button_Read_Task(void *pvParameters);
void Display_show_Task(void *pvParameters);

// Task Handler
TaskHandle_t ledBar_Task;
TaskHandle_t RGB_LED_Task;
TaskHandle_t Read_Angle_Task;
TaskHandle_t ENV_Task;
TaskHandle_t Button_Task;
TaskHandle_t Display_Task;

//delay time
int delay_time = 90;

// led bar var
#define Neopixel_PIN 15
#define NUM_LEDS 10
CRGB leds[NUM_LEDS];
uint8_t gHue = 0;

//RGB LEDs pin
#define RGB_LED_PIN 26
#define NUMs_RGB_LED 3
int RGB_COLOR[3] = {100, 100, 100};
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMs_RGB_LED, RGB_LED_PIN, NEO_GBR + NEO_KHZ800);

// Angle Task
#define Angle_PIN 36
int cur_angle = 0;
int last_sensorValue = 0;
int maxValue = 0;
int mapValue = 0;
int real_val = 0;

// ENV Task
float tmp = 0;
float humi = 0;
float last_tmp = 0;
float last_humi = 0;
DHT12 dht12; //Preset scale CELSIUS and ID 0x5c.

//Button STATUS
boolean BTN_STA[3] = {0, 0, 0};

//Display Task
#define x_axis 10
#define y_asix 30

void setup()
{
    M5.begin();
    M5.Power.begin();
    M5.Lcd.fillScreen(BLACK);
    // Neopixel initialization
    FastLED.addLeds<WS2811, Neopixel_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

    xTaskCreatePinnedToCore(FastLEDshowTask, "FastLEDshowTask", 2048, NULL, 2, &ledBar_Task, 1);

    //RGB LEDs initiallization
    pixels.begin();
    xTaskCreatePinnedToCore(RGB_LEDshowTask, "RGB_LEDshowTask", 2048, NULL, 1, &RGB_LED_Task, 1);

    //Angle Pin Read initiallization
    pinMode(25, OUTPUT); // Disable Speaker
    digitalWrite(25, 0);
    xTaskCreatePinnedToCore(Angle_LEDshowTask, "Angle_LEDshowTask", 2048, NULL, 2, &Read_Angle_Task, 1);

    //ENV Read initialization
    Wire.begin();
    xTaskCreatePinnedToCore(ENV_showTask, "ENV showTask", 2048, NULL, 2, &ENV_Task, 1);

    // Read Read initialization
    xTaskCreatePinnedToCore(Button_Read_Task, "Buttib Rad ask", 2048, NULL, 2, &Button_Task, 1);

    // Display
    xTaskCreatePinnedToCore(Display_show_Task, "Buttib Rad ask", 2048, NULL, 2, &Display_Task, 0);
}

void loop()
{

    vTaskDelay(delay_time / portTICK_RATE_MS);
}

void FastLEDshowTask(void *pvParameters)
{
    Serial.println("Hello ");
    for (;;)
    {
        FastLED.setBrightness(real_val);
        fill_rainbow(leds, NUM_LEDS, gHue, 7); // rainbow effect
        FastLED.show();                        // must be executed for neopixel becoming effective
        gHue++;

        //delay(delay_time);
        vTaskDelay(delay_time / portTICK_RATE_MS);
    }
}
void RGB_LEDshowTask(void *pvParameters)
{
    for (;;)
    {
        //delay(delay_time);
        vTaskDelay(delay_time / portTICK_RATE_MS); // This sends the updated pixel color to the hardware.
    }
}

void Angle_LEDshowTask(void *pvParameters)
{
    for (;;)
    {
        cur_angle = analogRead(Angle_PIN);
        mapValue = map(cur_angle, 0, 3900, 0, 255);
        if (abs(mapValue - last_sensorValue) > 5)
        { //debaunce
            real_val = mapValue > 5 ? mapValue : 0;
            Serial.println("Current angle : " + String(real_val));
            last_sensorValue = mapValue;
        }

        //delay(delay_time);
        vTaskDelay(delay_time / portTICK_RATE_MS);
    }
}

void ENV_showTask(void *pvParameters)
{
    for (;;)
    {
        tmp = dht12.readTemperature();
        humi = dht12.readHumidity();
        if (abs(tmp - last_tmp) > 0.2 || abs(humi - last_humi) > 0.2)
        {
            Serial.printf("Temperatura: %2.2f*C  Humedad: %0.2f%%  \r\n", tmp, humi);
            last_tmp = tmp;
            last_humi = humi;
        }

        //delay(delay_time);
        vTaskDelay(delay_time / portTICK_RATE_MS);
    }
}

void Button_Read_Task(void *pvParameters)
{
    for (;;)
    {

        if (M5.BtnA.wasPressed())
        {
            BTN_STA[0] = !BTN_STA[0];
            Serial.println("BTN A is " + String(BTN_STA[0]));
        }
        if (M5.BtnB.wasPressed())
        {
            BTN_STA[1] = !BTN_STA[1];
            Serial.println("BTN B is " + String(BTN_STA[1]));
        }
        if (M5.BtnC.wasPressed())
        {
            BTN_STA[2] = !BTN_STA[2];
            Serial.println("BTN C is " + String(BTN_STA[2]));
        }
        M5.update();

        //delay(delay_time);
        vTaskDelay(delay_time / portTICK_RATE_MS);
    }
}

void Display_show_Task(void *pvParameters)
{

    for (;;)
    {
        pixels.show();
        pixels.setPixelColor(0, pixels.Color(BTN_STA[0] ? RGB_COLOR[0] : 0, 0, 0)); // Moderately bright red color.
        pixels.show();
        pixels.setPixelColor(1, pixels.Color(0, BTN_STA[1] ? RGB_COLOR[1] : 0, 0)); // Moderately bright green color.
        pixels.show();
        pixels.setPixelColor(2, pixels.Color(0, 0, BTN_STA[2] ? RGB_COLOR[2] : 0)); // Moderately bright blue color.
        pixels.show();

        int space = 1;
        char buffer[50];
        M5.Lcd.setCursor(x_axis, y_asix + 10 * space++);
        M5.Lcd.println("LED Status A : ");
        M5.Lcd.setCursor(x_axis + 150, (y_asix + 10 * space) - 10);
        M5.Lcd.println(BTN_STA[0]);
        M5.Lcd.setCursor(x_axis, y_asix + 10 * space++);
        M5.Lcd.println("LED Status B : ");
        M5.Lcd.setCursor(x_axis + 150, (y_asix + 10 * space) - 10);
        M5.Lcd.println(BTN_STA[1]);
        M5.Lcd.setCursor(x_axis, y_asix + 10 * space++);
        M5.Lcd.println("LED Status C : ");
        M5.Lcd.setCursor(x_axis + 150, (y_asix + 10 * space) - 10);
        M5.Lcd.println(BTN_STA[2]);

        M5.Lcd.setCursor(x_axis, y_asix + 10 * space++);
        M5.Lcd.println("TEMP : ");
        M5.Lcd.setCursor(x_axis + 150, (y_asix + 10 * space) - 10);
        M5.Lcd.println(tmp);

        M5.Lcd.setCursor(x_axis, y_asix + 10 * space++);
        M5.Lcd.println("Humi : ");
        M5.Lcd.setCursor(x_axis + 150, (y_asix + 10 * space) - 10);
        M5.Lcd.println(humi);

        M5.Lcd.setCursor(x_axis, y_asix + 10 * space++);
        M5.Lcd.println("Angle : ");
        M5.Lcd.setCursor(x_axis + 150, (y_asix + 10 * space) - 10);
        sprintf(buffer, "%03d", map(real_val, 0, 255, 0, 100));
        M5.Lcd.println(buffer);
        //delay(delay_time);
        vTaskDelay(delay_time / portTICK_RATE_MS);
    }
}

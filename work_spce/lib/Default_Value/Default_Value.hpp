#define DrZin_WiFi_SSID "DrZin"
#define DrZin_WiFi_PASS "0985626152a"
#define HCRL_WiFi_SSID "HCRL-Edu"
#define HCRL_WiFi_PASS "Hybrid-6Zero7"
#define Defalult_Baud_Rate 115200
#define MY_MQTT_SERVER "161.246.6.147"
#define MY_MQTT_PORT 1883
#define HCRL_MQTT_SERVER "161.246.6.147"
#define HCRL_MQTT_PORT 1883
#define Default_WiFi_Task_Stack 4096
#define delay_Time 200
#define TaskDelay(Time) (delay(Time / portTICK_PERIOD_MS))
boolean debugging = true;
#define setDebugging(status) (debugging = status)
#define Sprintln(payload) (debugging ? Serial.println(payload) : 0)
#define Sprint(payload) (debugging ? Serial.print(payload) : 0)
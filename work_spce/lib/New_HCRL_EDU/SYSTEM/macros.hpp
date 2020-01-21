#ifndef System_Macros
#define System_Macros

#define HCRL_WiFi_SSID "MakeEdu"
#define HCRL_WiFi_PASS "Hybrid-6Zero7"
#define HCRL_MQTT_SERVER "161.246.6.147"
#define HCRL_MQTT_PORT 1883
#define MAX_SIZE 100
#define delay_Time 200
#define TaskDelay(Time) (delay(Time / portTICK_PERIOD_MS))
#define Sprintln(payload) (Serial.println(payload))
#define Sprint(payload) (Serial.print(payload))
#define Sec2MS(time) (time * 1000)
#endif
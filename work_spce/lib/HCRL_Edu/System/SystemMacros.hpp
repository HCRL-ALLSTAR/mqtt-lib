#ifndef System_Macros
#define System_Macros

#include <Arduino.h>
boolean debugging = true;
#define delay_Time 200
#define TaskDelay(Time) (delay(Time / portTICK_PERIOD_MS))
#define setDebugging(status) (debugging = status)
#define Sprintln(payload) (debugging ? Serial.println(payload) : 0)
#define Sprint(payload) (debugging ? Serial.print(payload) : 0)

#endif
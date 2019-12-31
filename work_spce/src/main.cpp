#include <TASK_LIB.h>

TASK_LIB myTask;
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    myTask.wifi_Begin(DrZin_WiFi_SSID, DrZin_WiFi_PASS);
}

void loop()
{
    TaskDelay(delay_Time);
}
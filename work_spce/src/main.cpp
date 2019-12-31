#include <TASK_LIB.h>

TASK_LIB myTask;
char list[512];
void setup()
{
    Serial.begin(Defalult_Baud_Rate);
    myTask.WiFi.Begin(DrZin_WiFi_SSID, DrZin_WiFi_PASS);
}

void loop()
{

    TaskDelay(delay_Time);
}
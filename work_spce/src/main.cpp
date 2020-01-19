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
}

void loop()
{
    hcrl.update(); //Update Data
}

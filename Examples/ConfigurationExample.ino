/**
 * LM92 Library
 * Kerry D. Wong
 * http://www.kerrywong.com
 * 1/2014
 *
 * Configuration example
 */

#include <LM92.h>
#include <Wire.h>

LM92 lm92;    
    
void setup()
{
    Wire.begin();
    Serial.begin(9600);
    
    lm92.setTLow(11);
    lm92.setTHigh(90);    
    lm92.setHysteresis(3);
    
    Serial.println(lm92.getManufacturerID());
    Serial.println(lm92.readConfigurationRegister());
    Serial.println(lm92.readHysteresis());
    Serial.println(lm92.readTLow());
    Serial.println(lm92.readTHigh());    
    Serial.println(lm92.readTCritical());
}

void loop()
{
    Serial.println(lm92.readTemperature());

    delay(500);
}

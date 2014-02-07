/**
 * LM92 Library
 * Kerry D. Wong
 * http://www.kerrywong.com
 * 1/2014
 *
 * Read temperature in Fahrenheit (default).
 */

#include <LM92.h>
#include <Wire.h>

LM92 lm92; //default constructor, address 0, 0   
    
void setup()
{
    Wire.begin();
    Serial.begin(9600);    
}

void loop()
{
    Serial.println(lm92.readTemperature());
    delay(500);
}

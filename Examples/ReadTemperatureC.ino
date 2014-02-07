/**
 * LM92 Library
 * Kerry D. Wong
 * http://www.kerrywong.com
 * 1/2014
 *
 * Read temperature in Celsius.
 */

#include <LM92.h>
#include <Wire.h>

LM92 lm92(1,0);  //address 1, 0
    
void setup()
{
    Wire.begin();
    Serial.begin(9600);  
  
    lm92.enableFaultQueue(true); //optional, make readings more tolerent to inteference
    lm92.ResultInCelsius = true;  //change to Celsius mode
}

void loop()
{
    Serial.println(lm92.readTemperature());
    delay(500);
}

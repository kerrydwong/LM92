#include "LM92.h"
/**
 * LM92 Library
 * Kerry D. Wong
 * http://www.kerrywong.com
 * 1/2014
 */

LM92::LM92()
{
	I2C_ADDRESS = BASE_I2C_ADDRESS;
	ResultInCelsius = false;
}

LM92::LM92(byte A1, byte A0)
{
	I2C_ADDRESS = BASE_I2C_ADDRESS | A1 << 1 | A0;
	ResultInCelsius = false;
}

double LM92::readTemperature() {
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(TEMPERATURE_REG_PTR);
	Wire.endTransmission();

	return readTemp();
}

double LM92::readTemp()
{
	long temp = readReg16() >> 3;
	double t;

	if (temp >= 8192)
		temp -= 8192;
	
	t = temp * 0.0625;

	if (!ResultInCelsius) t = t * 9.0 / 5.0 + 32.0;

	return t;
}
unsigned int LM92::getManufacturerID() 
{
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(ID_REG_PTR);
	Wire.endTransmission();

	return readReg16();
}

byte LM92::readConfigurationRegister()
{
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(CONFIG_REG_PTR);
	Wire.endTransmission();

	return readReg8();
}

double LM92::readHysteresis()
{
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(T_HYST_SET_REG_PTR);
	Wire.endTransmission();

	int temp = readReg16() >> 3;
	double t;
	
	if (temp >= 8192)
		temp -= 8192;
	
	t = temp * 0.0625;

	if (!ResultInCelsius) t = t * 9.0 / 5.0;

	return t;
}

double LM92::readTHigh()
{
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(T_HIGH_SET_REG_PTR);
	Wire.endTransmission();

	return readTemp();
}

double LM92::readTLow()
{
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(T_LOW_SET_REG_PTR);
	Wire.endTransmission();

	return readTemp();
}

double LM92::readTCritical()
{
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(T_CRIT_SET_REG_PTR);
	Wire.endTransmission();

	return readTemp();
}

void LM92::setHysteresis(double t) 
{
	t /= 0.0625;
	
	if (!ResultInCelsius) t = t * 5.0 / 9.0;

	int temp = (int) t << 3;
	byte low = temp & 0xff;
	byte high = (temp >> 8) & 0xff;
	
	//note, hysteresis can never be negative
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(T_HYST_SET_REG_PTR);
	Wire.write(high);
	Wire.write(low);
	Wire.endTransmission();
}

void LM92::setTHigh(double t)
{
	t /= 0.0625;
	
	if (!ResultInCelsius) t = t * 5.0 / 9.0;

	int temp = (int) t << 3;

	byte low = temp & 0xff;
	byte high = (temp >> 8) & 0xff;
	
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(T_HIGH_SET_REG_PTR);
	Wire.write(high);
	Wire.write(low);
	Wire.endTransmission();
}

void LM92::setTLow(double t)
{
	t /= 0.0625;
	
	if (!ResultInCelsius) t = t * 5.0 / 9.0;

	int temp = (int) t << 3;

	byte low = temp & 0xff;
	byte high = (temp >> 8) & 0xff;
	
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(T_LOW_SET_REG_PTR);
	Wire.write(high);
	Wire.write(low);
	Wire.endTransmission();
}

void LM92::setTCritical(double t)
{
	t /= 0.0625;
	
	if (!ResultInCelsius) t = t * 5.0 / 9.0;

	int temp = (int) t << 3;

	byte low = temp & 0xff;
	byte high = (temp >> 8) & 0xff;
	
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(T_CRIT_SET_REG_PTR);
	Wire.write(high);
	Wire.write(low);
	Wire.endTransmission();
}

byte LM92::readReg8()
{
    int temp;
    
    Wire.requestFrom(I2C_ADDRESS,2); 

    if (Wire.available()) 
    {
        temp = Wire.read();
    }

    return temp;
}

int LM92::readReg16()
{
    byte low, high;
    int temp;
    
    Wire.requestFrom(I2C_ADDRESS,2); 

    if (Wire.available()) 
    {
        high = Wire.read();
        low = Wire.read();
        temp = (high << 8) + low;
    }

    return temp;
}

void LM92::writeConfigReg(byte b)
{
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(CONFIG_REG_PTR);
	Wire.write(b);
	Wire.endTransmission();
}

void LM92::shutDown(bool shutdown)
{
	byte b = readConfigurationRegister();
	
	if (shutdown)
		b |= 0x1;
	else
		b &= ~0x1;
	
	writeConfigReg(b);
}

void LM92::enableFaultQueue(bool enable)
{
	byte b = readConfigurationRegister();
	
	if (enable)
		b |= 0x10;
	else
		b &= ~0x10;

	writeConfigReg(b);
}

void LM92::setINTMode(byte b)
{
	byte a = readConfigurationRegister();
	
	if (b == 0) 
		a &= ~0x2;
	else 
		a |= 0x2;

	writeConfigReg(a);
}

void LM92::setTCriticalPolarity(byte b)
{
	byte a = readConfigurationRegister();
	
	if (b == 0) 
		a &= ~0x4;
	else 
		a |= 0x4;

	writeConfigReg(a);
}

void LM92::setINTPolarity(byte b)
{
	byte a = readConfigurationRegister();
	
	if (b == 0) 
		a &= ~0x8;
	else 
		a |= 0x8;

	writeConfigReg(a);
}

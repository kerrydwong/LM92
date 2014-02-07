#ifndef LM92_H
#define LM92_H

/**
 * LM92 Library
 * Kerry D. Wong
 * http://www.kerrywong.com
 * 1/2014
 */
#include <Wire.h>
#include <Arduino.h>

class LM92 {
public: 
	static const int BASE_I2C_ADDRESS = 0x48;

	static const int TEMPERATURE_REG_PTR = 0x0;
	static const int CONFIG_REG_PTR = 0x1;
	static const int T_HYST_SET_REG_PTR = 0x2;
	static const int T_CRIT_SET_REG_PTR = 0x3;
	static const int T_LOW_SET_REG_PTR = 0x4;
	static const int T_HIGH_SET_REG_PTR = 0x5;
	static const int ID_REG_PTR = 0x7;

	int I2C_ADDRESS;	
	bool ResultInCelsius;//Celsius or Fahrenheit
	
	LM92();
	LM92(byte A1, byte A0); //Set Address

	double readTemperature();
	unsigned int getManufacturerID();
	byte readConfigurationRegister();
	double readHysteresis();
	double readTHigh();
	double readTLow();
	double readTCritical();
	void setHysteresis(double t);
	void setTHigh(double t);
	void setTLow(double t);
	void setTCritical(double t);

	void shutDown(bool shutdown);
	void enableFaultQueue(bool enable); //true: enable
					    //false: disable (default)
	void setINTMode(byte b); //0: Comparator interrupt mode (default)
				     //1: Event Interrupt mode
	void setTCriticalPolarity(byte b); //0: Active low (default)
					   //1: Active high
	void setINTPolarity(byte b); //0: Active low (default)
				     //1: Active high

private:
	double readTemp();

	byte readReg8();
	int readReg16();
	
	void writeConfigReg(byte b);
};
#endif

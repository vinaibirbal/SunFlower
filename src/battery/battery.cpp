#include "Arduino.h"
#include "battery.h"
#include "../hardware.h"

#define MaxVolt       8.3 
#define MinVolt       0
#define DivRatio      10/6
#define RefVolt       1024

Battery::Battery(float maxVolt, float minVolt, float refVolt, float divRatio, int batSense) {

	this->maxVolt = maxVolt;
	this->minVolt = minVolt;
    this->batSense = batSense;
    this->refVolt = refVolt;
    this->divRatio = divRatio;
}

Battery::Battery() {

	this->maxVolt = MaxVolt;
	this->minVolt = MinVolt;
    this->batSense = BSENSE;
    this->refVolt = RefVolt;
    this->divRatio = DivRatio;
}

float Battery::level(){

    return this->level(this->volt());
}

float Battery::level(float Volt) {
	if (Volt <= minVolt) {
		return 0;
	} else if (Volt >= maxVolt) {
		return 100;
	} else {
		return batEstimate(maxVolt, minVolt, Volt);
	}
}

float Battery::volt() {
	
	analogRead(batSense);
	delay(2); // allow the ADC to stabilize
	int voltage = analogRead(batSense) * divRatio * refVolt / 1024;
	return voltage;
}

// * c - c / (1 + k*x/v)^3

float Battery::batEstimate(float maxVolt, float minVolt, float Volt) {
	// slow
	// uint8_t result = 110 - (110 / (1 + pow(1.468 * (voltage - minVoltage)/(maxVoltage - minVoltage), 6)));

	// steep
	// uint8_t result = 102 - (102 / (1 + pow(1.621 * (voltage - minVoltage)/(maxVoltage - minVoltage), 8.1)));

	// normal
	float estimate = 105 - (105 / (1 + pow(1.724 * (Volt - minVolt)/(maxVolt - minVolt), 5.5)));
	return estimate >= 100 ? 100 : estimate;
}
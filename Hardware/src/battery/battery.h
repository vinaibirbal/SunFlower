#ifndef battery_h
#define battery_h

#include <Arduino.h>

class Battery {
    private:
		float minVolt;
		float maxVolt;
		float divRatio;
		int batSense;
	    float refVolt;

    public:

		Battery(float maxVolt, float minVolt, float refVolt, float divRatio, int batSense);
        Battery(); // constructor with default values
        float level(); // returns battery level
        float level(float volt);
		float volt(); //returns battery voltage in millivolts.
        float batEstimate(float maxVolt, float minVolt, float Volt);// estimates battery level	
};

#endif // BATTERY_H_


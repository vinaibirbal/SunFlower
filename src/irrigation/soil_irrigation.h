#include "Arduino.h"
#include "SHT31.h"

class IRRIGATION
{
    private:
        SHT31 sht;
        float sensorValue = 0;
    public:
        void setup();
        void tempHumidity();
        void tankWaterLevel();
        void readSoilMoisture();
        void soilMoisture();
        void waterPlant();
};
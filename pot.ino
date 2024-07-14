#include "src/hardware.h"
#include "src/movement/wheels.h"
#include "src/irrigation/soil_irrigation.h"
#include "src/solar_tracking/lightsensor.h"
#include "src/battery/battery.h"

WHEELS wheels;
IRRIGATION irrigation;
LDRS light_sensors;

void moveWheels(DIR optimal_dir)
{
  if(optimal_dir == CENTRE) wheels.haltWheels();
  else if(optimal_dir == FRONT) wheels.moveForward(200);
  else if(optimal_dir == BACK) wheels.moveBackward(200);
  else if(optimal_dir == RIGHT) wheels.moveLeft(200);
  else if(optimal_dir == LEFT) wheels.moveLeft(200);
}

void setup() {
  
  // Send debugging information via the Serial monitor
  Serial.begin(19200);

  // Subsystem Setup
  irrigation.setup();
}

void loop() {

  //********************** INDIVIDUAL SUBSYSTEM TESTS ********************** 
  
  // MECHANICAL TEST
  wheels.testmove();

  // IRRIGATION TEST
  // checks temperature, humidity, moisture content every 30 seconds
  irrigation.tempHumidity();    //check temperature and humidity of plant
  delay(1000);
  irrigation.tankWaterLevel();  //check water level in tank
  delay(1000);
  irrigation.soilMoisture();    //check soil moisture
  delay(1000);
  irrigation.tankWaterLevel();  //check water level
  // delay(30000);

  // LIGHT SENSORS
  light_sensors.readLightSensors();
  light_sensors.setOptDirLevel();
  light_sensors.printLightData();
  // delay(1000);

  //******************************* MAIN LOOP ******************************
  
  int health_check_timer = 0;
  
  // Get optimal light direction photoresistor readings
  light_sensors.readLightSensors();
  light_sensors.setOptDirLevel();
  light_sensors.printLightData();
  DIR optimal_dir = light_sensors.getOptDir();
  
  // Move/Stop pot in the optimal direction
  moveWheels(optimal_dir);

  if(health_check_timer % 150 == 0)
  {
    irrigation.tempHumidity();
    irrigation.tankWaterLevel();
    irrigation.soilMoisture();
    irrigation.tankWaterLevel();
  }

  delay(200);
  health_check_timer++;

}

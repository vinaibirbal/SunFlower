#include "hardware.h"
#include "motor.h"

MOTORS motors;

void setup() {
  Serial.begin(9600);
}

void loop() {
  motors.moveForward(250);
  delay(5000);
  motors.haltWheels(250, 'F');
  delay(15000);
}

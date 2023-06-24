#include "Arduino.h"
#include "hardware.h"
#include "irsensor.h"

void IR::setPin(int pin){
  pinMode(pin, INPUT);
  this->pin = pin;
  this->edgeFound = false;
}

bool IR::readIrSensor(){

  if(digitalRead(this->pin) == LOW){
    this->edgeFound = true;
    Serial.println("Edge detected");
  }
  else{
    this->edgeFound = false;
    Serial.println("Edge not detected");
  }

  return this->edgeFound;
}

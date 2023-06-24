#include "Arduino.h"
#include "ultrasonic.h"

const int trig_threshold = 5;

void UltraSonic::setPins(int trig, int echo) {
  this->trigPin = trig;
  this->echoPin = echo;
  this->objectFound = false;
  pinMode(this->trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(this->echoPin, INPUT); // Sets the echoPin as an Input
}

bool UltraSonic::readUltraSonic(){

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  float duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  this->distance = duration * 0.034 / 2;
  int obj_distance = this->distance;
  Serial.println(this->distance);
  
  if(obj_distance < trig_threshold){
    this->objectFound = true;
    Serial.println("Found an object. I should stop moving or not move");
  }
  else{
    this->objectFound = false;
    Serial.println("Object not in range");
  }

  return this->objectFound;

}

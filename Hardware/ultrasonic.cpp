#include "Arduino.h"
#include "hardware.h"
#include "ultrasonic.h"

void UltraSonic::setPins(int trig, int echo) {
    this->trigPin = trig;
    this->echoPin = echo;
}
void UltraSonic::setup(int trig, int echo) {
  
  this->trigPin = trig;
  this->echoPin = echo;
  this->trig = 5;
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
void UltraSonic::readUltraSonic(){

  setup();
    // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  this->distance = distance;
  if(distance > this->trig_dist){
    trig = true;
  }

}
int UltraSonic::getUltraSonic(){
    readUltraSonic();
    return this->distance;

}
void UltraSonic::setTrigLevel(int trig_dist){
    this->trigLevel = trig_dist;

}
void UltraSonic::printDistance(){

    Serial.println(this->distance);

}


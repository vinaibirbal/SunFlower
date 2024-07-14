#include "Arduino.h"
#include "hardware.h"
#include "motor.h"

/**
 *  Initialize Motor Driver
 *  @param input1     Direction pin 1
 *  @param input2     Direction pin 2
 *  @param input3     Direction pin 3
 *  @param input4     Direction pin 4
 */

MOTORS::MOTORS(){

  //Configure pins to behave as output
  pinMode(MD_IN1, OUTPUT);
  pinMode(MD_IN2, OUTPUT);

  INA1 = MD_IN1;
  INA2 = MD_IN2;

  digitalWrite(MD_IN1, LOW);
  digitalWrite(MD_IN2, LOW);

  pinMode(MD_IN3, OUTPUT);
  pinMode(MD_IN4, OUTPUT);

  INB1 = MD_IN3;
  INB2 = MD_IN4;

  digitalWrite(MD_IN3, LOW);
  digitalWrite(MD_IN4, LOW); 
}

void MOTORS::testmove(){

}

void MOTORS::haltWheels(int speed, char d){

  if((speed > 0) && (d == 'F')){
    while(speed >= 70){
        
        Serial.println(speed, DEC);

        moveForward(speed);

        speed = speed - 20;
        delay(250);
    }

    moveForward(0);
  }
}

void MOTORS::moveForward(int speed){

  analogWrite(INA1, speed);
  digitalWrite(INA2, LOW);

  digitalWrite(INB1, LOW);
  analogWrite(INB2, speed);
}

void MOTORS::moveBackward(int speed){

  digitalWrite(INA1, LOW);
  analogWrite(INA2, speed);
  
  analogWrite(INB1, speed);
  digitalWrite(INB2, LOW);

}

void MOTORS::move(int speed, bool dirction){

  if(direction){
    MoveForward(speed);
  }
  else{
    moveBackward(speed);
  }
}

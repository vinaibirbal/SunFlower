#include "Arduino.h"
#include "motordriver.h"

/**
 *  Initialize Motor Driver
 *  @param input1     Direction pin 1
 *  @param input2     Direction pin 2
 */

void MOTOR::initializeMotor(int input1, int input2){

  //Configure pins to behave as output
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);

  INA = input1;
  INB = input2;
}

/**
 *  Start the motor
 *  @param speed    Limit the speed of the motor from 75 to 255 where 255 is the fastest speed
 */
 
void MOTOR::setSpeed(byte direction, int speed){
  switch(direction){
    case HALT:
      digitalWrite(INA, LOW);
      digitalWrite(INB, LOW);
      break;
    case CLOCKWISE:
      analogWrite(INA, speed);
      digitalWrite(INB, LOW);
      break;
    case ANTICLOCKWISE:
      digitalWrite(INA, LOW);
      analogWrite(INB, speed);
  }
}

void MOTOR::halt(){
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
}

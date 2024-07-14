#include "Arduino.h"
#include "motordriver.h"
#include "../hardware.h"
#include "wheels.h"

/**
 *  Initialize Motor Driver
 *  @param input1     Direction pin 1
 *  @param input2     Direction pin 2
 */

WHEELS::WHEELS(){
    this->front_right.initializeMotor(MD1_IN2, MD1_IN1); //1 is PWM and 2 is DIR
    this->front_left.initializeMotor(MD1_IN3, MD1_IN4); //1 is PWM and 2 is DIR
    this->back_right.initializeMotor(MD2_IN4, MD2_IN3); //1 is DIR and 2 is PWM
    this->back_left.initializeMotor(MD2_IN1, MD2_IN2); //1 is PWM and 2 is PWM
}

void WHEELS::testmove(){
  this->front_right.setSpeed(0,0);
  this->front_left.setSpeed(0,0);
  delay(2000);
  this->front_right.setSpeed(CLOCKWISE,250);
  this->front_left.setSpeed(CLOCKWISE,250);
  delay(1000);
  this->front_right.setSpeed(0,0);
  this->front_left.setSpeed(0,0);
  delay(3000);
  this->front_right.setSpeed(ANTICLOCKWISE,250);
  this->front_left.setSpeed(ANTICLOCKWISE,250);
  delay(1000);
  this->front_right.setSpeed(0,0);
  this->front_left.setSpeed(0,0);
  delay(3000);
}

void WHEELS::haltWheels(){
  this->front_right.halt();
  this->front_left.halt();
  this->back_right.halt();
  this->back_left.halt();
}

void WHEELS::moveForward(const int speed){
  this->front_right.setSpeed(1,speed);
  this->front_left.setSpeed(1,speed);
  this->back_right.setSpeed(1,speed);
  this->back_left.setSpeed(1,speed);
}

void WHEELS::moveBackward(const int speed){
  this->front_right.setSpeed(2,speed);
  this->front_left.setSpeed(2,speed);
  this->back_right.setSpeed(2,speed);
  this->back_left.setSpeed(2,speed);  
}

void WHEELS::moveLeft(const int speed){
  this->front_right.setSpeed(1,speed);
  this->front_left.setSpeed(2,speed);
  this->back_right.setSpeed(2,speed);
  this->back_left.setSpeed(1,speed);  
}

void WHEELS::moveRight(const int speed){
  this->front_right.setSpeed(2,speed);
  this->front_left.setSpeed(1,speed);
  this->back_right.setSpeed(1,speed);
  this->back_left.setSpeed(2,speed);
}

void WHEELS::moveDiagonalRightForward(const int speed){
  this->front_left.setSpeed(1,speed);
  this->back_right.setSpeed(1,speed); 
}

void WHEELS::moveDiagonalLeftForward(const int speed){
  this->front_right.setSpeed(1,speed);
  this->back_left.setSpeed(1,speed);  
}

void WHEELS::moveDiagonalRightBackward(const int speed){
  this->front_right.setSpeed(2,speed);
  this->back_left.setSpeed(2,speed);   
}

void WHEELS::moveDiagonalLeftBackward(const int speed){
  this->front_left.setSpeed(2,speed);
  this->back_right.setSpeed(2,speed);  
}

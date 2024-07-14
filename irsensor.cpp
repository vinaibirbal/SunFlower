#include "Arduino.h"
#include "hardware.h"
#include "irsensor.h"


void IR::setPin(int pin){
    pinMode(pin, INPUT);
    this->pin = pin;
}
void IR::readIrSensor(){

    Serial.begin(9600);

    if(digitalRead(pin) == LOW){
       this->trig = true;
    }
    else{
        this->trig = false;
    }

}
bool IR::getIrTrig(int){

    readIrSensor();
    return this->trig;

}
void IR::printIrTrig(){
    if(ir_sensors){
        Serial.println("edge detected");
    }
    else{
        Serial.println("edge not detected");
    }
}



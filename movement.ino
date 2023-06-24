#include "hardware.h"
#include "motor.h"
#include "lightsensor.h"
#include "ultrasonic.h"
#include "irsensor.h"

MOTORS motors;
LDRS light_sensor;
UltraSonic forward_ultra;
UltraSonic back_ultra;
IR forward_ir;
IR back_ir;

enum States{	
    idle,
    light_sense,
    forward_move,
    backward_move,
    halt,
};

States nextState = idle;

bool direction = true; // true is forward, false is backward
int default_delay = 5000;//check light every 15 minutes = 900000
int poll_delay = 100; //delay between polling in ms
int disThresh = 5; //distance threshold in cm
const int speed = 150;

String moistureLow = "Soil moisture low";
String moistureHumid = "Soil moisture humid";
String moistureHigh = "Soil moisture high";

// Data packets can have the following structure:
// char megaData[] = "water level, pump, battery level"  
// char nanoData[] = "soil moisture" 
char megaData[3];
int intmegaData[4];
char nanoData[1];
byte counter = 0;

//add state markers to avoid infinite loop
//bool haltForward;
//bool haltBack;

void setup() {
  forward_ultra.setPins(forward_trig, forward_echo);
  back_ultra.setPins(back_trig, back_echo);
  
  forward_ir.setPin(ir_forward);
  back_ir.setPin(ir_back);

  pinMode(LDR1_OUT, INPUT);
  pinMode(LDR2_OUT, INPUT);
  pinMode(LDR3_OUT, INPUT);
  pinMode(LDR4_OUT, INPUT);

  pinMode(PUMP, OUTPUT);
  pinMode(water_trig, OUTPUT);
  pinMode(water_echo, INPUT);
  
  Serial.begin(9600);
  Serial1.begin(9600); //Use Tx1 (Pin D18) and Rx1 (Pin D19)
}

void loop() {
  
  switch(nextState){

    case idle:
      Serial.println("idle");
      motors.remainStop();
      delay(default_delay);
      
      //Should check here if receiving soil moisture low from RP2040 NANO
      if(Serial1.available() != 0){
        if(Serial1.read() == 0x03){ //received start flag
          do{
            byte m = Serial1.readBytesUntil(',',nanoData,1);
            nanoData[m] = '\0';
          }
        }
      }

      /*
      if (Serial1.available() > 0) {
        // read the incoming string:
        String incomingString = Serial1.readStringUntil('.');

        Serial.print("I received: ");
        Serial.println(incomingString);

        if(incomingString.equals(moistureLow)){
          //Check water level; turn on pump

          float waterLevel = readWaterLevel();

          if(waterLevel < 7){
            //Send message that water level is high. Turn on pump.
            Serial1.write("Water level high; turning on pump\n");
            waterPlant();
          }
          else if(waterLevel >=7){
            //Send message that water level is low. Do not turn on pump.
            Serial1.write("Water level low; not turning on pump\n");
          }
        }
        else if(incomingString.equals(moistureHigh) || incomingString.equals(moistureHumid)){
          //Check water level still. Do not turn on pump.
          float waterLevel = readWaterLevel();

          //Send message with water level to RP2040 Nano
          Serial1.write("Water level *** and turning on pump\n");
        }
      } */

      nextState = light_sense;
      Serial.println("going to sense light");
      break;
          
    case light_sense:
      delay(20);

      Serial1.write("Sensing light");
      Serial.println("Sensing Light");

      light_sensor.readLightSensors();
      light_sensor.setOptDirLevel();
      light_sensor.printLightData();
      
      if(light_sensor.getOptDir() == HALT){
        nextState = idle;
        Serial.println("optimal direction is centre. idle");
      } 
      else{
        direction = (light_sensor.getOptDir() == FRONT)? true : false;
        nextState = (light_sensor.getOptDir() == FRONT)? forward_move : backward_move;

        if(direction == true){
          Serial.println("moving forward");
        }
        else{
          Serial.println("moving backward");
        }
      }    
      break;

    case forward_move:
 
      delay(poll_delay);
      
   //   if(forward_ultra.readUltraSonic() || forward_ir.readIrSensor()){
      if(forward_ultra.readUltraSonic()){
        nextState = halt;
      }
      else{
        motors.moveForward(speed);
        delay(poll_delay);
        //motors.moveForward(0); //why are we setting it to zero here?
        nextState = light_sense;
      }
      break;

    case backward_move:
      
      delay(poll_delay);
      
    //  if(back_ultra.readUltraSonic() ||back_ir.readIrSensor()){
      if(back_ultra.readUltraSonic()){
        nextState = halt;
      }
      else{
        motors.moveBackward(speed);
        delay(poll_delay);
        //motors.moveBackward(0);
        nextState = light_sense;
      }
      break;

    case halt:
      Serial.println("in halt");
      if(direction){
        motors.moveBackward(speed);
        delay(2000);
        nextState = idle;
        Serial.println("going backward again");
      }
      else{
        motors.moveForward(speed);
        delay(2000);
        nextState = idle;
        Serial.println("going forward again");
      }
      delay(100);
      break;
  }
}

float readWaterLevel(){
  int timeTaken;
  float distance;

  digitalWrite(water_trig,LOW);
  delayMicroseconds(2);
  digitalWrite(water_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(water_trig,LOW);  
  timeTaken = pulseIn(water_echo, HIGH);

  if (timeTaken>0){
    distance = timeTaken/58.2;
    return distance;
  }
}

void waterPlant(){
  digitalWrite(PUMP, HIGH);
  delay(5000);
  digitalWrite(PUMP, LOW);
  Serial.println("Plant watering is complete");
}
  

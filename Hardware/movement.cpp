#include "hardware.h"
#include "motor.h"
#include "lightsensor.h"
#include "ultrasonic.h"
#include "irsensor.h"

//set pins in h file
int const forward_trig;
int const forward_echo;
int const back_trig;
int const back_echo;
int const ir_forward;
int const ir_back;

int speed = 100;


MOTORS motors;
LDRS light_sensor;
UltraSonic forward_ultra;
forward_ultra.setPins(forward_trig, forward_echo);
UltraSonic back_ultra;
back_ultra.setPins(back_trig, back_echo);
IR forward_ir;
forward_ir.setPin(ir_forward);
IR back_ir;
back_ir.setPin(ir_back);

//need to initialise pins

enum States
{	
    idle,
    light_sense,
    forward_move,
    back_move,
    halt
};

States nextState = Default;
bool direction = true; // true is forward, false is backward
int default_delay = 900000;//check light every 15 minutes
int poll_delay = 100; //delay between polling in ms
int disTresh = 5; //distance treshold in cm
//add state markers to avoid infinite loop
//bool haltForward;
//bool haltBack;


void setup() {
  Serial.begin(9600);
}

void loop() {
  switch(nextState)

   case idle:
    {
        delay(defaultdelay);
        nextState = light_sense;
          
    }
    break;

    case light_sense:
    {
        delay(20);
        light_sensor.getOptDir();
        if(light_sensor.opt_dir == CENTER){
            nextState = idle;
        } 
        else 
        {
            direction = (light_sense.opt_dir == FRONT) true ? false;
            nextState = (light_sense.opt_dir == FRONT) forward_move ? back_move;

        }    
          
    }
    break;

    case forward_move:
    {
        //check ir and ultra-sonic sensor
        forward_ultra.getUltraSonic();
        forward_ir.readIrSensor();

        delay(poll_delay);

        if(forward_ultra.trig || forward_ir.trig){
            nextState = halt;
            break;
        }
        else{
            motors.moveForward(speed);
            delay(poll_delay);
            motors.moveForward(0);
            nextState = light_sense;
        }
          
    }
    break;

    case back_move:
    {
//check ir and ultra-sonic sensor
        back_ultra.getUltraSonic();
        back_ir.readIrSensor();

        delay(poll_delay);

        if(back_ultra.trig ||back_ir.trig){
            nextState = halt;
            break;
        }
        else{
            motors.moveBackward(speed);
            delay(poll_delay);
            motors.moveBackward(0);
            nextState = light_sense;
        }
          
    }
    break;

    case halt:
    {
        if(direction){
            nextState = back_move;
        }
        else{
            nextState = forward_move;
        }
        direction = !direction;

        delay(100);
    }
    break;

    default:
        break;

}
#include "Arduino.h"
#include "../hardware.h"
#include "lightsensor.h"

void LDRS::readLightSensors()
{
    LDR[FRONT] = getLightLevel(analogRead(LDR1_OUT));
    LDR[BACK] = getLightLevel(analogRead(LDR2_OUT));
    LDR[LEFT] = getLightLevel(analogRead(LDR3_OUT));
    LDR[RIGHT] = getLightLevel(analogRead(LDR4_OUT));
}

LEVEL LDRS::getLightLevel(int ldr_value)
{
    LEVEL light_level;
    if (ldr_value < 20) {
        light_level = DARK;
    } else if (ldr_value < 600) {
        light_level = DIM;
    } else if (ldr_value < 850) {
        light_level = LIGHT; 
    } else if (ldr_value < 950) {
        light_level = BRIGHT;
    } else {
        light_level = VERY_BRIGHT;
    }
    return light_level;
}

void LDRS::setOptDirLevel()
{
    if(LDR[FRONT] == LDR[BACK] && LDR[BACK] == LDR[LEFT] && LDR[LEFT] == LDR[RIGHT]) {
        opt_dir = CENTRE;
        opt_level = LDR[FRONT];
        return;
    }
    
    opt_dir = FRONT;
    opt_level = LDR[FRONT];
    
    if(LDR[BACK] > opt_level) {
        opt_dir = BACK;
        opt_level = LDR[BACK];
    }

    int equal_ctr = 0;
    for(int i = 0; i < NUM_LDRS; i++)
    {
        if(i != opt_dir) {
            if(LDR[i] == opt_level)
            {
                equal_ctr++;
            }
        }
    }

    if(equal_ctr == 2) {
        opt_dir = CENTRE;
        return;
    }
}

DIR LDRS::getOptDir()
{
    return this->opt_dir;
}

LEVEL LDRS::getOptLevel()
{
    return this->opt_level;
}

void printLightLevel(LEVEL param)
{
    if(param == DIM) Serial.println("DIM");
    else if(param == DARK) Serial.println("DARK");
    else if(param == LIGHT) Serial.println("LIGHT");
    else if(param == BRIGHT) Serial.println("BRIGHT");
    else if(param == VERY_BRIGHT) Serial.println("VERY BRIGHT");
}

void printLightDir(DIR param)
{
    if(param == FRONT) Serial.println("FRONT");
    else if(param == BACK) Serial.println("BACK");
    else if(param == LEFT) Serial.println("LEFT");
    else if(param == RIGHT) Serial.println("RIGHT");
    else if(param == CENTRE) Serial.println("CENTRE");
}

void LDRS::printLightData()
{
    Serial.print("Front LDR = ");
    printLightLevel(LDR[FRONT]);
    Serial.print("Back LDR = ");
    printLightLevel(LDR[BACK]);
    Serial.print("Left LDR = ");
    printLightLevel(LDR[LEFT]);
    Serial.print("Right LDR = ");
    printLightLevel(LDR[RIGHT]);

    Serial.print("Optimal Direction = ");
    printLightDir(opt_dir);

    Serial.println();
}
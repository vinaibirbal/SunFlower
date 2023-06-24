#include "Arduino.h"
#include "lightsensor.h"
#include "hardware.h"

void LDRS::readLightSensors()
{
    LDR[F_LEFT] = getLightLevel(analogRead(LDR1_OUT));
    LDR[F_RIGHT] = getLightLevel(analogRead(LDR2_OUT));
    LDR[B_LEFT] = getLightLevel(analogRead(LDR3_OUT));
    LDR[B_RIGHT] = getLightLevel(analogRead(LDR4_OUT));
}

LEVEL LDRS::getLightLevel(int ldr_value)
{
    LEVEL light_level;
    Serial.println(ldr_value);
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
    if(LDR[F_LEFT] == LDR[F_RIGHT] && LDR[F_RIGHT] == LDR[B_LEFT] && LDR[B_LEFT] == LDR[B_RIGHT] && LDR[B_LEFT] == LDR[B_RIGHT]) {
        opt_dir = HALT;
        opt_level = LDR[F_LEFT];
        return;
    }

//    Serial.println(LDR[F_RIGHT]);
//    Serial.println(LDR[F_LEFT]);
//    Serial.println(LDR[B_RIGHT]);
//    Serial.println(LDR[B_LEFT]);
    
    float front= (float(LDR[F_RIGHT])+float(LDR[F_LEFT]))/2.0;
//    Serial.println(front);
    float back= (float(LDR[B_RIGHT])+float(LDR[B_LEFT]))/2.0;
//    Serial.println(back);

    if(front>back){
      opt_dir=FRONT;
    }
    else if (back>front){
      opt_dir=BACK;
    }
    else
      opt_dir=HALT;

    return;
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
    else if(param == HALT) Serial.println("HALT");
}

void LDRS::printLightData()
{
    Serial.print("F_LEFT LDR = ");
    printLightLevel(LDR[F_LEFT]);
    Serial.print("F_RIGHT LDR = ");
    printLightLevel(LDR[F_RIGHT]);
    Serial.print("B_Left LDR = ");
    printLightLevel(LDR[B_LEFT]);
    Serial.print("B_Right LDR = ");
    printLightLevel(LDR[B_RIGHT]);

    Serial.print("Optimal Direction = ");
    printLightDir(opt_dir);

    Serial.println();
}

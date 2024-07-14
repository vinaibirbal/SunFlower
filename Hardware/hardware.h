#include <Arduino.h>

/*
 *    Motor Driver 1: Controls the two motors
 *    @param  MD1_IN1 D44 (use ENA pin on shield)
 *    @param  MD1_IN2 D47
 *    @param  MD1_IN3 D46 (use ENB pin on shield)
 *    @param  MD1_IN4 D41
 *     
 *    IN1 IN2 GND VCC IN3 IN4
 *    PWM DIR         PWM DIR
 *    
 */

#define MD_IN1   44 
#define MD_IN2   7 //Or use 7 (PWM)
#define MD_IN3   46
#define MD_IN4   45 //Or use 45 (PWM)

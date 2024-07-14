#include <Arduino.h>

/*
 *    Motor Driver 1: Controls the front wheels
 *    @param  MD1_IN1 5
 *    @param  MD1_IN2 7
 *    @param  MD1_IN1 11
 *    @param  MD1_IN2 13
 *     
 *    IN1 IN2 GND VCC IN3 IN4
 *    PWM DIR         PWM DIR
 *    
 */

// MEGA
#define MD1_IN1   2  
#define MD1_IN2   38  
#define MD1_IN3   3 
#define MD1_IN4   41 

// UNO
// #define MD1_IN1   77 
// #define MD1_IN2   75  
// #define MD1_IN3   73
// #define MD1_IN4   71

/*
 *    Motor Driver 2: Controls the back wheels
 *    @param  MD2_IN1 2
 *    @param  MD2_IN2 3
 *    @param  MD2_IN1 4
 *    @param  MD2_IN2 9
 *    
 *    IN1 IN2 GND VCC IN3 IN4
 *    DIR PWM         PWM DIR
 */

// MEGA
#define MD2_IN1 40 
#define MD2_IN2 4 
#define MD2_IN3 5 
#define MD2_IN4 37 

// UNO
// #define MD2_IN1 59
// #define MD2_IN2 57
// #define MD2_IN3 55
// #define MD2_IN4 53


/*
 *    Light Dependent Resistor: Infers the Photoresistor values
 *    @param  LDR1_OUT
 *    @param  LDR2_OUT
 *    @param  LDR3_OUT
 *    @param  LDR4_OUT
 */
// MEGA
// #define LDR1_OUT 97
// #define LDR2_OUT 96
// #define LDR3_OUT 95
// #define LDR4_OUT 94

// UNO
#define LDR1_OUT A0
#define LDR2_OUT A4
#define LDR3_OUT A2
#define LDR4_OUT A3

/*
 *    Soil Irrigation: Reads the soil moisture, humidity, temperature and water level
 *    @param  SensorPin
 *    @param  trigPin
 *    @param  echoPin
 *    @param  mosfet
 */

// MEGA
#define SM      89
#define TRIG    15
#define ECHO    16
#define MOS     70

// UNO
// #define SM      A0
// #define TRIG    3
// #define ECHO    2
// #define MOS     6

/*
*   Battery: Estimates battery level
*   @param BatterySense
*/
#define BSENSE  87
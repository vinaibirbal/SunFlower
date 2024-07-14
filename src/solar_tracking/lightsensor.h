#ifndef lightsensor_h
#define lightsensor_h

#include "Arduino.h"

#define NUM_LDRS 4

enum DIR 
{
  FRONT,
  BACK,
  LEFT,
  RIGHT,
  CENTRE
};

enum LEVEL 
{
  DARK,
  DIM,
  LIGHT,
  BRIGHT,
  VERY_BRIGHT
};

// for now, it should stop when the light received on all the four sensors is equal
// with object detection, it would stop in the direction of most light, until it hits an object/edge, and or also when equal condition is met

// when timer runs out, read_all_sensors, set_optimal_direction, get_optimal_direction
// some way to set some condition flags to explore in a certain direction or give the next best optimal direction

class LDRS {
  private:
    DIR opt_dir;
    LEVEL opt_level;
    LEVEL LDR[NUM_LDRS];
  public:
    void readLightSensors();
    LEVEL getLightLevel(int);
    void setOptDirLevel();
    DIR getOptDir();
    LEVEL getOptLevel();
    void printLightData();
};

#endif
#ifndef ultrasonic_h
#define ultrasonic_h

#include "Arduino.h"

class UltraSonic{
  
  private:
    int distance;
    int trigPin;
    int echoPin;
    bool objectFound;

  public:
    void setPins(int trig, int echo);
    bool readUltraSonic();
};

#endif

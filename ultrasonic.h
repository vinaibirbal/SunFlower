#ifndef ultrasonic_h
#define ultrasonic_h

#include "Arduino.h"

class UltraSonic{
  private:
    int distance;
    int trig_dist;
    int trigPin;
    int echoPin;
    bool trig;

  public:
    void setPins(int trig, int echo);
    void setup(int trig, int echo);
    void readUltraSonic();
    int getUltraSonic(int);
    void setTrigLevel();
    void printDistance()
};

#endif

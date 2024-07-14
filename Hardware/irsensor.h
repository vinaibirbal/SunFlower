#ifndef irsensor_h
#define irsensor_h

#include "Arduino.h"


class IR{
  private:
    bool trig;
    int pin;
  public:
    void setPin(int pin);
    void readIrSensor();
    bool getIrTrig(int);
    void printIrTrig()
};

#endif
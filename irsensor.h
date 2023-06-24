#ifndef irsensor_h
#define irsensor_h

#include "Arduino.h"


class IR{
  private:
    bool edgeFound;
    int pin;
  public:
    void setPin(int pin);
    bool readIrSensor();
};

#endif

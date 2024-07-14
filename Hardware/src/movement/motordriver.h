#ifndef motordriver_h
#define motordriver_h

#include "Arduino.h"

#define HALT            0
#define CLOCKWISE       1
#define ANTICLOCKWISE   2

class MOTOR {
  private:
    int INA, INB;
    int dir;
    int _speed;
  public:
    void initializeMotor(int input1, int input2);
    void setSpeed(byte dir, int speed);
    void halt();
};

#endif

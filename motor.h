#ifndef motors_h
#define motors_h

#include "Arduino.h"

class MOTORS {
  private:
    int INA1, INA2;
    int INB1, INB2; 
    int speed;
    byte direction;
  public:
    MOTORS();
    void testmove();
    void haltWheels(int speed, char d);
    void moveForward(const int speed);
    void moveBackward(const int speed);
    void remainStop();
    //void move(int speed, bool direction)
};

#endif

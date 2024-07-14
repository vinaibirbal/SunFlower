#ifndef wheels_h
#define wheels_h

#include "Arduino.h"
#include "motordriver.h"

class WHEELS {
  private:
    MOTOR front_right;
    MOTOR front_left;
    MOTOR back_right;
    MOTOR back_left;
    int speed;
  public:
    WHEELS();
    void testmove();
    void haltWheels();
    void moveForward(const int speed);
    void moveBackward(const int speed);
    void moveLeft(const int speed);
    void moveRight(const int speed);
    void moveDiagonalRightForward(const int speed);
    void moveDiagonalLeftForward(const int speed);
    void moveDiagonalRightBackward(const int speed);
    void moveDiagonalLeftBackward(const int speed);
};

#endif

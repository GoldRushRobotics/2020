#ifndef __SENSORS_H__
#define __SENSORS_H__
#include <math.h>
class LightSensor {
private:
  int _pin = -1;
public:
  void attach(int);
  int read();
};

class Encoder {
private:
  static volatile double counter;
  double direction = 1;
  static void ai0();
  static void ai1();
public:
  void attach();
  void setDirection(double);
  void reset();
  double getTicks();
  double getDistance();
};

#endif

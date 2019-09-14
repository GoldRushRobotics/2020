/*
 * @Description Code for "theodore" using gyroscope and infrared sensors 
 * @Author Drive team
 */
#include <math.h>
#include <string.h>
#include <Servo.h>

#define BASE_SPEED 0.8
#define MAX_SPEED_MOD 0.2
#define SPEED_MULT 1024
#define TURN_MULT 0.1
#define TURN_POW 0.8
#define NULL_VALUE -9999

/*ADXL345  : Accelerometer
  HMC5843  : Magnetometer on SEN-10125
  HMC5883L : Magnetometer on SEN-10736
  ITG-3200 : Gyro */

Servo left;
Servo right;
char incomingData;

double headingOffset = 0;

double targetHeading = 0;

double signum(double value) {
  if (value > 0) return 1;
  if (value < 0) return -1;
  return 0;
}

double clip(double value, double minVal, double maxVal) {
  return min(max(value, minVal), maxVal);
}

bool isFacingForward = true;

double getHeading(String incomingData) {
  String yawString = "";
  Serial.print(incomingData);

  yawString = String(incomingData);//converts the incoming data 'char' type to string
  
  int equal = yawString.indexOf("=");// index of first = sign
  int comma = yawString.indexOf(","); //index of first comma
  yawString = yawString.substring(equal, comma); // returns substring from first equal to first comma
  
  double yaw = yawString.toDouble(); // parses the yawString String to a double type
  double heading = yaw - headingOffset + (isFacingForward ? 0 : 180);
  
  while (heading > 180) {
    heading -= 360;
  }
  while (heading < -180) {
    heading += 360;
  }
  return heading;
}


void setup() 
{
  Serial.begin(57600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  //left.attach(A0);
  //right.attach(A1);
  //headingOffset = getHeading();
}

void loop()
{
  double yaw = 0.0;
  if(Serial.available() > 0)
  {
    //analogWrite(3, 100);
    //analogWrite(5, 255);
    //incomingData = Serial.read();
    left.writeMicroseconds(2000);
    right.writeMicroseconds(-2000);
  /*
    double headingDiff = targetHeading - getHeading(incomingData);
    double speedModCalc = signum(headingDiff) * TURN_MULT * pow(abs(headingDiff), TURN_POW);
    double speedMod = clip(speedModCalc, -MAX_SPEED_MOD, MAX_SPEED_MOD);
    double rightPower = (BASE_SPEED + speedMod) * SPEED_MULT;
    double leftPower = (BASE_SPEED - speedMod) * SPEED_MULT;
    */
  }
}

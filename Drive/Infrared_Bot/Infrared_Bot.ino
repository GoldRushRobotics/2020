/*
 * @Description Code for "theodore" using gyroscope and infrared sensors 
 * @Author Drive team
 */
#include <math.h>
#include <ctype.h>
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
bool hasInitializedGyro = false;

double getHeading(double yaw) {
  double heading = yaw - headingOffset + (isFacingForward ? 0 : 180);
  
  while (heading > 180) {
    heading -= 360;
  }
  while (heading < -180) {
    heading += 360;
  }
  if (!hasInitializedGyro) {
    headingOffset = heading;
    hasInitializedGyro = true;
    return 0;
  }
  return heading;
}

bool isValidDouble(String s) {
  bool hasUsedDot = false;
  for (int i = 0; i < s.length(); i++) {
    char c = s.charAt(i);
    if (c == '-') {
      if (i > 0) {
        return false;
      }
    } else if (c == '.') {
      if (hasUsedDot) {
        return false;
      }
      hasUsedDot = true;
    } else if (!isDigit(c)) {
      return false;
    }
  }
  return true;
}

void actOnGyroReading(String dataLine)
{
  //Serial.println(dataLine);
  int equal = dataLine.indexOf("=");// index of first = sign
  int comma = dataLine.indexOf(","); //index of first comma
  String yawLine = dataLine.substring(equal+1, comma); // returns substring from first equal to first comma
  //Serial.println(String(equal) + ", " + String(comma) + ", " + yawLine);

  if (isValidDouble(yawLine)) {
    double yaw = yawLine.toDouble(); // parses the yawString String to a double type
    
    double headingDiff = targetHeading - getHeading(yaw);
    Serial.println(String(headingDiff));
    double speedModCalc = signum(headingDiff) * TURN_MULT * pow(abs(headingDiff), TURN_POW);
    double speedMod = clip(speedModCalc, -MAX_SPEED_MOD, MAX_SPEED_MOD);
    double rightPower = (BASE_SPEED + speedMod) * SPEED_MULT;
    double leftPower = (BASE_SPEED - speedMod) * SPEED_MULT;
  } else {
    Serial.println("ERROR FOUND MOTHAFUCKA!!! " + dataLine);
  }
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

String dataLine = "";
void loop()
{
  double yaw = 0.0;
  if(Serial.available() > 0)
  {
    //analogWrite(3, 100);
    //analogWrite(5, 255);
    bool isReading = false;
    incomingData = Serial.read();
    dataLine += String(incomingData);
    int newLine = dataLine.indexOf("\r");
    if (newLine > 0) {
      actOnGyroReading(dataLine);
      dataLine = "";
    }
    
    left.writeMicroseconds(2000);
    right.writeMicroseconds(-2000);
  }
}

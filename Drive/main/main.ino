#include <Servo.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>

#define DRIVE_BASE_SPEED 0.3
#define DRIVE_MAX_SPEED_MOD 0.1
#define DRIVE_TURN_MULT 0.06
#define DRIVE_TURN_POW 0.7
#define LIGHT_TURN_MOD 5 // degrees

#define TURN_MAX_SPEED_MOD 0.3
#define TURN_TURN_MULT 0.04
#define TURN_TURN_POW 0.5

#define SLOW_DOWN_FOR_READABILITY false
#define SLOW_DOWN_DELAY_TIME 100

Servo left;
Servo right;

double headingOffset = 0;
double targetHeading = 0;
double currHeading = 0;

Adafruit_BNO055 bno = Adafruit_BNO055(55);


void loop() {
  lineFollowForSeconds(6);
  turnToHeading(180);
  lineFollowForSeconds(6);
  turnToHeading(0);
}

void setup() {
  Serial.begin(9600);
  
  left.attach(A0);  // left servo
  right.attach(A1); // right servo

  pinMode(2, INPUT); // left light
  pinMode(3, INPUT); // right light

  // initialize the imu
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  Serial.println("IMU initialized!");
}

bool isValidDouble(String s) {
  bool hasUsedDigit = true;
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
    } else {
      hasUsedDigit = true;
    }
  }
  return hasUsedDigit;
}

double getHeading() {
  sensors_event_t event;
  bno.getEvent(&event);
  
  double heading = event.orientation.x - headingOffset - targetHeading;
  
  while (heading > 180) {
    heading -= 360;
  }
  while (heading < -180) {
    heading += 360;
  }
  return heading;
}

double signum(double value) {
  if (value > 0) return 1;
  if (value < 0) return -1;
  return 0;
}

double clip(double value, double minVal, double maxVal) {
  return min(max(value, minVal), maxVal);
}

void setPower(double leftPower, double rightPower)
{
  left.write(90 - leftPower * 90);
  right.write(90 + rightPower * 90);
}

void lineFollowGyroForSeconds(double seconds, double target) {
  unsigned long startTime = millis();
  while (millis() - startTime < seconds * 1000) {
    if (digitalRead(2) == 0 && digitalRead(3) == 1) {
      targetHeading = target - LIGHT_TURN_MOD; // turn left
    } else if (digitalRead(2) == 1 && digitalRead(3) == 0) {
      targetHeading = target + LIGHT_TURN_MOD; // turn right
    } else {
      targetHeading = target; // go straight
    }
    
    double heading = getHeading();
    Serial.println("Heading: " + String(heading));
    double speedModCalc = signum(heading) * DRIVE_TURN_MULT * pow(abs(heading), DRIVE_TURN_POW);
    double speedMod = clip(speedModCalc, -DRIVE_MAX_SPEED_MOD, DRIVE_MAX_SPEED_MOD);
    //Serial.println("Speed Mod: " + String(speedMod));
    double leftPower = (DRIVE_BASE_SPEED - speedMod);
    double rightPower = (DRIVE_BASE_SPEED + speedMod);
    setPower(leftPower, rightPower);
  }
}

void lineFollowForSeconds(double seconds) {
  unsigned long startTime = millis();
  while (millis() - startTime < seconds * 1000) {
    if (digitalRead(2) == 0 && digitalRead(3) == 1) {
      setPower(0.25, 0.5); // turn left
    } else if (digitalRead(2) == 1 && digitalRead(3) == 0) {
      setPower(0.5, 0.25); // turn right
    } else {
      setPower(0.5, 0.5); // go straight
    }
  }
}

void driveGyroForSeconds(double seconds, double target) {
  unsigned long startTime = millis();
  targetHeading = target;
  while (millis() - startTime < seconds * 1000) {
    double heading = getHeading();
    Serial.println("Heading: " + String(heading));
    double speedModCalc = signum(heading) * DRIVE_TURN_MULT * pow(abs(heading), DRIVE_TURN_POW);
    double speedMod = clip(speedModCalc, -DRIVE_MAX_SPEED_MOD, DRIVE_MAX_SPEED_MOD);
    //Serial.println("Speed Mod: " + String(speedMod));
    double leftPower = (DRIVE_BASE_SPEED - speedMod);
    double rightPower = (DRIVE_BASE_SPEED + speedMod);
    setPower(leftPower, rightPower);
  }
}

void lineFollow() {
  double startHeading = 0;//getHeading();
  while (true) {
    if (digitalRead(2) == 0 && digitalRead(3) == 1) {
      targetHeading = startHeading - LIGHT_TURN_MOD; // turn left
    } else if (digitalRead(2) == 1 && digitalRead(3) == 0) {
      targetHeading = startHeading + LIGHT_TURN_MOD; // turn right
    } else {
      targetHeading = startHeading; // go straight
    }
    
    double heading = getHeading();
    Serial.println("Heading: " + String(heading));
    double speedModCalc = signum(heading) * DRIVE_TURN_MULT * pow(abs(heading), DRIVE_TURN_POW);
    double speedMod = clip(speedModCalc, -DRIVE_MAX_SPEED_MOD, DRIVE_MAX_SPEED_MOD);
    //Serial.println("Speed Mod: " + String(speedMod));
    double leftPower = (DRIVE_BASE_SPEED - speedMod);
    double rightPower = (DRIVE_BASE_SPEED + speedMod);
    setPower(leftPower, rightPower);
  }
}

void turnToHeading(double target) {
  targetHeading = target;
  unsigned long startTime = millis();
  while (true) {
    double heading = getHeading();
    Serial.println("Heading: " + String(heading));
    double speedModCalc = signum(heading) * TURN_TURN_MULT * pow(abs(heading), TURN_TURN_POW);
    double speedMod = clip(speedModCalc, -TURN_MAX_SPEED_MOD, TURN_MAX_SPEED_MOD);
    //Serial.println("Speed Mod: " + String(speedMod));
    double leftPower = -speedMod;
    double rightPower = speedMod;
    setPower(leftPower, rightPower);
    if (abs(heading) > 3) {
      startTime = millis();
    } else {
      if (millis() - startTime > 200) {
        setPower(0, 0);
        return;
      }
    }
  }
}

void idle() {
  while (true) {
    delay(100);
  }
}

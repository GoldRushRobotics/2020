#include <Servo.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>
#include "Sensors.h"

#define SERVO_LEFT A0
#define SERVO_RIGHT A1

#define LIGHT_CENTER_LEFT 2
#define LIGHT_CENTER_RIGHT 3
#define LIGHT_OUTER_LEFT 4
#define LIGHT_OUTER_RIGHT 5

Servo servoLeft;
Servo servoRight;

LightSensor lightCenterLeft;
LightSensor lightCenterRight;
LightSensor lightOuterLeft;
LightSensor lightOuterRight;

double headingOffset = 0;
double targetHeading = 0;
double currHeading = 0;

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void loop() {
  setPower(1, 1);
  while(true) { delay(100); }
  lineFollowForSeconds(10);
  turnToHeading(180);
  lineFollowForSeconds(4);
  idle();
}

void setup() {
  Serial.begin(9600);
  
  servoLeft.attach(SERVO_LEFT);  // left servo
  servoRight.attach(SERVO_RIGHT); // right servo

  lightCenterLeft.attach(LIGHT_CENTER_LEFT);
  lightCenterRight.attach(LIGHT_CENTER_RIGHT);
  lightOuterLeft.attach(LIGHT_OUTER_LEFT);
  lightOuterRight.attach(LIGHT_OUTER_RIGHT);

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

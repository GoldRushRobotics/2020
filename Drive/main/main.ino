#include <Servo.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>
#include <math.h>
#include "Sensors.h"

#define SERVO_LEFT A0
#define SERVO_RIGHT A1

#define LIGHT_CENTER_LEFT 6
#define LIGHT_CENTER_RIGHT 7
#define LIGHT_OUTER_LEFT 4
#define LIGHT_OUTER_RIGHT 5

Servo servoLeft;
Servo servoRight;

Encoder enc;

LightSensor lightCenterLeft;
LightSensor lightCenterRight;
LightSensor lightOuterLeft;
LightSensor lightOuterRight;

double headingOffset = 0;
double targetHeading = 0;
double currHeading = 0;

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void loop() { //code that can be modified to make robot do whatever
  delay(1000);
  setPower(1);
  delay(10);
  setPower(0);
  
  driveDistance(100, 0.3);
  
  double currHeading = 90;
  turnToHeading(currHeading);
  driveDistanceOnHeading(100, 0.3, currHeading);
  idle();
}

/*
 * PIN LAYOUTS:
 * 
 * Encoder:
 * A -> 2
 * B -> 3
 * 
 * IMU:
 * SDA -> A4
 * SCL -> A5
 */

void setup() { //setups up all sensors / actuators
  Serial.begin(9600);
  
  servoLeft.attach(SERVO_LEFT);  // left servo
  servoRight.attach(SERVO_RIGHT); // right servo

  enc.attach();

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

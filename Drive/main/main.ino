#include <Servo.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>
#include <math.h>
#include "Sensors.h"

#define SERVO_LEFT 11
#define SERVO_RIGHT 10

#define LIGHT_LEFT 4
#define LIGHT_CENTER 8
#define LIGHT_RIGHT 7
#define grabberPin 4
#define STEPPER 5
#define STEPPER_DIR 6

#define RUN_STEPPER_CNT 3

Servo servoLeft;
Servo servoRight;

Encoder enc;

LightSensor lightLeft;
LightSensor lightCenter;
LightSensor lightRight;


double headingOffset = 0;
double targetHeading = 0;
double currHeading = 0;

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void loop() { //code that can be modified to make robot do whatever
  //Serial.println(enc.getTicks());  
  /*driveDistance(13, -.3);
  delay(1000);
  lineFollowForBarCount(5);
  idle();*/

//  delay(1000);
  //driveDistanceOnHeading(100, 0);
/*
  lineFollowForBarCount(5);

  delay(1000);
  turnToHeading(0);
  delay(300);
  driveDistanceOnHeading(6, 0);
  delay(300);
  turnToHeading(90);
  delay(300);
  driveDistanceOnHeading(30,90);
  delay(300);
  driveDistanceOnHeading(-30,90);
  delay(300);
  turnToHeading(0);
  delay(300);
  lineFollowForBarCount(1);
  delay(300);
  turnToHeading(0);  
  idle();*/
//  raiseStack(RUN_STEPPER_CNT);
//  delay(3000);
//  lowerStack(RUN_STEPPER_CNT);
//  delay(3000);
//  closeGrabber(2000);
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
 * 
 * LIGHT:
 * L -> 4
 * C -> 8
 * R -> 7
 */

void setup() { //setups up all sensors / actuators
  Serial.begin(9600);
  
  servoLeft.attach(SERVO_LEFT);  // left servo
  servoRight.attach(SERVO_RIGHT); // right servo
  
  pinMode(STEPPER, OUTPUT);
  pinMode(STEPPER_DIR, OUTPUT);
  enc.attach();
//  openGrabber(2000);
  
  lightLeft.attach(LIGHT_LEFT);
  lightCenter.attach(LIGHT_CENTER);
  lightRight.attach(LIGHT_RIGHT);
/*
  // initialize the imu
  if(!bno.begin())
  {
    // There was a problem detecting the BNO055 ... check your connections 
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  Serial.println("IMU initialized!");
  delay(500);
  headingOffset = getHeading();*/
}

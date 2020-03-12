#include <Servo.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>
#include <math.h>
#include "Sensors.h"

//could be switched digital pins 4-6
#define SERVO_LEFT_PIN 5
#define SERVO_RIGHT_PIN 6
#define SERVO_GRABBER_PIN 4 //servo for grabber
#define SERVO_DELIVER 11

#define LIGHT_LEFT_PIN A2
#define LIGHT_CENTER_PIN A6
#define LIGHT_RIGHT_PIN A3

//could be switched A0 or A1
#define STEPPER_PIN A0
#define STEPPER_DIR_PIN A1

#define RUN_STEPPER_CNT 3 //variable for the stepper count

Servo servoLeft;
Servo servoRight;
Servo grabber;
Servo deliverer;

Encoder enc;

LightSensor lightLeft;
LightSensor lightCenter;
LightSensor lightRight;


double headingOffset = 0;
double currHeading = 0;

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void loop() { //code that can be modified to make robot do whatever
  
  /*/ uncomment below when done --------------------
  openGrabber(300);
  lineFollowForBarCount(5);
  delay(1000);
  turnToHeading(0, true);
  delay(300);
  driveDistanceOnHeading(17, 0);
  delay(300);
  turnToHeading(90, true);
  delay(300);
  driveDistanceOnHeading(40, 88);
  delay(3000);
  closeGrabber(500);
  raiseStack(RUN_STEPPER_CNT);
  delay(1000);
  driveDistanceOnHeading(-40, 84);
  delay(300);
  turnToHeading(0);
  delay(300);
  lineFollowForBarCount(1);
  delay(300);
  turnToHeading(0, true);
  lowerStack(RUN_STEPPER_CNT);
  idle();
*/


// -----------------------------------------
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
  
  servoLeft.attach(SERVO_LEFT_PIN);  // left servo
  servoRight.attach(SERVO_RIGHT_PIN); // right servo
  deliverer.attach(SERVO_DELIVER);
  
  pinMode(STEPPER_PIN, OUTPUT);
  pinMode(STEPPER_DIR_PIN, OUTPUT);
  enc.attach();
  
  lightLeft.attach(LIGHT_LEFT_PIN);
  lightCenter.attach(LIGHT_CENTER_PIN);
  lightRight.attach(LIGHT_RIGHT_PIN);

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
  delay(3000);
  headingOffset = getHeading();
  Serial.println("Heading offset set to: " + String(headingOffset));

  deliverer.write(130);
}

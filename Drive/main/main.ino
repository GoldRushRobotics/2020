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

Encoder enc;

LightSensor lightLeft;
LightSensor lightCenter;
LightSensor lightRight;


double headingOffset = 0;
double currHeading = 0;

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void loop() { //code that can be modified to make robot do whatever
  /*driveDistance(13, -.3);
  delay(1000);
  lineFollowForBarCount(5);
  idle();*/
  //Serial.println(String(getHeading()));
  //Serial.println(String(lightLeft.read()) + "\t" + String(lightCenter.read()) + "\t" + String(lightRight.read()));
  //Serial.println(lightRight.read());
//  delay(1000);
  //driveDistanceOnHeading(100, 0);
  //Serial.println(enc.getTicks());

//  driveDistanceOnHeading(1000, 0);
//  setPower(0.5);
//  delay(5000);
//  setPower(0);
  
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
  driveDistanceOnHeading(-40, 84);
  delay(300);
  turnToHeading(0);
  delay(300);
  lineFollowForBarCount(1);
  delay(300);
  turnToHeading(0, true);
  idle();

  //raiseStack(RUN_STEPPER_CNT);
   // openGrabber(300);
//  delay(3000);
//  Serial.println("Lowering stack...");
////  lowerStack(RUN_STEPPER_CNT);
//  int run_cnt = RUN_STEPPER_CNT;
//  digitalWrite(STEPPER_DIR_PIN, HIGH); //Pull direction pin high to move in "reverse"
//  for(int x= 0; x<(1000*run_cnt); x++)  //Loop the stepping enough times for motion to be visible
//  {
//    digitalWrite(STEPPER_PIN, HIGH); //Trigger one step
//    delayMicroseconds(500);
//    digitalWrite(STEPPER_PIN, LOW); //Pull step pin low so it can be triggered again
//    delayMicroseconds(500);
//  }
//  Serial.println("Stack lowered!");
//  idle();
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
  
  pinMode(STEPPER_PIN, OUTPUT);
  pinMode(STEPPER_DIR_PIN, OUTPUT);
  enc.attach();
//  openGrabber(2000);
  
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
}

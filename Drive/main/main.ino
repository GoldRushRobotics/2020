#include <Servo.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>
#include <math.h>
#include "Sensors.h"

#define SERVO_LEFT 11
#define SERVO_RIGHT 10

#define LIGHT_CENTER_LEFT 6
#define LIGHT_LEFT 4
#define LIGHT_RIGHT 5

Servo servoLeft;
Servo servoRight;

Encoder enc;

LightSensor lightleft;
LightSensor lightCenter;
LightSensor lightRight;


double headingOffset = 0;
double targetHeading = 0;
double currHeading = 0;

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void loop() { //code that can be modified to make robot do whatever
  
  
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

  lightLeft.attach(LIGHT_LEFT);
  lightCenter.attach(LIGHT_CENTER_LEFT);
  lightRight.attach(LIGHT_RIGHT);

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

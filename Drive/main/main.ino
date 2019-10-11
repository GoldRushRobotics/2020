#include <Servo.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>

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

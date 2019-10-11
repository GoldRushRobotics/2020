#include <Servo.h>

#define DRIVE_SPEED 0.5
#define OFF_SUB 0.25

//initialize servos
Servo left;
Servo right;

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);  //left IR sensor
  pinMode(3, INPUT);  //right IR sensor
  left.attach(A0);  //left servo
  right.attach(A1); //right servo
}

void setPower(double leftPower, double rightPower)
{
  left.write(90 - leftPower * 90);
  right.write(90 + rightPower * 90);
}

void loop()
{
  int leftSensor = digitalRead(2);
  int rightSensor = digitalRead(3);

  Serial.print("Left\tRight\n");
  Serial.print(leftSensor);
  Serial.print("\t");
  Serial.print(rightSensor);
  Serial.print("\n\n");
  
  if (leftSensor == 0 && rightSensor == 0)  //white-white
  {
    //go straight
    //left.writeMicroseconds(1000);
    //right.writeMicroseconds(2000);

    setPower(DRIVE_SPEED, DRIVE_SPEED);
  }

  if (leftSensor == 0 && rightSensor == 1)  //white-black
  {
    //turn left
    //left.writeMicroseconds(1500);
    //right.writeMicroseconds(2000);

    setPower(DRIVE_SPEED - OFF_SUB, DRIVE_SPEED);
  }

  if (leftSensor == 1 && rightSensor == 0)  //black-white
  {
    //turn right
    //left.writeMicroseconds(1000);
    //right.writeMicroseconds(1500);

    setPower(DRIVE_SPEED, DRIVE_SPEED - OFF_SUB);
  }

  if (leftSensor == 1 && rightSensor == 1)  //black-black
  {
    //turn in a circle
    //left.writeMicroseconds(1000);
    //right.writeMicroseconds(1000);

    setPower(DRIVE_SPEED, DRIVE_SPEED);
  }
}

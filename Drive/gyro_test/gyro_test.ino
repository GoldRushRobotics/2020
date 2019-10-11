#include <Servo.h>

#define BASE_SPEED 0.5
#define MAX_SPEED_MOD 0.5
#define TURN_MULT 0.04
#define TURN_POW 0.8
#define NULL_VALUE -9999
#define CURR_HEADING_RATIO 0.2
#define CURR_HEADING_MAX_DIFF 10

#define SLOW_DOWN_FOR_READABILITY false
#define SLOW_DOWN_DELAY_TIME 100

enum DriveState {
  lineFollow,
  turn
};

DriveState state = lineFollow;

Servo left;
Servo right;

bool hasInitializedGyro = false;
double headingOffset = 0;
double targetHeading = 0;
double currHeading = 0;

void setup() {
  Serial.begin(57600);
  
  left.attach(A0);  // left servo
  right.attach(A1); // right servo
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

double getHeading(double yaw) {
  double heading = yaw - headingOffset - targetHeading;
  
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

void lineFollowAction(double heading) {
  Serial.println("Heading: " + String(heading));
  double speedModCalc = signum(heading) * TURN_MULT * pow(abs(heading), TURN_POW);
  double speedMod = clip(speedModCalc, -MAX_SPEED_MOD, MAX_SPEED_MOD);
  //Serial.println("Speed Mod: " + String(speedMod));
  double leftPower = (BASE_SPEED - speedMod);
  double rightPower = (BASE_SPEED + speedMod);
  setPower(leftPower, rightPower);
}

void turnAction(double heading) {
  Serial.println("ERROR: not yet implemented");
}

void updateHeading() {
  // put your main code here, to run repeatedly:
  char buff[100];
  int amnt = Serial.readBytesUntil('\n', buff, 100);
  String dataLine = String(buff);
  //Serial.println(String(amnt) + ", " + message);

  // make sure the message exists
  if (amnt <= 0) {
    Serial.println("ERROR: serial read amount 0 MOTHAFUCKA");
    return;
  }

  // parse the message for yaw
  int equal = dataLine.indexOf("=");// index of first = sign
  int comma = dataLine.indexOf(","); //index of first comma
  String yawLine = dataLine.substring(equal+1, comma); // returns substring from first equal to first comma
  
  // check to see if yaw is a double
  if (!isValidDouble(yawLine)) {
    Serial.println("ERROR: yawLine [" + String(yawLine) + "] is not a double MOTHAFUCKA");
    return;
  }

  // convert yaw to a double
  double yaw = yawLine.toDouble();
  //Serial.println("BLAM! " + String(yaw));

  // act on the yaw
  double heading = getHeading(yaw);
  double currHeadingDiff = signum(heading - currHeading) * min(abs(heading - currHeading), CURR_HEADING_MAX_DIFF); // find our difference between heading and currHeading, clip to 10
  currHeading += currHeadingDiff * CURR_HEADING_RATIO; // add 20% of diff to currHeading
}

void loop() {
  updateHeading();
  
  if (state == lineFollow) {
    lineFollowAction(currHeading);
  } else if (state == turn) {
    turnAction(currHeading);
  }

  // sleep to allow for reading of values
  if (SLOW_DOWN_FOR_READABILITY) delay(SLOW_DOWN_DELAY_TIME);
}

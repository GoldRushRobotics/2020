#define DRIVE_BASE_SPEED 0.3
#define DRIVE_MAX_SPEED_MOD 0.1
#define DRIVE_TURN_MULT 0.06
#define DRIVE_TURN_POW 0.7
#define LIGHT_TURN_MOD 5

#define TURN_MAX_SPEED_MOD 0.3
#define TURN_TURN_MULT 0.04
#define TURN_TURN_POW 0.5

#define LF_BASE_SPEED 0.5
#define LF_SPEED_MOD 0.25

void driveDistance(double distance) {
  setPower(0, 0);
  while (true) {
    double d = readDouble();
    if (d != -99) {
      Serial.println("Setting drive speed to " + String(d));
      setPower(d, d);
    }
    Serial.println("Left: " + String(servoLeft.read()) + "\tRight: " + String(servoRight.read()));
    delay(100);
  }
}

void lineFollowForBarCount(int barCount) {
  bool prevSeeWhite = true;
  int currBarCount = 0;
  while (currBarCount < barCount) {
    lineFollowLoopIteration();

    bool currSeeWhite = lightOuterLeft.read() == 1 && lightOuterRight.read() == 1;
    if (!prevSeeWhite && currSeeWhite) {
      currBarCount++;
    }
    prevSeeWhite = currSeeWhite;
  }
}

void lineFollowForSeconds(double seconds) {
  unsigned long startTime = millis();
  while (millis() - startTime < seconds * 1000) { //loop until seconds is reached
    lineFollowLoopIteration();
  }
}

void lineFollowLoopIteration() { //stays on the line with infrared sensors
  if (lightCenterLeft.read() == 0 && lightCenterRight.read() == 1) {
    setPower(LF_BASE_SPEED - LF_SPEED_MOD, LF_BASE_SPEED); // turn left
  } else if (lightCenterLeft.read() == 1 && lightCenterRight.read() == 0) {
    setPower(LF_BASE_SPEED, LF_BASE_SPEED - LF_SPEED_MOD); // turn right
  } else {
    setPower(LF_BASE_SPEED, LF_BASE_SPEED); // go straight
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
  setPower(0, 0);
  while (true) {
    delay(100);
  }
}






/* old and should(?) not be used

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

*/

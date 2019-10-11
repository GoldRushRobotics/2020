#define DRIVE_BASE_SPEED 0.3
#define DRIVE_MAX_SPEED_MOD 0.1
#define DRIVE_TURN_MULT 0.06
#define DRIVE_TURN_POW 0.7
#define LIGHT_TURN_MOD 5 // degrees

#define TURN_MAX_SPEED_MOD 0.3
#define TURN_TURN_MULT 0.04
#define TURN_TURN_POW 0.5

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

void lineFollowForSeconds(double seconds) {
  unsigned long startTime = millis();
  while (millis() - startTime < seconds * 1000) {
    if (digitalRead(2) == 0 && digitalRead(3) == 1) {
      setPower(0.25, 0.5); // turn left
    } else if (digitalRead(2) == 1 && digitalRead(3) == 0) {
      setPower(0.5, 0.25); // turn right
    } else {
      setPower(0.5, 0.5); // go straight
    }
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
  while (true) {
    delay(100);
  }
}

#define DRIVE_BASE_SPEED 0.3
#define DRIVE_MAX_SPEED_MOD 0.1
#define DRIVE_TURN_MULT 0.02
#define DRIVE_TURN_POW 0.7
#define LIGHT_TURN_MOD 5

#define TURN_MAX_SPEED_MOD 0.3
#define TURN_MIN_SPEED 0.1
#define TURN_TURN_MULT 0.03
#define TURN_TURN_POW 0.5
#define TURN_DEGREE_CUTOFF 5

#define LF_BASE_SPEED 0.5
#define LF_SPEED_MOD 0.25

void driveDistance(double distance, double power) {
  Serial.println("Driving distance of " + String(distance) + " cm");
  if (distance == 0 || power == 0) {
    return;
  }
  if (distance < 0) {
    power *= -1;
  }
  
  enc.reset();
  double ticks = abs(distanceToTicks(distance));
  Serial.println(String(ticks));

  setPower(power);
  while (abs(enc.getTicks()) < ticks) {
    Serial.println(String(enc.getTicks()));
    setPower(power);
    delay(10);
  }
  setPower(0);
}

void driveDistanceOnHeading(double distance, double power, double target) {
  //Serial.println("Driving distance of " + String(distance) + " cm at heading " + String(target));
  if (distance == 0 || power == 0) {
    return;
  }
  if (distance < 0) {
    power *= -1;
  }
  
  enc.reset();
  double ticks = abs(distanceToTicks(distance));
  targetHeading = target;
  
  setPower(power);
  unsigned long startTime = millis();
  while (abs(enc.getTicks()) < ticks) {
    double heading = getHeading();
//    Serial.println("Heading: " + String(heading) + "\tEncoder: " + String(enc.getTicks()));
    //Serial.println(String(millis() - startTime) + "," + String(enc.getTicks()));
    Serial.print(millis() - startTime); Serial.print(", "); Serial.println(enc.getTicks());
    double speedModCalc = signum(heading) * DRIVE_TURN_MULT * pow(abs(heading), DRIVE_TURN_POW);
    double speedMod = clip(speedModCalc, -DRIVE_MAX_SPEED_MOD, DRIVE_MAX_SPEED_MOD);
    double leftPower = (DRIVE_BASE_SPEED - speedMod);
    double rightPower = (DRIVE_BASE_SPEED + speedMod);
    setPower(leftPower, rightPower);
  }
  setPower(0);
}

void lineFollowForBarCount(int barCount) {
  Serial.println("Following line for " + String(barCount) + " bars");
  bool prevSeeWhite = true;
  int currBarCount = 0;
  while (currBarCount < barCount) {
    lineFollowLoopIteration();

    bool currSeeWhite = lightLeft.read() == 1 && lightRight.read() == 1;
    if (!prevSeeWhite && currSeeWhite) {
      currBarCount++;
    }
    prevSeeWhite = currSeeWhite;
  }
}

void lineFollowForSeconds(double seconds) {
  Serial.println("Following line for " + String(seconds) + " seconds");
  unsigned long startTime = millis();
  while (millis() - startTime < seconds * 1000) { //loop until seconds is reached
    lineFollowLoopIteration();
  }
}

void lineFollowLoopIteration() { //stays on the line with infrared sensors
  if (lightLeft.read() == 1 && lightRight.read() == 1) {
    setPower(LF_BASE_SPEED, LF_BASE_SPEED); // go straight
  } 
  else if (lightCenter.read() == 1) {
    setPower(LF_BASE_SPEED - LF_SPEED_MOD, LF_BASE_SPEED); // turn left
  }
  else if (lightCenter.read() == 0) {
    setPower(LF_BASE_SPEED, LF_BASE_SPEED - LF_SPEED_MOD); // turn right
  }
}

void getOffBlock(){
    setPower(1,1);

    while(true){
      if(lightLeft.read() == 1 && lightRight.read() == 1) {
    }
    else {
      return;
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
  Serial.println("Turning to heading " + String(target));
  targetHeading = target;
  unsigned long startTime = millis();
  while (true) {
    double heading = getHeading();
    Serial.println("Heading: " + String(heading));
    double speedModCalc = signum(heading) * TURN_TURN_MULT * pow(abs(heading), TURN_TURN_POW);
    double speedMod = clip(speedModCalc, -TURN_MAX_SPEED_MOD, TURN_MAX_SPEED_MOD);
    //Serial.println("Speed Mod: " + String(speedMod));
    if (abs(heading) > TURN_DEGREE_CUTOFF) {
      startTime = millis();
      if (abs(speedMod) < TURN_MIN_SPEED) {
        speedMod = signum(speedMod) * TURN_MIN_SPEED;
      }
    } else {
      if (millis() - startTime > 200) {
        setPower(0, 0);
        return;
      }
    }
    double leftPower = -speedMod;
    double rightPower = speedMod;
    setPower(leftPower, rightPower);
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

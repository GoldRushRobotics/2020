#define DRIVE_BASE_SPEED 0.15
#define DRIVE_MAX_SPEED_MOD 0.08
#define DRIVE_TURN_MULT 0.01
#define DRIVE_TURN_POW 1.0
#define LIGHT_TURN_MOD 5

#define TURN_MAX_SPEED_MOD 0.4
#define TURN_MIN_SPEED 0.15
#define TURN_TURN_MULT 0.02
#define TURN_TURN_POW 0.5
#define TURN_DEGREE_CUTOFF 4

#define LF_BASE_SPEED 0.15
#define LF_SPEED_MOD 0.025

#define SERVO_GRABBER_OPEN_POS 100
#define SERVO_GRABBER_CLOSE_POS 52

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
//void driveDistanceOnHeadingBar(double distance, double targetHeading, bool bar) {
//  driveDistanceOnHeading(double distance, 
//}

void driveDistanceOnHeading(double distance, double targetHeading) {
  //Serial.println("Driving distance of " + String(distance) + " cm at heading " + String(target));
  if (distance == 0) {// || power == 0) {
    return;
  }

  
  enc.reset();
  double ticks = abs(distanceToTicks(distance));
  double dir = signum(distance);
  bool currSeeWhite = false;

  setPower(DRIVE_BASE_SPEED * dir);
  while (abs(enc.getTicks()) < ticks) {
    /*if(currSeeWhite = lightLeft.read() == 1 && lightRight.read() == 1) {
      setPower(0);
      return;
    }*/
    driveGyroLoopIteration(targetHeading, dir);
  }
  setPower(0);
}

void driveGyroLoopIteration(double targetHeading, double dir) {
    double heading = getHeadingDiff(targetHeading);
    Serial.println("Heading: " + String(heading));
    double speedModCalc = signum(heading) * DRIVE_TURN_MULT * pow(abs(heading), DRIVE_TURN_POW);
    double speedMod = clip(speedModCalc * dir, -DRIVE_MAX_SPEED_MOD, DRIVE_MAX_SPEED_MOD);
    double leftPower = DRIVE_BASE_SPEED - speedMod;
    double rightPower = DRIVE_BASE_SPEED + speedMod;
    setPower(leftPower * dir, rightPower * dir);
}

void lineFollowForBarCount(int barCount) {
  lineFollowForBarCount(barCount, 0);
}

void lineFollowForBarCount(int barCount, double targetHeading) {
  Serial.println("Following line for " + String(barCount) + " bars");
  bool prevSeeWhite = true;
  int currBarCount = 0;
  while (currBarCount < barCount) {
//    Serial.println("Gyro heading: " + String(getHeadingDiff(targetHeading)) + ", " + String(headingOffset));
    bool currSeeWhite = lightLeft.read() == 1 && lightRight.read() == 1;
    if (currSeeWhite) {
      driveGyroLoopIteration(targetHeading, 1.0);
    }
    else {
      lineFollowLoopIteration();
    }
    if (!prevSeeWhite && currSeeWhite) {
      currBarCount++;
    }
    prevSeeWhite = currSeeWhite;
  }
  setPower(0);
}

void lineFollowForBarCountInverse(int barCount, double targetHeading) {
  Serial.println("Following line for " + String(barCount) + " bars");
  bool prevSeeWhite = true;
  int currBarCount = 0;
  while (currBarCount < barCount) {
//    Serial.println("Gyro heading: " + String(getHeadingDiff(targetHeading)) + ", " + String(headingOffset));
    bool currSeeWhite = lightLeft.read() == 1 && lightRight.read() == 1;
    if (currSeeWhite) {
      driveGyroLoopIteration(targetHeading, 1.0);
    }
    else {
      lineFollowLoopIterationInverse();
    }
    if (!prevSeeWhite && currSeeWhite) {
      currBarCount++;
    }
    prevSeeWhite = currSeeWhite;
  }
  setPower(0);
}

void lineFollowForSeconds(double seconds) {
  Serial.println("Following line for " + String(seconds) + " seconds");
  unsigned long startTime = millis();
  while (millis() - startTime < seconds * 1000) { //loop until seconds is reached
    lineFollowLoopIteration();
  }
}

void lineFollowLoopIteration() { //stays on the line with infrared sensors
//  if (lightLeft.read() == 1 && lightRight.read() == 1) {
////    setPower(LF_BASE_SPEED, LF_BASE_SPEED); // go straight
//    // should not get here
//  } 
//  else 
  if (lightCenter.read() == 1) {
    setPower(LF_BASE_SPEED - LF_SPEED_MOD, LF_BASE_SPEED + LF_SPEED_MOD); // turn left
  }
  else {
    setPower(LF_BASE_SPEED + LF_SPEED_MOD, LF_BASE_SPEED - LF_SPEED_MOD); // turn right
  }
}

void lineFollowLoopIterationInverse() { //stays on the line with infrared sensors
  if (lightCenter.read() == 1) {
    setPower(LF_BASE_SPEED + LF_SPEED_MOD, LF_BASE_SPEED - LF_SPEED_MOD); // turn right
  }
  else {
    setPower(LF_BASE_SPEED - LF_SPEED_MOD, LF_BASE_SPEED + LF_SPEED_MOD); // turn left
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

void driveGyroForSeconds(double seconds, double targetHeading) {
  unsigned long startTime = millis();
  while (millis() - startTime < seconds * 1000) {
    double heading = getHeadingDiff(targetHeading);
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
  double targetHeading = 0;
  while (true) {
    if (digitalRead(2) == 0 && digitalRead(3) == 1) {
      targetHeading = startHeading - LIGHT_TURN_MOD; // turn left
    } else if (digitalRead(2) == 1 && digitalRead(3) == 0) {
      targetHeading = startHeading + LIGHT_TURN_MOD; // turn right
    } else {
      targetHeading = startHeading; // go straight
    }
    
    double heading = getHeadingDiff(targetHeading);
    Serial.println("Heading: " + String(heading));
    double speedModCalc = signum(heading) * DRIVE_TURN_MULT * pow(abs(heading), DRIVE_TURN_POW);
    double speedMod = clip(speedModCalc, -DRIVE_MAX_SPEED_MOD, DRIVE_MAX_SPEED_MOD);
    //Serial.println("Speed Mod: " + String(speedMod));
    double leftPower = (DRIVE_BASE_SPEED - speedMod);
    double rightPower = (DRIVE_BASE_SPEED + speedMod);
    setPower(leftPower, rightPower);
  }
}

void turnToHeading(double targetHeading) {
  turnToHeading(targetHeading, false);
}

void turnToHeading(double targetHeading, bool goSofter) {
  Serial.println("Turning to heading " + String(targetHeading));
  unsigned long startTime = millis();
  while (true) {
    double heading = getHeadingDiff(targetHeading);
    Serial.println("Heading: " + String(heading));
    double speedModCalc = signum(heading) * TURN_TURN_MULT * pow(abs(heading), TURN_TURN_POW);
    double speedMod = clip(speedModCalc, -TURN_MAX_SPEED_MOD, TURN_MAX_SPEED_MOD);
    //Serial.println("Speed Mod: " + String(speedMod));
    if (abs(heading) > TURN_DEGREE_CUTOFF) {
      startTime = millis();
      if (abs(speedMod) < TURN_MIN_SPEED) {
//        speedMod = signum(speedMod) * TURN_CONST_SPEED;
        speedMod = signum(speedMod) * TURN_MIN_SPEED;
      }
    } else {
      if (millis() - startTime > 200) {
        setPower(0, 0);
        return;
      }
    }
    if (goSofter) {
      speedMod *= 0.50;
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

void raiseStack(int run_cnt)
{
  digitalWrite(STEPPER_DIR_PIN, LOW); //Pull direction pin low to move "forward"
  for(int x= 0; x<(1000*run_cnt); x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(STEPPER_PIN ,HIGH); //Trigger one step forward
    delayMicroseconds(500);
    digitalWrite(STEPPER_PIN,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(500);
  }
}

//Reverse default microstep mode function
void lowerStack(int run_cnt)
{
  digitalWrite(STEPPER_DIR_PIN, HIGH); //Pull direction pin high to move in "reverse"
  for(int x= 0; x<(1000*run_cnt); x++)  //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(STEPPER_PIN, HIGH); //Trigger one step
    delayMicroseconds(500);
    digitalWrite(STEPPER_PIN, LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(500);
  }
}

void closeGrabber(int delay_msc){
  grabber.attach(4);
  grabber.write(SERVO_GRABBER_CLOSE_POS); // close position
  delay(delay_msc);
}

void openGrabber(int delay_msc) {
  grabber.attach(4);
  grabber.write(SERVO_GRABBER_OPEN_POS); // open position
  delay(delay_msc);
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

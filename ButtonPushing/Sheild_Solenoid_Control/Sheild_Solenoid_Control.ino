#include <TLE94112.h>
#include <Tle94112Motor.h>
#include "pi2000.h"

// Tle94112 Object
Tle94112 controller = Tle94112();

// Tle94112Motor Objects
Tle94112Motor solenoid0(controller);
Tle94112Motor solenoid1(controller);
Tle94112Motor solenoid2(controller);
Tle94112Motor solenoid3(controller);
Tle94112Motor solenoid4(controller);
Tle94112Motor solenoid5(controller);
Tle94112Motor solenoid6(controller);
Tle94112Motor solenoid7(controller);
Tle94112Motor solenoid8(controller);
Tle94112Motor solenoid9(controller);


void setup() {
  // Enable MotorController Tle94112
  // Note: Required to be done before starting to configure the solenoid
  controller.begin();
  
  // Connect solenoid1 to HB1 and so on...
  solenoid1.connect(solenoid1.HIGHSIDE, controller.TLE_HB1);
  
  solenoid2.connect(solenoid2.HIGHSIDE, controller.TLE_HB2);

  solenoid3.connect(solenoid3.HIGHSIDE, controller.TLE_HB3);
  
  solenoid4.connect(solenoid4.HIGHSIDE, controller.TLE_HB4);

  solenoid5.connect(solenoid5.HIGHSIDE, controller.TLE_HB5);
  
  solenoid6.connect(solenoid6.HIGHSIDE, controller.TLE_HB6);

  solenoid7.connect(solenoid7.HIGHSIDE, controller.TLE_HB7);

  solenoid8.connect(solenoid8.HIGHSIDE, controller.TLE_HB8);

  solenoid9.connect(solenoid9.HIGHSIDE, controller.TLE_HB9);

  solenoid0.connect(solenoid0.HIGHSIDE, controller.TLE_HB10);
  
  //when configuration is done, call begin to start operating the solenoids
  solenoid0.begin();
  solenoid1.begin();
  solenoid2.begin();
  solenoid3.begin();
  solenoid4.begin();
  solenoid5.begin();
  solenoid6.begin();
  solenoid7.begin();
  solenoid8.begin();
  solenoid9.begin();
  
  //after calling begin(), the solenoids are active. 
}


void loop() {
  for(int i = 0; i < 2001; i++){
      char c = pi[i];
      if(c == '0'){
        solenoid0.setSpeed(255);
        delay(25);
        solenoid0.setSpeed(0);
      } else if(c == '1'){
        solenoid1.setSpeed(255);
        delay(25);
        solenoid1.setSpeed(0);
      } else if(c == '2'){
        solenoid2.setSpeed(255);
        delay(25);
        solenoid2.setSpeed(0);
      } else if(c == '3'){
        solenoid3.setSpeed(255);
        delay(25);
        solenoid3.setSpeed(0);
      } else if(c == '4'){
        solenoid4.setSpeed(255);
        delay(25);
        solenoid4.setSpeed(0);
      } else if(c == '5'){
        solenoid5.setSpeed(255);
        delay(25);
        solenoid5.setSpeed(0);
      } else if(c == '6'){
        solenoid6.setSpeed(255);
        delay(25);
        solenoid6.setSpeed(0);
      } else if(c == '7'){
        solenoid7.setSpeed(255);
        delay(25);
        solenoid7.setSpeed(0);
      } else if(c == '8'){
        solenoid8.setSpeed(255);
        delay(25);
        solenoid8.setSpeed(0);
      } else if(c == '9'){
        solenoid9.setSpeed(255);
        delay(25);
        solenoid9.setSpeed(0);
      }
  }
}

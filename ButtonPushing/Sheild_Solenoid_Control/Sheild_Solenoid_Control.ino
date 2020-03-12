#include <TLE94112.h>
#include <Tle94112Motor.h>
#include "pi2000.h"

// Tle94112 Object
Tle94112 controller = Tle94112();

// delay (this plus deployment time equals 25ms)
int Delay = 23; //up from 19
char push_number = 'A'; //the button we should currently push. Initalized to something random so that we don't count the first button as a double press
char last_number = 'A'; //the last number that was pushed. Initalized to something random

void setup() {
  // Enable MotorController Tle94112
  // Note: Required to be done before starting to configure the solenoid
  controller.begin();

  // config serial output for debugging
  Serial.begin(9600);

  // config limit switche
  pinMode(7, INPUT_PULLUP);
  //while(digitalRead(7) == HIGH or micros() < 10000000) {}; wait until the switch is engaged (pressed in) or until 10 seconds have passed
  
  while(digitalRead(7) == LOW) {}; //do nothing while the button is pressed in

  delay(5000); //wait 5 seconds for the hugger to get onto the wall
}


void loop() {
  //write speed values to the registers
  controller.writeReg(Tle94112::PWM1_DC_CTRL, 0x03, 0xFF, 255);
  controller.writeReg(Tle94112::PWM2_DC_CTRL, 0x03, 0xFF, 0);
  
  for(int i = 0; i < 7501; i++){
      // get pi digit from pi2000.h

      last_number=push_number; //record the last pushed number so that we don't forget it when we read in the current number we should be pushing
      push_number = pgm_read_byte_near(pi + i);

      if (push_number == last_number) delay(100); //if we are pushing the same button as last time, wait twice the delay time so that we can give the solenoid time to settle down
      
      //for testing:
      //String s = "0123456789";
      //char push_number = '0'; 
      //Serial.println(c);

      // if none of the limit switches are pressed, do nothing
      //while(digitalRead(7) != HIGH){}
      
      // a limit switch is triggered
      
      // engage the solenoid corresponding to that pi digit, leave it out for 25 ms, retract it
      if(push_number == '0'){
        controller.configHB(controller.TLE_HB10, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB10, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(push_number == '1'){
        controller.configHB(controller.TLE_HB1, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB1, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(push_number == '2'){
        controller.configHB(controller.TLE_HB2, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB2, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(push_number == '3'){
        controller.configHB(controller.TLE_HB3, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB3, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(push_number == '4'){
        controller.configHB(controller.TLE_HB4, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB4, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(push_number == '5'){
        controller.configHB(controller.TLE_HB5, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB5, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(push_number == '6'){
        controller.configHB(controller.TLE_HB6, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB6, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(push_number == '7'){
        controller.configHB(controller.TLE_HB7, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB7, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(push_number == '8'){
        controller.configHB(controller.TLE_HB8, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB8, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(push_number == '9'){
        controller.configHB(controller.TLE_HB9, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB9, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      }
      delay(Delay);
  }
}

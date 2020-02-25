#include <TLE94112.h>
#include <Tle94112Motor.h>
#include "pi2000.h"

// Tle94112 Object
Tle94112 controller = Tle94112();

// delay (this plus deployment time equals 25ms)
int Delay = 19;

void setup() {
  // Enable MotorController Tle94112
  // Note: Required to be done before starting to configure the solenoid
  controller.begin();

  // config serial output for debugging
  Serial.begin(9600);

  // config limit switches
  pinMode(7, INPUT);
  pinMode(6, INPUT);
}


void loop() {
  //write speed values to the registers
  controller.writeReg(Tle94112::PWM1_DC_CTRL, 0x03, 0xFF, 255);
  controller.writeReg(Tle94112::PWM2_DC_CTRL, 0x03, 0xFF, 0);
  
  for(int i = 0; i < 7501; i++){
      // get pi digit from pi2000.h
      char c = pgm_read_byte_near(pi + i);
      
      //for testing:
      //String s = "0123456789";
      //char c = '0'; 
      //Serial.println(c);

      // if none of the limit switches are pressed, do nothing
      while(digitalRead(7) != HIGH){}

      // a limit switch is triggered

      // engage the solenoid corresponding to that pi digit, leave it out for 25 ms, retract it
      if(c == '0'){
        controller.configHB(controller.TLE_HB10, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB10, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(c == '1'){
        controller.configHB(controller.TLE_HB1, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB1, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(c == '2'){
        controller.configHB(controller.TLE_HB2, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB2, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(c == '3'){
        controller.configHB(controller.TLE_HB3, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB3, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(c == '4'){
        controller.configHB(controller.TLE_HB4, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB4, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(c == '5'){
        controller.configHB(controller.TLE_HB5, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB5, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(c == '6'){
        controller.configHB(controller.TLE_HB6, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB6, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(c == '7'){
        controller.configHB(controller.TLE_HB7, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB7, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(c == '8'){
        controller.configHB(controller.TLE_HB8, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB8, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      } else if(c == '9'){
        controller.configHB(controller.TLE_HB9, controller.TLE_HIGH, controller.TLE_NOPWM, 0);
        delay(Delay);
        controller.configHB(controller.TLE_HB9, controller.TLE_HIGH, controller.TLE_PWM1, 0);
      }
      delay(Delay);
  }
}

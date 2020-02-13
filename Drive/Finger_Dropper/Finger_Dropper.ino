#include <Servo.h>

Servo s;
int setPoint = 0;


void setup() {
  // Servo went on pin 9 for testing
  s.attach(9);
  s.write(0);
  Serial.begin(9600);
  //configure pin 2 as an input and pin 13 as an output and hook them together to act as a limit switch
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  delay(100);
}

void loop() {
  /*for(int i = 0; i < 181; i++){ // "Sweep" function for debug
     s.write(i);
     delay(10);
     Serial.println(i);
  }*/
  if(digitalRead(2) == 1){ // if the limit switch is triggered deploy servo
    Serial.println("button pressed");
    s.write(168);
  }
  else{
    s.write(0);
  }
  delay(100);
}

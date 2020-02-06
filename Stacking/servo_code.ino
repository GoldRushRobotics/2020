#include <Encoder.h>
#define motorDir 9
#define pwm 5
#define encChA 3
#define encChB 2
#define limit 6
#define UP LOW
#define DN HIGH
#define MAXH 8250
int speeds = 255;
  bool flag = true;
  int pos = 0;
  Encoder myEnc(encChA, encChB);
void setup() {
  pinMode(limit, INPUT);
  pinMode(motorDir, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(encChA, INPUT);
  pinMode(encChB, INPUT);
  digitalWrite(encChA, HIGH);
 
  pos = myEnc.read();
  Serial.begin(9600);
  digitalWrite(motorDir, DN);
  analogWrite(pwm, 70);
  while(digitalRead(limit) == LOW){
    delay(1);
  }
  Serial.print(digitalRead(limit));
  analogWrite(pwm, 0);
  myEnc.write(0);
  
}
void loop() {
  // put your main code here, to run repeatedly:
 /* pos = myEnc.read();
  Serial.print(pos);
  Serial.print("\n");
  if(flag){
    speeds = speeds - 1;
    digitalWrite(motorDir, HIGH);
    analogWrite(pwm, speeds);
    if(speeds == 0){
      flag = false;
      delay(10);
    }
  }
  else{
    speeds = speeds + 1;
    digitalWrite(motorDir, LOW);
    analogWrite(pwm, speeds);
    if(speeds == 255){
      flag = true;
      delay(10);
    }
  }
  delay(10);
  */
  raiseFlag();
  lowerFlag();
}
void raiseFlag(){
  pos = myEnc.read();
  while(pos < MAXH){
    pos = myEnc.read();
    speeds = map(MAXH-pos, 30, MAXH, 25, 255);
    digitalWrite(motorDir, UP);
    analogWrite(pwm, speeds);
    Serial.print(pos);
    Serial.print("\n");
  }
  analogWrite(pwm, 0);
  delay(100);
}
void lowerFlag(){
  while(myEnc.read() > 30){
    speeds = map(myEnc.read(), 30, MAXH, 25, 255);
    digitalWrite(motorDir, DN);
    analogWrite(pwm, speeds);
    Serial.print(myEnc.read());
    Serial.print("\n");
  }
  analogWrite(pwm, 0);
  delay(100);
}

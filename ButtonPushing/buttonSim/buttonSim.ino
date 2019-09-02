int piArray[63] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 5, 1, 0, 5, 8, 2, 0, 9, 7, 4, 9, 4, 4, 5, 9};
/*
 * Number Layout (pi digit, led pin, input pin):
 * 0, 2, 22
 * 1, 3, 23
 * 2, 4, 24
 * 3, 5, 25
 * 4, 6, 26
 * 5, 7, 27
 * 6, 8, 28
 * 7, 9, 29
 * 8, 10, 30
 * 9, 11, 31
 */
void setup() { 
  // put your setup code here, to run once:
  for(int i = 2; i <= 11; i++){
     pinMode(i, OUTPUT);//sets the pin mode for the output pins
  }
  for(int i = 22; i <= 31; i++){
    pinMode(i, INPUT);
  }
} 

void loop() {
  int piLength = 63;
      for(int i = 0; i < piLength; i++ ){ //Loop starts at one and goes for the length of piArray
        int buttonNum = piArray[i]; //reads integer at position i in piArray and assigns that integer to int solNum
        int ledPin = buttonNum + 2; //sets solNum to the correct output pin
        digitalWrite(ledPin, HIGH); //Sends on signal to the given pin
          for(int j = 0; j < 25; j+= 0){
            if(digitalRead(buttonNum + 22) == HIGH){
              j += 1;
              delay(1);
            }
            else if(digitalRead(buttonNum + 22) == LOW && j > 0){
              flashLed();
              break;
            }
          }
        digitalWrite(ledPin, LOW); //turns off signal to the given pin
        for(int m = 0; m < 25; m++){
          delay(1);
          for(int f = 0; f < 10; f++){
            if(digitalRead(f + 22) == HIGH && f != buttonNum){
              flashLed();
              break;
            }
          }
        }
      if(i == 62){
        delay(200);
        for(int j = 2; j <= 11; j++){
          digitalWrite(j, HIGH);
        }
        delay(5000);
        for(int j = 2; j <= 11; j++){
          digitalWrite(j, LOW);
        }
        i = 0;
        break;
      }
    }
  }

void flashLed(){
  delay(500);
  for(int k = 2; k <= 11; k++){
     digitalWrite(k, HIGH);
   }
   delay(500);
   for(int k = 2; k <= 11; k++){
      digitalWrite(k, LOW);
   }
   delay(500);
   for(int k = 2; k <= 11; k++){
     digitalWrite(k, HIGH);
   }
   delay(500);
   for(int k = 2; k <= 11; k++){
      digitalWrite(k, LOW);
   }
}

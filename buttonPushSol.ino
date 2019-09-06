int piArray[63] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 5, 1, 0, 5, 8, 2, 0, 9, 7, 4, 9, 4, 4, 5, 9};

void setup() { 
  // put your setup code here, to run once:
  for(int i = 2; i <= 11; i++){
     pinMode(i, OUTPUT);//sets the pin mode for the output pins
  }
  pinMode(13, INPUT);
} 

void loop() {
  int piLength = 63;
      for(int i = 0; i < piLength; i++ ){ //Loop starts at one and goes for the length of piArray
        if(digitalRead(13) == 1){
        i = 0;
        break;
      }
        int solNum = piArray[i]; //reads integer at position i in piArray and assigns that integer to int solNum
        int solenoidPin = solNum + 2; //sets solNum to the correct output pin
        digitalWrite(solenoidPin, HIGH); //Sends on signal to the given pin
        delay(100); //waits 100 ms for duration of button press
        digitalWrite(solenoidPin, LOW); //turns off signal to the given pin
        Serial.print('solenoidPin'); //prints the number of the pin that it sent the signal to
        delay(50); //waits 50 ms for break between button presses
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

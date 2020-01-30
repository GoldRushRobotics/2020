void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(A4);
  int val2 = digitalRead(A5);
  int val3 = digitalRead(4);
  Serial.print(val);
  Serial.print(" ");
  Serial.print(val2);
  Serial.print(" ");
  Serial.println(val3);
}

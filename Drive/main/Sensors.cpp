#include "Sensors.h"
#include "Arduino.h"

void LightSensor::attach(int pin) {
  _pin = pin;
  pinMode(pin, INPUT);
}

int LightSensor::read() {
  if (_pin >= 0) {
    return digitalRead(_pin);
  }
  Serial.println("ERROR: light sensor attempted to be read before being attached!");
  return -1;
}


volatile double Encoder::counter = 0;

void Encoder::attach() { 
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
}

void Encoder::ai0() {
  if (digitalRead(3) == LOW) {
    Encoder::counter++;
  } else {
    Encoder::counter--;
  }
}

void Encoder::ai1() {
  if (digitalRead(2) == LOW) {
    Encoder::counter--;
  } else {
    Encoder::counter++;
  }
}

void Encoder::setDirection(double dir) {
  if (dir > 0) {
    direction = 1;
  } else if (dir < 0)  {
    direction = -1;
  } else {
    direction = 0;
  }
}

void Encoder::reset() {
  counter = 0;
}

double Encoder::getTicks() {
  return Encoder::counter * direction;
}

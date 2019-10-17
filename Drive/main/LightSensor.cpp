#include "LightSensor.h"
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
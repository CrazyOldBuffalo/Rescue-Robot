#include <Arduino.h>
#include <Servo.h>

Servo rightMotorDir, rightMotorSpd, leftMotorDir, leftMotorSpd;

void setup() {
  Serial.begin(9600);
  rightMotorDir.attach(15);
  rightMotorSpd.attach(9);
  leftMotorDir.attach(16);
  leftMotorSpd.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
}
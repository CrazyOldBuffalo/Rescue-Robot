#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <Servo.h>
#include "drive.h"

drive move;


void setup() {

}

// the loop function runs over and over again forever
void loop() {
    move.forward();
    delay(1000);
    move.stop();
}
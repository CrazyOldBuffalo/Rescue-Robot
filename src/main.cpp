#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <Servo.h>
#include <Zumo32U4IMU.h>
#include "manual.h"
#include "turn.h"
#include "FrontSensing.h"

Turn move;
Zumo32U4ButtonA buttonA;
manual man;
FrontSensing proxSensors = FrontSensing();

char packet;
bool buttonPressed = false;
bool breaker = false;


void setup()
{
    Serial1.begin(9600);
    Serial1.println("Press Button A for Manual, B for Automatic");
    do
    {
        if (buttonA.isPressed())
        {
            buttonPressed = true;
            man.manualMode(move, proxSensors);
        }
    }
    while (!buttonPressed);
}

// the loop function runs over and over again forever
void loop()
{

}
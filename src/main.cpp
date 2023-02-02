#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <Servo.h>
#include "manual.h"
#include "drive.h"

drive move;
Zumo32U4ButtonA buttonA;
manual man;
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
            Serial1.println("Entering Manual Mode");
            man.manualMode(move);
        }
    }
    while (!buttonPressed);
}

// the loop function runs over and over again forever
void loop()
{

}
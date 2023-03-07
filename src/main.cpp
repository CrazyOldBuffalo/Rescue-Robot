// Includes various headers that are required
// Also includes various libraries needed to get the robot to work.

#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include <Servo.h>
#include <Zumo32U4IMU.h>
#include "manual.h"
#include "turn.h"
#include "FrontSensing.h"
//#include "auto.h"

// Creates objects for the required classes
// Turn for turning, ButtonA for the button pressing
// Manual for driving in manual mode
// proxSensors for the proximity sensors
Turn move;
Zumo32U4ButtonA buttonA;
manual man;
FrontSensing proxSensors = FrontSensing();

// Varaiable for checking if the button was pressed
bool buttonPressed = false;


// Performs setup for the zumo
// Sets serial to begin at baudrate 9600
// Prints that it's waiting for a button press
// when it's pressed stop the loop and run the manual mode using the turn and proximitySensors to pass through
void setup()
{
    Serial1.begin(9600);
    Serial1.println("Press Button A to begin setup");
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
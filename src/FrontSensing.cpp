// FrontSensor class for the proximity sensors
// Performs all functions for reading, getting and calculating with the sensors for detecting obstacles or people
// Includes header file


#include "FrontSensing.h"


// Constructor for creating the sensors and sets the values to 0 after initialising
FrontSensing::FrontSensing()
{
    proxSensors.initThreeSensors();
    leftProxSensorValue = 0;
    rightProxSensorValue = 0;
    middleLeftProxSensorValue = 0;
    middleRightProxSensorValue = 0;
};

// Getter function for the left proximity sensor
// Reads and returns the value
int FrontSensing::getLeftBrightness()
{
    proxSensors.read();
    leftProxSensorValue = proxSensors.countsLeftWithLeftLeds();
    return leftProxSensorValue;
};

// Getter function for the right proximity sensor
// Reads and returns the value
int FrontSensing::getRightBrightness()
{
    proxSensors.read();
    rightProxSensorValue = proxSensors.countsRightWithRightLeds();
    return rightProxSensorValue;
}

// Getter functions for the middle proximity sensors
// Reads and returns the values
int FrontSensing::getMiddleLeftBrightness()
{
    proxSensors.read();
    middleLeftProxSensorValue = proxSensors.countsFrontWithLeftLeds();
    return middleLeftProxSensorValue;
}

int FrontSensing::getMiddleRightBrightness()
{
    proxSensors.read();
    middleRightProxSensorValue = proxSensors.countsFrontWithRightLeds();
    return middleRightProxSensorValue;
}


// Bool returns for the sensors
// Coded in reverse (for some reason? not sure why I did that)
// Call the getter functions from above, if they are less that 6 they're true
// if 6 (close to object) they return false so other functions can trigger
bool FrontSensing::leftSensorCheck() {
    if (getLeftBrightness() < 6) {
        return true;
    }
    return false;
}

bool FrontSensing::frontSensorCheck() {
    if (getMiddleLeftBrightness() < 6 && getMiddleRightBrightness() < 6) {
        return true;
    }
    return false;
}

bool FrontSensing::rightSensorCheck() {
    if(getRightBrightness() < 6) {
        return true;
    }
    return false;
}


// String returns for sensor checks above
// For outputting String to the serial if they detect something >= 6
// So the operator knows whats going on.
String FrontSensing::obstacleFront() {
    if(!frontSensorCheck()) {
        return "Obstacle or Person in front of Robot - CAUTION";
    }
    return "Clear";
}

String FrontSensing::obstacleLeft() {
    if (!leftSensorCheck()) {
        return "Obstacle or Person Left of Robot - CAUTION";
    }
    return "Clear";
}

String FrontSensing::obstacleRight() {
    if(!rightSensorCheck()) {
        return "Obstacle or Person Right of Robot - CAUTION";
    }
    return "Clear";
}
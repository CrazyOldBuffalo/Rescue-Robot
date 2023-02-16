#include "FrontSensing.h"

FrontSensing::FrontSensing()
{
    proxSensors.initThreeSensors();
    leftProxSensorValue = 0;
    rightProxSensorValue = 0;
    middleLeftProxSensorValue = 0;
    middleRightProxSensorValue = 0;
};

int FrontSensing::getLeftBrightness()
{
    proxSensors.read();
    leftProxSensorValue = proxSensors.countsLeftWithLeftLeds();
    return leftProxSensorValue;
};

int FrontSensing::getRightBrightness()
{
    proxSensors.read();
    rightProxSensorValue = proxSensors.countsRightWithRightLeds();
    return rightProxSensorValue;
}

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

String FrontSensing::obstacleFront() {
    if(frontSensorCheck()) {
        return "No Obstacles In Front of Robot";
    }
    return "Obstacle in front of Robot - CAUTION";
}

String FrontSensing::obstacleLeft() {
    if (leftSensorCheck()) {
        return "No Obstacles near Left of Robot";
    }
    return "Obstacle Left of Robot - CAUTION";
}

String FrontSensing::obstacleRight() {
    if(rightSensorCheck()) {
        return "No Obstacles near Right of Robot";
    }
    return "Obstacle Right of Robot - CAUTION";
}
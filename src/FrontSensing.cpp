#include "FrontSensing.h"

FrontSensing::FrontSensing()
{
    proxSensors.initThreeSensors();
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

bool FrontSensing::frontSensorCheck() {
    if (getMiddleLeftBrightness() < 6 && getMiddleRightBrightness() < 6) {
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
#pragma once
#include <Zumo32U4ProximitySensors.h>
#include "drive.h"

class FrontSensing
{
private:
    Zumo32U4ProximitySensors proxSensors;
    int leftProxSensorValue, rightProxSensorValue, middleLeftProxSensorValue, middleRightProxSensorValue;
    void setupScan();

public:
    FrontSensing();
    int getLeftBrightness();
    int getRightBrightness();
    bool frontSensorCheck();
    bool leftSensorCheck();
    bool rightSensorCheck();
    int getMiddleLeftBrightness();
    int getMiddleRightBrightness();
    void proximityAlert();
    String obstacleFront();
    String obstacleLeft();
    String obstacleRight();
};
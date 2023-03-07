#pragma once
#include <Zumo32U4ProximitySensors.h>
#include "turn.h"

// Headerfile for the proximity sensors
// Creates a proximity sensor object and values for each sensor
// Creates a bunch of functions covered in the cpp file
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
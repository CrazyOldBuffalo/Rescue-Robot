#pragma once
#include <Zumo32U4ProximitySensors.h>
#include "drive.h"

class FrontSensing
{
private:
    Zumo32U4ProximitySensors proxSensors;
    int leftProxSensorValue, rightProxSensorValue, middleLeftProxSensorValue, middleRightProxSensorValue;
    void setupScan(Zumo32U4ProximitySensors proxSensors);

public:
    FrontSensing();
    int getValues(Zumo32U4ProximitySensors proxSensors);
    int getLeft(Zumo32U4ProximitySensors proxSensors);
    int getRight(Zumo32U4ProximitySensors proxSensors);
    int getMiddleLeft(Zumo32U4ProximitySensors proxSensors);
    int getMiddleRight(Zumo32U4ProximitySensors proxSensors);
    void proximityAlert();
};
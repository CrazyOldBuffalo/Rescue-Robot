#include "FrontSensing.h"

FrontSensing::FrontSensing()
{
    proxSensors.initThreeSensors();
};

int FrontSensing::getLeft(Zumo32U4ProximitySensors proxSensors)
{
    this->setupScan(proxSensors);
    return proxSensors.countsLeftWithLeftLeds();
};

int FrontSensing::getRight(Zumo32U4ProximitySensors proxSensors)
{
    this->setupScan(proxSensors);
    return proxSensors.countsRightWithRightLeds();
}

int FrontSensing::getMiddleLeft(Zumo32U4ProximitySensors proxSensors)
{
    this->setupScan(proxSensors);
    return proxSensors.countsFrontWithLeftLeds();
}

int FrontSensing::getMiddleRight(Zumo32U4ProximitySensors proxSensors)
{
    this->setupScan(proxSensors);
    return proxSensors.countsFrontWithRightLeds();
}

void FrontSensing::setupScan(Zumo32U4ProximitySensors proxSensors)
{
    proxSensors.lineSensorEmittersOff();
    proxSensors.pullupsOn();
}
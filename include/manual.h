#pragma once
#include "FrontSensing.h"


class Manual {
private:
    bool breaker = false;
    char packet;
public:
    void manualMode(Turn drive, FrontSensing proxSensors);
    void sensorScan(FrontSensing proxSensors);
};
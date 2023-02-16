#pragma once
#include "FrontSensing.h"


class manual {
private:
    bool breaker = false;
    char packet;
public:
    void manualMode(Turn drive, FrontSensing proxSensors);
    void sensorScan(FrontSensing proxSensors);
};
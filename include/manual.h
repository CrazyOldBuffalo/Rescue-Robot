#pragma once
#include "FrontSensing.h"
#include "lineSensor.h"


class manual {
private:
    bool breaker = false;
    char packet;
    LineSensor lineSensor;
public:
    void manualMode(Turn drive, FrontSensing proxSensors);
    void sensorScan(FrontSensing proxSensors);
};
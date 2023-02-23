#pragma once
#include "FrontSensing.h"
#include "lineSensor.h"


class manual {
private:
    bool breaker = false;
    char packet;
    LineSensor lineSensor;
    bool blocker = false;
public:
    void manualMode(Turn drive, FrontSensing proxSensors);
    void sensorScan(Turn drive, FrontSensing proxSensors);
    void linescan();
};
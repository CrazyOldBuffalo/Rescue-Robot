#pragma once
#include "drive.h"
#include "FrontSensing.h"


class Manual {
private:
    bool breaker = false;
    char packet;
public:
    void manualMode(drive drive, FrontSensing proxSensors);
};
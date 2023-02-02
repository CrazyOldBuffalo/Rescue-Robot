#pragma once
#include "drive.h"


class manual {
private:
    bool breaker = false;
    char packet;
public:
    void manualMode(drive drive);
};
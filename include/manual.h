#pragma once
#include "FrontSensing.h"
#include "lineSensor.h"


class manual {
private:
    bool breaker = false;
    char packet;
    LineSensor lineSensor;
    bool blocker = false;
    bool autoMode = false;
    bool linefoundLeft, linefoundRight, linefoundFront;
public:
    void manualMode(Turn drive, FrontSensing proxSensors);
    void sensorScan(Turn drive, FrontSensing proxSensors);
    void linescan();
    void automaticMode(Turn drive, FrontSensing proxSensors);
    void detectedLeftLine(Turn drive, FrontSensing proxSensors);
    void detectedRightLine(Turn drive, FrontSensing proxSensors);
    void detectedFrontLine(Turn drive, FrontSensing proxSensors);
    void search(Turn drive, FrontSensing proxSensors);
    void movingForward(Turn drive, FrontSensing proxSensors);
    void RoomLeft(Turn drive, FrontSensing proxSensors);
    void RoomRight(Turn drive, FrontSensing proxSensors);
    void TurnLeft(Turn drive, FrontSensing proxSensors);
    void TurnRight(Turn drive, FrontSensing proxSensors);
    void UhOh(Turn drive, FrontSensing proxSensors);
};
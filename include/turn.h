#pragma once
#include <Wire.h>
#include <Zumo32U4.h>
#include "gyroSensor.h"

class Turn
{
private:
    Zumo32U4Motors motors;
    int turnspeed = 150;
    int motorspeed = 150;
    int angle = 0;
    GyroSensor gyro = GyroSensor();
public:
    void turnleft();
    void turnleft(int turnval);
    void turnright();
    void turnright(int turnval);
    void stop();
    void forward();
    void backward();
    void calibrate();
    void autoForward();
    void autoBackward();
};
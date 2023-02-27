#include "lineSensor.h"

void LineSensor::lineSensorSetup()
{
    lineSensor.initFiveSensors();
    lineSensorCalibration();
}

void LineSensor::lineSensorCalibration()
{
    Serial1.println("Calibrating Line Sensors");
    lineSensor.calibrate();
    delay(1000);
    Serial1.println("Calibration Complete");
}

void LineSensor::lineSensorRead()
{
    lineSensor.readCalibrated(lineSensorValues);
    left1 = lineSensorValues[0];
    left2 = lineSensorValues[1];
    right1 = lineSensorValues[3];
    right2 = lineSensorValues[4];
    
}

bool LineSensor::leftLineSensing()
{
    lineSensorRead();
    if (left1 > 5 && left2 > 5)
    {
        return true;
    }
    return false;
}

bool LineSensor::rightLineSensing()
{
    lineSensorRead();
    if(right1 > 5 && right2 > 5)
    {
        return true;
    }
    return false;
}

unsigned int LineSensor::leftValue1()
{
    return left1;
}
unsigned int LineSensor::leftValue2()
{
    return left2;
}

unsigned int LineSensor::rightValue1()
{
    return right1;
}

unsigned int LineSensor::rightValue2()
{
    return right2;
}
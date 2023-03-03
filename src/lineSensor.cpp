// LineSensor class for loading, calibrating and reading the linesensor
// includes the header file

#include "lineSensor.h"


// initialises the linesensor
// calibrates it for use
void LineSensor::lineSensorSetup()
{
    lineSensor.initFiveSensors();
    lineSensorCalibration();
}

// Outputs to the user that the linesensors are being calibrated
// waits for the sensor to be still
// outputs it's complete to the user
void LineSensor::lineSensorCalibration()
{
    Serial1.println("Calibrating Line Sensors");
    lineSensor.calibrate();
    delay(1000);
    Serial1.println("Calibration Complete");
}

// reads the values from the line sensors and sets it to the lineSensorValues attribute
void LineSensor::lineSensorRead()
{
    lineSensor.readCalibrated(lineSensorValues);
}

// reads the linesensor on the left and checks if they are greater than 1
// returns true if so
bool LineSensor::leftLineSensing()
{
    lineSensor.readCalibrated(lineSensorValues);
    if (lineSensorValues[0] > 1 || lineSensorValues[1] > 1)
    {
        return true;
    }
    return false;
}

// reads the linesensor on the right and checks if they are greater than 1
// returns true if so
bool LineSensor::rightLineSensing()
{
    lineSensorRead();
    if(lineSensorValues[3] > 1 || lineSensorValues[4] > 1)
    {
        return true;
    }
    return false;
}

// reads the linesensor on the front and checks if they are greater than 1
// returns true if so
bool LineSensor::frontLineSensing()
{
    lineSensorRead();
    if (lineSensorValues[2] > 0 || lineSensorValues[3] > 0)
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
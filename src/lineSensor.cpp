#include "lineSensor.h"

void LineSensor::lineSensorSetup() {
    lineSensor.initFiveSensors();
    lineSensorCalibration();
}

void LineSensor::lineSensorCalibration() {
    Serial1.println("Calibrating Line Sensors");
    lineSensor.calibrate();
    delay(1000);
    Serial1.println("Calibration Complete");
}

void LineSensor::lineSensorRead() {
    lineSensor.readCalibrated(lineSensorValues);
    left1 = lineSensorValues[0];
    left2 = lineSensorValues[1];
    right1 = lineSensorValues[4];
    right2 = lineSensorValues[5];
    //pos = lineSensor.readLine(lineSensorValues);
}


unsigned int LineSensor::leftValue1() {
    return left1;
}
unsigned int LineSensor::leftValue2() {
    return left2;
}

unsigned int LineSensor::rightValue1() {
    return right1;
}

unsigned int LineSensor::rightValue2() {
    return right2;
}
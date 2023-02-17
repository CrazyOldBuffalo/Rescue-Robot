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

void LineSensor::lineSensorTest() {
    int value = lineSensor.readLine(lineSensorValues);
    Serial1.println("line is:");
    Serial1.println(value);
}
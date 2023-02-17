#include "lineSensor.h"

void LineSensor::lineSensorSetup() {
    lineSensor.initFiveSensors();
}

void LineSensor::lineSensorCalibration() {
    Serial1.println("Calibrating Line Sensors");
    lineSensor.calibrate();
    delay(1000);
    Serial1.println("Calibration Complete");
}
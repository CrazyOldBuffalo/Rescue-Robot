// Class file + header for the gyrosensor
// For using with the turn class that allows the robot to turn

#include "gyroSensor.h"

// Resets the turn sensor and TurnAngle variable to 0
void GyroSensor::turnSensorReset()
{
    gyroLastUpdate = micros();
    turnAngle = 0;
}

// Initialises the Gyro and configures for turnSensing
// Waits for .5 seconds
// sets total to 0 and waits for the gyro to read new data before setting total to the z axis on the gyro
// Calls reset to put it to 0
void GyroSensor::turnSensorSetup()
{
    Wire.begin();
    imu.init();
    imu.enableDefault();
    imu.configureForTurnSensing();

    delay(500);

    int32_t total = 0;
    for (uint16_t i = 0; i < 1024; i++)
    {
        // Wait for new data to be available, then read it.
        while (!imu.gyroDataReady())
        {
        }
        imu.readGyro();

        // Add the Z axis reading to the total.
        total += imu.g.z;
    }
    gyroOffset = total / 1024;
    turnSensorReset();
}

// Updates the turn sensor, is used to update the gyro in turn.cpp for turning left/right
// reads the gyro, sets the last update time and then adds a calculation to the turn angle.
void GyroSensor::turnSensorUpdate() {
    imu.readGyro();
    turnRate = imu.g.z - gyroOffset;
    uint16_t m = micros();
    uint16_t dt = m - gyroLastUpdate;
    gyroLastUpdate = m;

    int32_t d = (int32_t)turnRate * dt;

    turnAngle += (int64_t)d * 14680064 / 17578125;
}

int32_t GyroSensor::getTurnAngle45() {
    return turnAngle45;
}
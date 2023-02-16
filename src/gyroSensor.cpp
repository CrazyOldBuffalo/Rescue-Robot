#include "gyroSensor.h"

void GyroSensor::turnSensorReset()
{
    gyroLastUpdate = micros();
    turnAngle = 0;
}

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
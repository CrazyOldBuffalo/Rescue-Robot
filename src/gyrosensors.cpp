#include "gyrosensors.h"

gyrosensors::gyrosensors() {
    this->turnAngle = 0;
    this->turnRate;
    this->gyroOffset;
    this->gyroLastUpdate = 0;
};


void gyrosensors::turnSensorCalibration() {
    Wire.begin();
    imu.init();
    imu.enableDefault();
    imu.configureForTurnSensing();
    delay(1000);
    int32_t total = 0;
    for (uint16_t i = 0; i < 1024; i++) {
        while(!imu.gyroDataReady()) {}
        imu.readGyro();

        total += imu.g.z;
    }

    gyroOffset = total / 1024;
    turnSensorReset();
};

void gyrosensors::turnSensorReset() {
    gyroLastUpdate = micros();
    turnAngle = 0;
};

void gyrosensors::turnSensorUpdate() {
    imu.readGyro();
    turnRate = imu.g.z - gyroOffset;
    uint16_t m = micros();
    uint16_t dt = m - gyroLastUpdate;
    gyroLastUpdate = m;
    int32_t d = (int32_t)turnRate * dt;

    turnAngle += (int64_t)d * 14680064 / 17578125;
}


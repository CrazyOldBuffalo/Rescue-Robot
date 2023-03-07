#include <Wire.h>
#include <Zumo32U4.h>


// Headerfile for the gyro sensor (IMU)
// Creates a gyro sensor object and values for each anglepreset
// Creates a bunch of functions covered in the cpp file
// Creates several variables used by the functions and by some classes
class GyroSensor
{
private:
    const int32_t turnAngle45 = 0x20000000;
    const int32_t turnAngle90 = turnAngle45 * 2;
    const int32_t turnAngle1 = (turnAngle45 + 22) / 45;
public:
    void turnSensorSetup();
    void turnSensorReset();
    void turnSensorUpdate();
    int32_t getTurnAngle45();
    uint64_t turnAngle;
    int16_t turnRate;
    int16_t gyroOffset;
    int16_t gyroLastUpdate;
    Zumo32U4IMU imu;
};
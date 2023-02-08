
#pragma once
#include <Zumo32U4.h>
#include <Zumo32U4IMU.h>
#include "Wire.h"


class gyrosensors {
  private:
  const int32_t turnAngle45 = 0x20000000;
  const int32_t turnAngle90 = turnAngle45 * 2;
  const int32_t turnAngle180 = turnAngle90 * 2;
  const int32_t turnAngle360 = turnAngle180 * 2;
  Zumo32U4IMU imu;

  public:
  gyrosensors();
  void turnSensorCalibration();
  void turnSensorReset();
  void turnSensorUpdate();
  void resetTurnAngle();
  int32_t turnAngle;
  int16_t turnRate;
  int16_t gyroOffset;
  uint16_t gyroLastUpdate;
};
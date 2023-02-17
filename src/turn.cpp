#include "turn.h"


void Turn::turnleft(int degree) {
    gyro.turnSensorReset();
    motors.setSpeeds(-turnspeed, turnspeed);
    int angle = 0;
    while(angle < degree) {
      delay(1);
      gyro.turnSensorUpdate();
      angle = (((int32_t)gyro.turnAngle >> 16)* 360) >> 16;
      Serial.println(angle);
    }
    stop();
}

void Turn::turnright(int degree) {
    gyro.turnSensorReset();
    motors.setSpeeds(turnspeed, -turnspeed);
    int angle = 0;
    while (angle > -degree) {
        delay(1);
        gyro.turnSensorUpdate();
        angle = (((int32_t) gyro.turnAngle >> 16)* 360) >> 16;
        Serial.println(angle);
    }
    stop();
}

void Turn::forward() {
    motors.setSpeeds(motorspeed, motorspeed);
    delay(1000);
    stop();
}

void Turn::stop() {
    motors.setSpeeds(0,0);
    delay(1000);
}

void Turn::calibrate() {
    Serial.println("Calibrating");
    gyro.turnSensorSetup();
    delay(2000);
    gyro.turnSensorReset();
    Serial.println("Calibrating Complete");
}

void Turn::backward() {
  motors.setSpeeds(-motorspeed,-motorspeed) ;
  delay(1000);
  stop();
}
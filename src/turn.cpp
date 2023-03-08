// A Class for controlling the Zumo Servos and motors to get it to perform different actions like turning, going forward or reversing

// Headerfile
#include "turn.h"

// Get the Zumo to turn left by a set amount of degrees (from the function call)
// Continues to turn the robot until the robot has turned by the angle passed into it
// Stops when done
void Turn::turnleft(int degree) {
    gyro.turnSensorReset();
    motors.setSpeeds(-turnspeed, turnspeed);
    int angle = 0;
    while(angle < degree) {
      delay(1);
      gyro.turnSensorUpdate();
      angle = (((int32_t)gyro.turnAngle >> 16)* 360) >> 16;
    }
    stop();
}

//Same as turnleft but for right
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


// gets the robot to move forward for 0.5 seconds and then stop
void Turn::forward() {
    motors.setSpeeds(motorspeed, motorspeed);
    delay(250);
    stop();
}

// stops the robot
void Turn::stop() {
    motors.setSpeeds(0,0);
    delay(50);
}

// forward speeds for when using the auto mode to give it more consistency and is also slower than normal forward
void Turn::autoForward() {
    motors.setSpeeds(100,100);
}

// Calibrates the gyro sensor and resets it (called on startup when Button A is pressed)
void Turn::calibrate() {
    Serial.println("Calibrating");
    gyro.turnSensorSetup();
    delay(2000);
    gyro.turnSensorReset();
    Serial.println("Calibrating Complete");
}

// Reverses the robot
void Turn::backward() {
  motors.setSpeeds(-motorspeed,-motorspeed);
  delay(500);
  stop();
}

// Reverses the robot in auto mode (also more consistency)
void Turn::autoBackward() {
    motors.setSpeeds(-100, -100);
}
  #include "drive.h"

  void drive::turnleft() {
    motors.setSpeeds(-200, 200);
  };

  void drive::turnleft(int16_t leftval, int16_t rightval) {
    motors.setSpeeds(leftval, rightval);
  }
  
  void drive::turnright() {
    motors.setSpeeds(200, -200);
  };

  void drive::turnright(int16_t leftval, int16_t rightval) {
    motors.setSpeeds(leftval, rightval);
  }

  void drive::stop() {
    motors.setSpeeds(0, 0);
  };

  void drive::forward() {
    motors.setSpeeds(200, 200);
  };

  void drive::backward() {
    motors.setSpeeds(-200, -200);
  };
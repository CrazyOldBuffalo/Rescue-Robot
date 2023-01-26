  #include "drive.h";

  void drive::turnleft() {
    motors.setSpeeds(-200, 200);
  };

  void drive::turnright() {
    motors.setSpeeds(200, -200);
  };

  void drive::stop() {
    motors.setSpeeds(0, 0);
  };

  void drive::forward() {
    motors.setSpeeds(200, 200);
  };

  void drive::backward() {
    motors.setSpeeds(-200, -200);
  };
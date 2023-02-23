#include <Zumo32U4.h>

class LineSensor
{
private:
    Zumo32U4LineSensors lineSensor;
    #define NUM_SENSORS 5
    unsigned int lineSensorValues[NUM_SENSORS];
    unsigned int left1, left2, right1, right2 = 0;
    int16_t pos = 0;
public:
    void lineSensorSetup();
    void lineSensorCalibration();
    void lineSensorRead();
    unsigned int leftValue1();
    unsigned int leftValue2();
    unsigned int rightValue1();
    unsigned int rightValue2();
    bool leftLineSensing();
    bool rightLineSensing();  
};

#include <Zumo32U4.h>

class LineSensor
{
private:
    Zumo32U4LineSensors lineSensor;
    #define NUM_SENSORS 5
    unsigned int lineSensorValues[NUM_SENSORS];
public:
    void lineSensorSetup();
    void lineSensorCalibration();
    void lineSensorTest();
};

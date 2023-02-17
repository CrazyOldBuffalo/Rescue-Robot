#include <Zumo32U4.h>

class LineSensor
{
private:
    Zumo32U4LineSensors lineSensor;
public:
    void lineSensorSetup();
    void lineSensorCalibration();
};

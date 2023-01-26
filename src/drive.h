#include <Wire.h>
#include <Zumo32U4.h>

class drive
{
private:
    Zumo32U4Motors motors;
public:
    drive::drive();
    drive::~drive();
    void turnleft();
    void turnright();
    void stop();
    void forward();
    void backward();
};



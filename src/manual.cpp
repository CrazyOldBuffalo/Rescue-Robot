#include "manual.h"

void manual::manualMode(Turn move, FrontSensing proxSensors) {
    move.calibrate();
    delay(1000);
    while (!breaker)
    {
        if (Serial1.available() > 0)
        {
            packet = (char)Serial1.read();
            switch (packet)
            {
            case 'w':
                move.forward();
                delay(500);
                move.stop();
                sensorScan(proxSensors);
                break;
            case 'a':
                move.turnleft(15);
                delay(500);
                move.stop();
                sensorScan(proxSensors);
                break;
            case 'd':
                move.turnright(15);
                delay(500);
                move.stop();
                sensorScan(proxSensors);
                break;
            case 's':
                move.backward();
                delay(500);
                move.stop();
                sensorScan(proxSensors);
                break;
            case 'x':
                move.stop();
                delay(1000);
                Serial1.println("Exiting");
                breaker = true;
                break;
            default:
                break;
            }
        }
    }
}

void manual::sensorScan(FrontSensing proxSensors) {
    Serial1.println("Checking Sensors for Obstacles");
    Serial1.println("Front Sensors: ");
    Serial1.println(proxSensors.obstacleFront());
    Serial1.println("Left Sensors: ");
    Serial1.println(proxSensors.leftSensorCheck());
    Serial1.println("Right Sensors: ");
    Serial1.println(proxSensors.rightSensorCheck());
}
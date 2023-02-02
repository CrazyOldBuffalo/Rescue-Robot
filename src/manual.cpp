#include "manual.h"

void manual::manualMode(drive move, FrontSensing proxSensors) {
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
                move.turnleft();
                delay(500);
                move.stop();
                sensorScan(proxSensors);
                break;
            case 'd':
                move.turnright();
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
    Serial1.println("Left Sensor: ");
    Serial1.println(proxSensors.obstacleLeft());
    Serial1.println("Right Sensor: ");
    Serial1.println(proxSensors.obstacleRight());
}
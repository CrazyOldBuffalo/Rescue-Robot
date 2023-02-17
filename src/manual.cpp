#include "manual.h"

void manual::manualMode(Turn move, FrontSensing proxSensors) {
    move.calibrate();
    lineSensor.lineSensorSetup();
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
                delay(50);
                move.stop();
                sensorScan(proxSensors);
                lineSensor.lineSensorTest();
                break;
            case 'a':
                move.turnleft(15);
                delay(50);
                move.stop();
                sensorScan(proxSensors);
                lineSensor.lineSensorTest();
                break;
            case 'd':
                move.turnright(15);
                delay(50);
                move.stop();
                sensorScan(proxSensors);
                lineSensor.lineSensorTest();
                break;
            case 's':
                move.backward();
                delay(50);
                move.stop();
                sensorScan(proxSensors);
                lineSensor.lineSensorTest();
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
    if(!proxSensors.frontSensorCheck()) {
        Serial1.println("Front Sensor:");
        Serial1.println(proxSensors.obstacleFront());
    }
    if(!proxSensors.leftSensorCheck()) {
        Serial1.println("Left Sensor:");
        Serial1.println(proxSensors.obstacleLeft());
    }
    if(!proxSensors.rightSensorCheck()) {
        Serial1.println("Right Sensor:");
        Serial1.println(proxSensors.obstacleRight());
    }
}
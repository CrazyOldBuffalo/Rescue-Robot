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
            if (blocker) {
                Serial1.println("Obstacle in Front");
                break;
            }
            else {
                move.forward();
                delay(50);
                move.stop();
                sensorScan(move, proxSensors);
                linescan();
                break;
            }
            case 'a':
                move.turnleft(15);
                delay(50);
                sensorScan(move, proxSensors);
                linescan();
                break;
            case 'd':
                move.turnright(15);
                delay(50);
                sensorScan(move, proxSensors);
                linescan();
                break;
            case 's':
                move.backward();
                delay(50);
                move.stop();
                sensorScan(move, proxSensors);
                linescan();
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

void manual::sensorScan(Turn drive, FrontSensing proxSensors) {
    if(!proxSensors.frontSensorCheck()) {
        Serial1.println("Front Sensor:");
        Serial1.println(proxSensors.obstacleFront());
        drive.stop();
        blocker = true;
    }
    if(proxSensors.frontSensorCheck()) {
        blocker = false;
    }
    if(!proxSensors.leftSensorCheck()) {
        Serial1.println("Left Sensor:");
        Serial1.println(proxSensors.obstacleLeft());
        drive.stop();
    }
    if(!proxSensors.rightSensorCheck()) {
        Serial1.println("Right Sensor:");
        Serial1.println(proxSensors.obstacleRight());
        drive.stop();
    }
}

void manual::linescan() {
    lineSensor.lineSensorRead();
    Serial1.println("Left Values:");
    Serial1.println(lineSensor.leftValue1(), lineSensor.leftValue2());
    Serial1.println("Right Values");
    Serial1.println(lineSensor.rightValue1(), lineSensor.rightValue2());
}
#include "manual.h"

void manual::manualMode(Turn move, FrontSensing proxSensors)
{
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
                if (blocker)
                {
                    Serial1.println("Obstacle in Front");
                    break;
                }
                else
                {
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
            case 'g':
                Serial1.println("Switching to Auto Mode");
                automaticMode(move, proxSensors);
                break;
            default:
                break;
            }
        }
    }
}

void manual::sensorScan(Turn drive, FrontSensing proxSensors)
{
    if (!proxSensors.frontSensorCheck())
    {
        Serial1.println("Front Sensor:");
        Serial1.println(proxSensors.obstacleFront());
        drive.stop();
        blocker = true;
    }
    if (proxSensors.frontSensorCheck())
    {
        blocker = false;
    }
    if (!proxSensors.leftSensorCheck())
    {
        Serial1.println("Left Sensor:");
        Serial1.println(proxSensors.obstacleLeft());
        drive.stop();
    }
    if (!proxSensors.rightSensorCheck())
    {
        Serial1.println("Right Sensor:");
        Serial1.println(proxSensors.obstacleRight());
        drive.stop();
    }
}

void manual::linescan()
{
    lineSensor.lineSensorRead();
    Serial1.println("Left Values:");
    Serial1.println(lineSensor.leftValue1());
    Serial1.println(lineSensor.leftValue2());
    Serial1.println("Right Values");
    Serial1.println(lineSensor.rightValue1());
    Serial1.println(lineSensor.rightValue2());
}

void manual::automaticMode(Turn drive, FrontSensing proxSensors)
{
    bool autoMode = true;
    while(autoMode)
    {

        drive.autoForward();
        drive.stop();
        //search(drive, proxSensors);
        // proxSensors.frontSensorCheck();
        // lineSensor.lineSensorRead();
        // if(!proxSensors.frontSensorCheck())
        // {
        //     drive.stop();
        //     autoMode = false;
        // }
        // if(lineSensor.leftLineSensing())
        // {
        //     drive.stop();
        //     detectedLeftLine(drive, proxSensors);
        // }
        // if(lineSensor.rightLineSensing())
        // {
        //     drive.stop();
        //     detectedRightLine(drive, proxSensors);
        // }
        // if(lineSensor.frontLineSensing())
        // {
        //     drive.stop();
        //     detectedFrontLine(drive, proxSensors);
        // }
        // if(lineSensor.leftLineSensing() && lineSensor.rightLineSensing())
        // {
        //     drive.stop();
        // }
        if(Serial1.available() > 0)
        {
            char x = (char)Serial1.read();

            switch (x)
            {
            case 'h':
                autoMode = false;
                drive.stop();
                break;
            }
        }
    }
}

void manual::detectedLeftLine(Turn drive, FrontSensing proxSensors)
{
    while (lineSensor.leftLineSensing())
    {
        drive.turnright(5);
        lineSensor.lineSensorRead();
        if (!proxSensors.frontSensorCheck())
        {
            proxSensors.obstacleFront();
            drive.stop();
            break;
        }
    }
}

void manual::detectedRightLine(Turn drive, FrontSensing proxSensors)
{
    while (lineSensor.rightLineSensing())
    {
        drive.turnleft(5);
        if (!proxSensors.frontSensorCheck())
        {
            proxSensors.obstacleFront();
            drive.stop();
            break;
        }
    }
}

void manual::detectedFrontLine(Turn drive, FrontSensing proxSensors)
{
    bool linefoundLeft = false;
    bool linefoundight = false;
    int i = 0;
    while ( i < 5) {
        drive.turnleft(5);
        lineSensor.lineSensorRead();
        if(lineSensor.leftLineSensing())
        {
            linefoundLeft = true;
            drive.stop();
            break;
        }
    }
    drive.turnright(25);
    while (i < 5)
    {
        drive.turnright(5);
        lineSensor.lineSensorRead();
        if(lineSensor.rightLineSensing())
        {
            linefoundight = true;
            drive.stop();
            break;
        }
    }
    drive.turnleft(25);
    if(linefoundLeft)
    {
        drive.turnleft(10);
    }
    if(linefoundight)
    {
        drive.turnright(10);
    }
    else if(linefoundight && linefoundLeft)
    {
        drive.turnleft(180);
    }
    
    if(!proxSensors.frontSensorCheck())
    {
        proxSensors.obstacleFront();
        drive.stop();
    }
}

void manual::search(Turn drive, FrontSensing proxSensor)
{
    bool leftline = false;
    bool rightline = false;
    int count = 0;
    drive.turnleft(90);
    lineSensor.frontLineSensing();
    do{
        drive.autoForward();
        lineSensor.lineSensorRead();
        if(lineSensor.frontLineSensing())
        {
            leftline = true;
            drive.stop();
            break;
        }
        count++;
    } while (lineSensor.frontLineSensing() || count < 10);
    drive.turnright(180);
    lineSensor.frontLineSensing();
    count = 0;
    do {
        drive.autoForward();
        lineSensor.lineSensorRead();
        if(lineSensor.frontLineSensing())
        {
            rightline = true;
            drive.stop();
            break;
        }
        count++;
    } while(lineSensor.frontLineSensing() || count < 10);
}
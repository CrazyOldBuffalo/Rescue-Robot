// Manual mode is used for most of the code
// Contains a switch case for controlling it manually and the code for automatic mode
// Includes the header file

#include "manual.h"

// Calibrates the turn sensors, linesensors, proximity sensors, etc
// waits for 1 second to ensure they're calibrated
// enters a loop until the user presses/sends x to exit
void Manual::manualMode(Turn move, FrontSensing proxSensors)
{
    move.calibrate();
    lineSensor.lineSensorSetup();
    delay(1000);
    while (!breaker)
    {
        // controls the robot based on the serial input from the xbee and reads it
        if (Serial1.available() > 0)
        {
            packet = (char)Serial1.read();
            switch (packet)
            {
            // moves the robot forward unless the robot has detected an object infront of it,
            // meaning the user has to turn left, right or reverse before they can move forward again
            case 'w':
                if (blocker)
                {
                    Serial1.println("Obstacle in Front");
                    break;
                }
                else
                {
                    // moves forward, stops and then scans for both the proximity sensors and lines
                    move.forward();
                    delay(50);
                    move.stop();
                    sensorScan(move, proxSensors);
                    linescan(move);
                    break;
                }
            // turns left by 15 degrees and performs the same scans
            case 'a':
                move.turnleft(15);
                delay(50);
                sensorScan(move, proxSensors);
                linescan(move);
                break;
            // turns right by 15 degrees and performs the same scans
            case 'd':
                move.turnright(15);
                delay(50);
                sensorScan(move, proxSensors);
                linescan(move);
                break;
            // moves backward and scans
            case 's':
                move.backward();
                delay(50);
                move.stop();
                sensorScan(move, proxSensors);
                linescan(move);
                break;
            // Exits the manual mode, for when you've finished
            case 'x':
                move.stop();
                delay(1000);
                Serial1.println("Exiting");
                breaker = true;
                break;
            // Switches to automatic mode
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

// Performs a sensor scan for objects infront, left and right of the robot and prints out a warning if something is detected
void Manual::sensorScan(Turn drive, FrontSensing proxSensors)
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

// reads the linesensors and prints the values
// more for testing
void Manual::linescan(Turn drive)
{
    lineSensor.lineSensorRead();
    if (lineSensor.leftLineSensing())
    {
        Serial1.println("Caution Wall Found Left");
        drive.stop();
    }
    if (lineSensor.rightLineSensing())
    {
        Serial1.println("Caution Wall Found Right");
        drive.stop();
    }
    if (lineSensor.frontLineSensing())
    {
        Serial1.println("Caution Wall Found Front");
        drive.stop();
    }
}

// Automatic mode of the program
// sets the loop to run until the exit key is pressed (but will only trigger at the end of that run)
// sets 3 variables for the lines to false for when the code loops again to be used by the search function
// Runs the robot to move forward and then do a search for any lines
// Checks after the search to determine what the robot should do depending on the results

void Manual::automaticMode(Turn drive, FrontSensing proxSensors)
{
    bool autoMode = true;
    do
    {
        if (Serial1.available() > 0)
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
        linefoundLeft = false;
        linefoundRight = false;
        linefoundFront = false;
        movingForward(drive, proxSensors);
        search(drive, proxSensors);
        // Make decision on next move based on what lines were detected around the robot
        if (linefoundLeft && linefoundRight && !linefoundFront)
        {
            delay(1000);
            if (Serial1.available() > 0)
            {
                char x = (char)Serial1.read();
                if (x == 'h')
                {
                    autoMode = false;
                    drive.stop();
                    Serial1.println("Exiting Auto Mode");
                }
            }
            else
            {
                movingForward(drive, proxSensors);
            }
        }
        if (!linefoundLeft && linefoundRight && !linefoundFront)
        {
            uhohcounter = 0;
            delay(1000);
            if (Serial1.available() > 0)
            {
                char x = (char)Serial1.read();
                if (x == 'h')
                {
                    autoMode = false;
                    drive.stop();
                    Serial1.println("Room Found Left");
                    Serial1.println("Exiting Auto Mode");
                }
            }
            else
            {
                RoomLeft(drive, proxSensors);
            }
        }
        if (linefoundLeft && !linefoundRight && !linefoundFront)
        {
            uhohcounter = 0;
            delay(1000);
            if (Serial1.available() > 0)
            {
                char x = (char)Serial1.read();
                if (x == 'h')
                {
                    autoMode = false;
                    drive.stop();
                    Serial1.println("Room Found Right");
                    Serial1.println("Exiting Auto Mode");
                }
            }
            else
            {
                RoomRight(drive, proxSensors);
            }
        }
        if (linefoundLeft && !linefoundRight && linefoundFront)
        {
            uhohcounter = 0;
            delay(1000);
            if (Serial1.available() > 0)
            {
                char x = (char)Serial1.read();
                if (x == 'h')
                {
                    autoMode = false;
                    drive.stop();
                    Serial1.println("Turn Right");
                    Serial1.println("Exiting Auto Mode");
                }
            }
            else
            {
                TurnRight(drive, proxSensors);
            }
        }
        if (!linefoundLeft && linefoundRight && linefoundFront)
        {
            uhohcounter = 0;
            delay(1000);
            if (Serial1.available() > 0)
            {
                char x = (char)Serial1.read();
                if (x == 'h')
                {
                    autoMode = false;
                    drive.stop();
                    Serial1.println("Room Found Right");
                    Serial1.println("Exiting Auto Mode");
                }
            }
            else
            {
                TurnLeft(drive, proxSensors);
            }
        }
        if ((!linefoundLeft && !linefoundRight && linefoundFront))
        {
            uhohcounter = 0;
            delay(1000);
            if (Serial1.available() > 0)
            {
                char x = (char)Serial1.read();
                if (x == 'h')
                {
                    autoMode = false;
                    drive.stop();
                    Serial1.println("Room Found Left");
                    Serial1.println("Exiting Auto Mode");
                }
            }
            else
            {
                TJunction(drive, proxSensors);
            }
        }
        if (linefoundLeft && linefoundRight && linefoundFront)
        {
            uhohcounter = 0;
            End(drive, proxSensors);
        }
        if (!linefoundLeft && !linefoundRight && !linefoundFront)
        {
            uhohcounter++;
            if (uhohcounter >= 2)
            {
                UhOh(drive, proxSensors);
                break;
            }
        }
    } while (autoMode);
}

// Automatic mode function that keeps the robot away from the left line when it's detected and turns it away by turning right
void Manual::detectedLeftLine(Turn drive, FrontSensing proxSensors)
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

// Automatic mode function that keeps the robot away from the right line when it's detected and turns it away by turning right
void Manual::detectedRightLine(Turn drive, FrontSensing proxSensors)
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

// Test Function - Unused
void Manual::detectedFrontLine(Turn drive, FrontSensing proxSensors)
{
    linefoundLeft = false;
    linefoundRight = false;
    int i = 0;
    while (i < 5)
    {
        drive.turnleft(5);
        lineSensor.lineSensorRead();
        if (lineSensor.leftLineSensing())
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
        if (lineSensor.rightLineSensing())
        {
            linefoundRight = true;
            drive.stop();
            break;
        }
    }
    drive.turnleft(25);
    if (linefoundLeft)
    {
        drive.turnleft(10);
    }
    if (linefoundRight)
    {
        drive.turnright(10);
    }
    else if (linefoundRight && linefoundLeft)
    {
        drive.turnleft(180);
    }

    if (!proxSensors.frontSensorCheck())
    {
        proxSensors.obstacleFront();
        drive.stop();
    }
}

// Search function that sets 3 line variables to false
// turns left 90 degrees (roughly)
// and then drives forward for a second or until it detects a line - if it detects a line it sets the variable to true
// returns to the original postion and then does a 180 and repeats for the other line
// then returns to the original position
void Manual::search(Turn drive, FrontSensing proxSensor)
{
    Serial1.println("Seaching");
    linefoundLeft = false;
    linefoundRight = false;
    linefoundFront = false;
    int count = 0;
    while (lineSensor.frontLineSensing() || count < 4)
    {
        count++;
        drive.autoForward();
        delay(50);
        lineSensor.lineSensorRead();
        if (lineSensor.frontLineSensing())
        {
            linefoundFront = true;
            drive.stop();
            break;
        }
        if (lineSensor.leftLineSensing())
        {
            detectedLeftLine(drive, proxSensor);
        }
        if (lineSensor.rightLineSensing())
        {
            detectedRightLine(drive, proxSensor);
        }
        if (!proxSensor.frontSensorCheck())
        {
            Serial1.println(proxSensor.obstacleFront());
            drive.stop();
            break;
        }
    }
    count = 0;
    drive.turnleft(90);
    delay(50);
    while (count < 5)
    {
        count++;
        lineSensor.lineSensorRead();
        drive.autoForward();
        delay(50);
        lineSensor.lineSensorRead();
        if (lineSensor.frontLineSensing())
        {
            linefoundLeft = true;
            drive.stop();
            break;
        }
        if (!proxSensor.frontSensorCheck())
        {
            Serial1.println(proxSensor.obstacleFront());
            drive.stop();
            break;
        }
    }
    drive.stop();
    while (count != 0)
    {
        drive.autoBackward();
        delay(50);
        count--;
    }
    drive.turnright(180);
    count = 0;
    delay(50);
    while (count < 5)
    {
        count++;
        lineSensor.lineSensorRead();
        drive.autoForward();
        delay(50);
        lineSensor.lineSensorRead();
        if (lineSensor.frontLineSensing())
        {
            linefoundRight = true;
            drive.stop();
            break;
        }
        delay(50);
        proxSensor.frontSensorCheck();
        if (!proxSensor.frontSensorCheck())
        {
            Serial1.println(proxSensor.obstacleFront());
            drive.stop();
            break;
        }
    }
    drive.stop();
    while (count != 0)
    {
        drive.autoBackward();
        delay(100);
        count--;
    }
    drive.turnleft(90);
    drive.stop();
}

// drives the robot forward for 1 second whilst correcting for any lines detected left or right of it
void Manual::movingForward(Turn drive, FrontSensing proxSensors)
{
    int timer = 0;
    while (timer < 5)
    {
        timer++;
        drive.autoForward();
        delay(50);
        lineSensor.lineSensorRead();
        if (lineSensor.frontLineSensing())
        {
            drive.stop();
            break;
        }
        if (!lineSensor.frontLineSensing())
        {
            if (lineSensor.leftLineSensing())
            {
                detectedLeftLine(drive, proxSensors);
            }
            if (lineSensor.rightLineSensing())
            {
                detectedRightLine(drive, proxSensors);
            }
        }
        if (!proxSensors.frontSensorCheck())
        {
            drive.stop();
            break;
        }
    }
}

// function for if a room is detected to the left based on the search and if statements in automode
void Manual::RoomLeft(Turn drive, FrontSensing proxSensors)
{
    drive.stop();
    Serial1.write("Left Room HERE");
    drive.turnright(5);
}

// function for if a room is detected to the right based on the search and if statements in automode
void Manual::RoomRight(Turn drive, FrontSensing proxSensors)
{
    drive.stop();
    Serial1.write("Right Room Here");
    drive.turnleft(5);
}

// function for if no lines are detected around the robot and exits the automode
void Manual::UhOh(Turn drive, FrontSensing proxSensors)
{
    Serial1.write("An Error Has Occurred with the robot, Aborting");
    drive.stop();
    autoMode = false;
}

// Function for when a Tjunction is detected (No left or right but front line) will turn left by default
void Manual::TJunction(Turn drive, FrontSensing proxSensors)
{
    drive.stop();
    Serial1.write("TJunction found");
    drive.turnleft(90);
}

// Function for when a Left turn is detected (No left line, but front and right line)
void Manual::TurnLeft(Turn drive, FrontSensing proxSensors)
{
    drive.stop();
    Serial1.write("Left Turn");
    drive.turnleft(90);
}

// Function for when a Right turn is detected (No right line, but front and left line)
void Manual::TurnRight(Turn drive, FrontSensing proxSensors)
{
    drive.stop();
    Serial1.write("Right Turn");
    drive.turnright(90);
}

// Function for when an end is detected (Left, right and front lines)
void Manual::End(Turn drive, FrontSensing proxSensors)
{
    drive.stop();
    Serial1.write("End of map");
    drive.turnleft(90);
    drive.turnleft(90);
}
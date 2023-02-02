#include "manual.h"

void manual::manualMode(drive move) {
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
                break;
            case 'a':
                move.turnleft();
                delay(500);
                move.stop();
                break;
            case 'd':
                move.turnright();
                delay(500);
                move.stop();
                break;
            case 's':
                move.backward();
                delay(500);
                move.stop();
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
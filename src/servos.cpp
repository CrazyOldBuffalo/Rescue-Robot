#include <Arduino.h>
#include "servos.h"

void attach() {
    Serial.println("Servo Attached");
}

void detach() {
    Serial.println("Servo Detached");
}

void write(int x) {
    Serial.println("x");
}
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "sabertooth.h"

// Assuming we're using four motors
SaberMotor right_front(128, SABER_MOTOR_1, 9600);
SaberMotor right_back(128, SABER_MOTOR_2, 9600);
SaberMotor left_front(129, SABER_MOTOR_1, 9600);
SaberMotor left_back(129, SABER_MOTOR_2, 9600);

void setup() {
    // Serial init
    Serial.begin(9600);
}

void loop() {
    // Do nothing for now
}

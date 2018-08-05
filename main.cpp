#include <Arduino.h>
#include <SoftwareSerial.h>

// Which pins don't matter and we aren't using rx
#define SOFT_RX 10
#define SOFT_TX 11

SoftwareSerial saber_serial(SOFT_RX, SOFT_TX);

void setup() {
    // Serial init
    Serial.begin(9600);
    saber_serial.begin(9600);
}

void loop() {
    // Do nothing for now
}

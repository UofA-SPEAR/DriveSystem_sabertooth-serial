#include <Arduino.h>
#include <SoftwareSerial.h>

// Which pins don't matter and we aren't using rx
#define SOFT_RX 10
#define SOFT_TX 11

void setup() {
    // Serial init
    Serial.begin(9600);
}

void loop() {
    // Do nothing for now
}

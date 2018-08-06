#include <Arduino.h>
#include <SoftwareSerial.h>

#include "main.h"
#include "sabertooth.h"

// Assuming we're using four motors
SaberMotor right_front(128, SABER_MOTOR_1, 9600);
SaberMotor right_back(128, SABER_MOTOR_2, 9600);
SaberMotor left_front(129, SABER_MOTOR_1, 9600);
SaberMotor left_back(129, SABER_MOTOR_2, 9600);

cmd_t command;

void setup() {
    // Serial init
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() >= 2) {
        read_serial_command(&command);

        handle_command(&command);
    }
}

/**@brief Function to handle a command
 */
static void handle_command(cmd_t * cmd) {
    Serial.println("Command recieved!");

    if (cmd->direction == SIDE_LEFT) {
        Serial.print("Left turn at ");
    } else if (cmd->direction == SIDE_RIGHT) {
        Serial.print("Right turn at ");
    }

    Serial.print(cmd->value);
    Serial.println("%");
}


/**@brief Function to read in a serial command
 */
static void read_serial_command(cmd_t * cmd) {
    uint8_t buf[2];

    Serial.readBytes(buf, 2);
    
    cmd->side  = (char) buf[0];
    cmd->value = (int8_t) buf[1]; // this may not work, needs testing
}

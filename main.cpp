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
uint32_t time = 0;

void setup() {
    // Serial init
    Serial.begin(9600);

    right_front.setRampingRate(30);
    left_front.setRampingRate(30);
    right_front.setMinVoltage(12);
    left_front.setMinVoltage(12);
}

void loop() {
    if (Serial.available() >= 2) {
        read_serial_command(&command);

        handle_command(&command);
    }

    if ( (millis() - time) > 1000 ) { // if more than 1s has elapsed without a command
        handle_timeout();
    }

}

/**@brief Function to handle a command timeout.
 *
 * @details Turns all motors off.
 */
static void handle_timeout() {
    time = millis();

    right_front.setMotorSpeed(0);
    right_back.setMotorSpeed(0);
    left_front.setMotorSpeed(0);
    left_back.setMotorSpeed(0);
}

/**@brief Function to handle a command
 */
static void handle_command(cmd_t * cmd) {

    if (cmd->side == SIDE_LEFT) {
        left_front.setMotorSpeed(cmd->value);
        left_back.setMotorSpeed(cmd->value);
    } else if (cmd->side == SIDE_RIGHT) {
        right_front.setMotorSpeed(cmd->value);
        right_back.setMotorSpeed(cmd->value);
    } else {
        while(Serial.read() != -1);
    }


}


/**@brief Function to read in a serial command
 *
 * @note Also resets the time variable for timeouts
 */
static void read_serial_command(cmd_t * cmd) {
    char buf[2];

    Serial.readBytes(buf, 2);
    
    cmd->side  = (char) buf[0];
    cmd->value = (int8_t) buf[1]; // this may not work, needs testing

    time = millis();
}

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
    if (Serial.available() >= 5) {
        if(read_serial_command(&command) == CMD_SUCCESS) {
            handle_command(&command);
        }
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

    switch(cmd->side){
        case SIDE_TOP:
            right_front.setMotorSpeed(cmd->value);
            left_front.setMotorSpeed(cmd->value);
            break;
        case SIDE_BOTTOM:
            left_back.setMotorSpeed(cmd->value);
            right_back.setMotorSpeed(cmd->value);
            break;
        case SIDE_RIGHT:
            right_front.setMotorSpeed(cmd->value);
            right_back.setMotorSpeed(cmd->value);
            break;
        case SIDE_LEFT:
            left_front.setMotorSpeed(cmd->value);
            left_back.setMotorSpeed(cmd->value);
            break;
        case WHEEL_TOP_LEFT:
            left_front.setMotorSpeed(cmd->value);
            break;
        case WHEEL_TOP_RIGHT:
            right_front.setMotorSpeed(cmd->value);
            break;
        case WHEEL_BOTTOM_LEFT:
            left_back.setMotorSpeed(cmd->value);
            break;
        case WHEEL_BOTTOM_RIGHT:
            right_back.setMotorSpeed(cmd->value);
            break;
        default:
            while(Serial.read() != -1);
    }
}


/**@brief Function to read in a serial command
 *
 * @note Also resets the time variable for timeouts
 */
static void read_serial_command(cmd_t * cmd) {
    char buf[5];

    Serial.readBytes(buf, 5);
    
    char start = buf[0];
    cmd->side  = (char) buf[1];
    cmd->value = (int8_t) buf[2]; // this may not work, needs testing
    char check = buf[3];
    char end = buf[4];

    if(start != 2 && end != 3 && check != (buf[1] + buf[2])){
        return CMD_ERR_INVALID;
    }

    time = millis();
    return CMD_SUCCESS;
}

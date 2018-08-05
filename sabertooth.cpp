#include <Arduino.h>
#include <SoftwareSerial.h>

#include "sabertooth.h"

/**@brief Constructor function for SaberMotor class.
 *
 * @details Changes a few settings variables and initialises serial at a baudrate.
 */
SaberMotor::SaberMotor(uint8_t address, saber_motor_t motor_num, uint8_t baudrate) {
    settings.address = address;
    settings.motor_num = motor_num;

    this->serialInit(baudrate);
}

/**@brief Function to initialise soft serial interface
 */
void SaberMotor::serialInit(uint8_t baudrate) {
    // End serial in case it's running
    saber_serial.end();

    // Restart serial at specified baudrate
    saber_serial.begin(baudrate);

    settings.baudrate = baudrate;
}

/**@brief Function for sending command over serial.
 *
 * @details Writes the address, then the command number, then the command value to send over software serial.
 */
void SaberMotor::sendCommand(uint8_t command, uint8_t value) {
    // From the datasheet: the checksum is a 7-bit value hat is just the addition of all values
    uint8_t checksum = (settings.address + command + value) &0b01111111;

    saber_serial.write(settings.address);
    saber_serial.write(command);
    saber_serial.write(value);
    saber_serial.write(checksum);
}

/**@brief Function to set a motor speed.
 *
 * @param speed Signed integer representing speed to set motor at.
 *              Value > 0 represents forward motion and Value < 0 represents reverse motion.
 */
void SaberMotor::setMotorSpeed(int8_t speed) {
    /* Motor command numbers:
     * 0: Drive forward motor 1
     * 1: Drive backwards motor 1
     * 4: Drive forward motor 2
     * 5: Drive backwards motor 2
     */

    uint8_t cmd, value;

    /* Set the command offset (which motor is which)
     * As of now the only valid inputs are 1 and 2.
     * Not sure how to handle invalid inputs.
     * I'm going to assume people don't make mistakes.
     */
    if (settings.motor_num == SABER_MOTOR_1) {
        cmd = 0;
    } else if (settings.motor_num == SABER_MOTOR_2) {
        cmd = 4;
    }

    /* Change settings based on direction
     */
    if (speed >= 0) { // If you're going forwards:
        value = speed;
    } else { // If you're going backwards
        value = abs(speed);
        cmd += 1; // Set command to run motor backwards
    }

    /* Actually send command
     */
    this->sendCommand(cmd, value);
}

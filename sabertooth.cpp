#include <Arduino.h>
#include <SoftwareSerial.h>

#include "sabertooth.h"

/**@brief Constructor function for SaberMotor class.
 *
 * @details Changes a few settings variables and initialises serial at a baudrate.
 */
SaberMotor::SaberMotor(uint8_t address, uint8_t motor_num, uint8_t baudrate) {
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



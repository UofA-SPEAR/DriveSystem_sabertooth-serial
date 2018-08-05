#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial saber_serial(SABER_RX, SABER_TX);

/**@brief Constructor function for SaberMotor class.
 *
 * @details Simply sets a few settings variables.
 */
SaberMotor::SaberMotor(uint8_t address, uint8_t motor_num) {
    settings.address = address;
    settings.motor_num = motor_num;
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

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

void SaberMotor::sendCommand(uint8_t command, uint8_t value) {

}

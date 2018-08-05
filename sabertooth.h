#ifndef SABERTOOTH_H_
#define SABERTOOTH_H_

#include <Arduino.h>
#include <SoftwareSerial>

extern SoftwareSerial saber_serial(SABER_RX, SABER_TX);

typedef enum {
    SABER_SUCCESS,
    SABER_INVALID_VALUE,
} saber_err_t;

typedef struct {
    int8_t speed;

    uint8_t ramp_setting;
    uint8_t deadband;

    uint8_t baudrate;

    uint8_t address;
} saber_channel_settings_t

/**@brief Class for controlling a single motor on the Sabertooth.
 *
 * @details Class that communicates with the Sabertooth 60A dual motor driver to control one motor.
 *          Instantiate with info on the address of the driver, which motor to control, and maybe a few
 *          settings.
 *
 * @note saber_serial must be initialised with the proper baud rate before this class can be used.
 */
class SaberMotor {
    public:
        void setSpeedMotor(int8_t speed);

        // These config functions apply to both channels
        void setRampingRate(uint8_t ramp_setting);
        void setDeadband(uint8_t deadband);

        // Only sends valid values. You must re-init saber_serial after you call this.
        // Don't call this if you don't know what you're doing.
        saber_err_t setBaudRate(uint8_t);

    private:
        saber_channel_settings_t settings;

        void sendCommand(uint8_t command, uint8_t value);
}

#endif

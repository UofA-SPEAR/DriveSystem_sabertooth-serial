#ifndef SABERTOOTH_H_
#define SABERTOOTH_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

#define SABER_RX    10 // This pin will be unused
#define SABER_TX    11 // Doesn't really matter what this is

SoftwareSerial saber_serial(SABER_RX, SABER_TX);

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
    uint8_t motor_num;
} saber_channel_settings_t;

/**@brief Class for controlling a single motor on the Sabertooth.
 *
 * @details Class that communicates with the Sabertooth 60A dual motor driver to control one motor.
 *          Instantiate with info on the address of the driver, which motor to control, and maybe a few
 *          settings.
 *
 * @note saber_serial must be initialised with the proper baud rate before this class can be used.
 *
 * TODO: add max voltage setting function (and min voltage)
 */
class SaberMotor {
    public:
        SaberMotor(uint8_t address, uint8_t motor_num, uint8_t baudrate);

        void setSpeedMotor(int8_t speed);

        // These config functions apply to both channels
        void setRampingRate(uint8_t ramp_setting);
        void setDeadband(uint8_t deadband);
        saber_err_t setBaudRate(uint8_t);

        // This *shouldn't* be used but I'm exposing it here anyways
        void serialInit(uint8_t baudrate);

    private:
        saber_channel_settings_t settings;

        void sendCommand(uint8_t command, uint8_t value);
};

#endif

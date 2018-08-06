# Sabertooth Drive Code #

This is a repo for the arduino code for using [Sabertooth Motor Drivers](https://www.robotshop.com/ca/en/sabertooth-dual-motor-driver.html).

This will use packetized serial commands to control each motor.
I'll use the Uno and it wil get commands over serial from the Jetson.
I'll also be using the SoftwareSerial library for serial output to the drivers.

## Status ##

If it's pushed to the repo it builds. (If it doesn't @davidlenfesty will give you a stern talking to).

The sabertooth library is finished, but completely untested (we don't have the drivers in yet).
As far as I'm aware it should work, people are welcome to review the datasheet and all the serial stuff.

## Control Interface ##

For now the drive system is controlled via serial over USB.
The command is a 2-byte "packet" with information on the side and the power level.
The first byte is a value that specifies which side you are controlling, it's
a letter encoded in ASCII, L or R for left and right, respectively.
The second is a signed integer specifying the magnitude.

The value is a signed integer from -100 to 100, specifying reverse and forward power, in percent.

Some examples:
- "L35" and "R60" would make the rover turn to the left.
- "L-100" and "R-100" would make the rover go full power, backwards. (Please don't do this ever)

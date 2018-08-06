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
The command is a 2-byte "packet" with information on the type of change in motion and magnitude.
The first byte is a value that specifies if you're changing power or turning direction,
a letter encoded in ASCII, P and T, respectively. The second is a signed integer specifying the magnitude.

For power, the values can range from -100 to +100, representing power in percent.
For turning, the values can range from -90 to 90, representing an angle I guess.
Not too sure on exactly how this should be implemented but that can be changed later.

Some examples:
- "P35": go forward at 35% power.
- "T-45": turn left at 45 degrees or something.
- "P-90": back up at 90% power.

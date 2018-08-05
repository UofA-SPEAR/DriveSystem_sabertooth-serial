# Sabertooth Drive Code #

This is a repo for the arduino code for using [Sabertooth Motor Drivers](https://www.robotshop.com/ca/en/sabertooth-dual-motor-driver.html).

This will use packetized serial commands to control each motor.
I'll use the Uno and it wil get commands over serial from the Jetson.
I'll also be using the SoftwareSerial library for serial output to the drivers.

## Status ##

If it's pushed to the repo it builds. (If it doesn't @davidlenfesty will give you a stern talking to).

The sabertooth library is finished, but completely untested (we don't have the drivers in yet).
As far as I'm aware it should work, people are welcome to review the datasheet and all the serial stuff.

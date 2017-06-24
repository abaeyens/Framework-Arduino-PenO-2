# RuneMotor
The RuneMotor library is a basic motor library specifically designed for the hardware used in the P&O2 projects. It is largely based on the Dwengo motor library.
It is not written object oriented. If you want to control more than two motors, let me know and I'll see what I can do to write an object-oriented version that supports extra motors.
Every motor uses two pins, one for speed control (to control to the MOSFET) and one for direction control (to control the relais).
The pinout can be configured in the `RuneMotor.h` file. Please note that the pinout of the Arduino differs from the P&O pinout.

Features:
- Supports PWM speed control (expected hardware configuration: PWM on MOSFET)
- Supports direction switching (expected hardware configuration: DPDT relais)
- Intelligent switching of the relais saves power (the relais consume a lot of power)
- Automatically avoids high currents when switching the direction of a motor.

## Examples
- RuneMotor_example_01: Controlling the motors.
- RuneMotor_example_02: Reading the current speed of motors.

## Usage
Initiate the motors.
```cpp
initMotors();
```

Set the speed of motor 1 to maximum speed forward. Using a value higher than 255 does not increase the speed of the motor.
```cpp
setSpeedMotor1(255);
```

Set the speed of motor 1 to maximum speed backward.
```cpp
setSpeedMotor1(-255);
```

Stop motor 1.
```cpp
setSpeedMotor1(0);
```

Stop both motors.
```cpp
stopMotors();
```

Read the current speed (e.g. speed value last written) of motor 1.
```cpp
getSpeedMotor1(0);
```

The functions for motor 2 are extremely similar, just replace the `1` in the command with a `2`.

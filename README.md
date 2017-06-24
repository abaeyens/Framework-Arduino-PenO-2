# Framework Arduino P&O-2

A framework with libraries to be used for developing Arduino robots in P&O 2.

Currently the framework consist of three libraries:
- RuneWork: A simple taskmanager and sound player. Can be used to call functions in the future. However, it currently does not support direct control of servos.
- RuneMotor: A motorcontroller, specially suited for the electronics used in the P&O courses.
- VirtualButton: A class to create virtual buttons and virtual pedals. They are of great use when using a remote control with non-proportional controls (e.g. a TV set remote). Virtual pedals allow to limit the acceleration of motors.

The RuneWork library is fully independent of the other two. However, the VirtualButton is designed to be used together with RuneWork. All three combined they can be used as a backbone for your program, along with the Arduino standard library and your IR decoding library of choice.

These three libraries were developed during a P&O-2 project from february to mai 2017. A small wheelchair-robot was designed during this course.

# How to use
1. Download the repository as a zip file to a (temporary) folder of choice
2. Unpack the zip file.
3. Copy the three folders, named `RuneWork2`, `RuneMotor` and `VirtualButton`, to the Arduino library folder. On Windows machines the path is `/Documents/Arduino/libraries`.
4. (Re)start the Arduino IDE. Everything should work straight out of the box now. Don't forget to add the `#include` in your mainprogram however.

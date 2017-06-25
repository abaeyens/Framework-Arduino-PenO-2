# Framework Arduino P&O-2

A framework with libraries to be used for developing Arduino robots in P&O 2.

Currently the framework consist of three libraries:
- RuneWork2: A simple taskmanager and sound player. Can be used to call functions in the future. Currently it does not support controlling servos very well.
- RuneMotor: A motorcontroller, specially suited for the electronics used in the P&O courses.
- VirtualButton: A class to create virtual buttons and virtual pedals. They are of great use when using a remote control with non-proportional controls (e.g. a TV set remote). Virtual pedals allow to limit the acceleration of motors.

The RuneWork2 library is fully independent of the other two. However, the VirtualButton is designed to be used together with RuneWork2. All three combined they can be used as a backbone for your program, along with the Arduino standard library and your IR decoding library of choice.


## How to
### Installation
1. Download the repository as a zip file to a (temporary) folder of choice
2. Unpack the zip file.
3. Copy the three folders, named `RuneWork2`, `RuneMotor` and `VirtualButton`, to the Arduino library folder. On Windows machines the path is `/Documents/Arduino/libraries`.
4. (Re)start the Arduino IDE. Everything should work straight out of the box now. Don't forget to add the `#include` in your mainprogram however.


### Usage
There are some example Arduino sketches in the `example` folders in the three library folders. If something isn't yet completely clear, please post an issue or send me an e-mail.


## About
These three libraries were developed during a P&O-2 group project from february to mai 2017. A small wheelchair-robot was designed during this course.


## FAQ
- For which Arduino models can these libraries be used?

   These libraries are developed for use with the Arduino Uno Rev3, which uses the ATmega328p microcontroller. As these libraries depend on the Arduino library for most function the code should also work for other Arduino models, however some pins might have to be remapped and there might be some small issues with the timers as well. The VirtualButton library should work fine on any Arduino as it is just regular C++ code and doesn't use any particular library.  

- Can I use servos together with the RuneWork2 library?

   Short answer: no. Slightly longer answer: yes, but it's rather difficult. Most servo libraries use Timer1 for timing the pulses sent to the servo. However, this timer is also used by the RuneWork2 library.

- Is the RuneWork2 library stable?

   During the project it performed exactly as required, but please be careful in your programming. Unlike on a normal computer, there are no failsafes for e.g. buffer overflows on an Arduino. While it's unlikely your device will be physically damadged, it may crash and/or reboot due to small errors in the code.  

- What timers do these libraries use?

   RuneMotor uses the standard Arduino PWM libraries and thus Timer0 is used, which by default is also used for the function delay(). The PWM frequency is not changed and is around 1 kHz. The RuneWork2 library uses Timer1 for the taskmanaging system and Timer2 for playing sounds. The VirtualButton library doesn't use any timers.  

- How does the RuneWork2 taskmanager handle tasks that take a lot of time? Can I use delays in those tasks/functions?
   The RuneWork2 taskmanager is not designed to handle tasks that take more time than the defined period (see RuneWork2 README). I strongly disadvise the use of delays inside RuneWork2 tasks, but if really want, you can.

# Framework Arduino P&O-2

A framework with libraries to be used for developing Arduino robots in P&O 2.

Currently the framework consist of three libraries:
- RuneWork2: A simple taskmanager and sound player. Is based on cooperative multitasking. Can be used to call functions in the future. Currently it does not support controlling servos very well.
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
There are some example Arduino sketches in the `example` folders in the three library folders. If something isn't yet completely clear, please post an issue (here on GitHub) or send me an e-mail.


## About
These three libraries were developed during a P&O 2 group project in the second semester of the year 2016-2017 in the course P&O 2 of the KULeuven. **CWISPLE**, a small wheelchair-robot was designed and built during this course. This P&O 2 project was a group project of Team 413 and involved much more than just these libraries, like designing and building the wheelchair-robot, experiments, ... While I developed these libaries, the project as a whole wouldn't have been possible at all without the fantastic efforts of all the team members of Team 413. The team members of Team 413 (of 2017) were E. Broeders, S. Coppens, K. Dermul, A. Deschrevel, J. Christiaens, W. De Schepper, S. Boon and A. Baeyens.

If you use this software in your project and you share or publish the code used in your project (like for example in the reports for P&0 2), please refer properly to this code as required by the GNU GPLv3 license. Please also reference to Team 413 (of 2017 - there's a team 413 every year) and it's members.


## FAQ
- What is cooperative multitasking?

   Cooperative mulitasking differs from pre-emptive multasking, as is used in about all current advanced operating systems (Linux Cent OS, Windows 10, Mac OS X, Android, ...) in that the taskmanager does not end or interrupt a running process. The processess have to end and limit their runtime by theirselves . This makes cooperative multasking simpler to implement. The downside is that one process can hang the whole machine. So, code carefully. If you have 'difficult' code, try to put in the main loop. See [Wikipedia: Cooperative multitasking](https://en.wikipedia.org/wiki/Cooperative_multitasking) for a more thorough explication.
   
   
- For which Arduino models can these libraries be used?

   These libraries are developed for use with the Arduino Uno Rev3, which uses the ATmega328p microcontroller. As these libraries depend on the Arduino library for most function the code should also work for other Arduino models, however some pins might have to be remapped and there might be some small issues with the timers as well. The VirtualButton library should work fine on any Arduino as it is just regular C++ code and doesn't use any particular library.  

- Can I use servos together with the RuneWork2 library?

   Short answer: no. Slightly longer answer: yes, but it's rather difficult. Most servo libraries use Timer1 for timing the pulses sent to the servo. However, this timer is also used by the RuneWork2 library.

- Is the RuneWork2 library stable?

   During the project it performed exactly as required, but please be careful in your programming. Unlike on a normal computer, there are no failsafes for e.g. buffer overflows on an Arduino. While it is unlikely that your device will be physically damadged, it may crash and/or reboot due to small errors in the code. The README in the RuneWork2 folder exlains the usage of the RuneWork2 library.  

- What timers do these libraries use?

   RuneMotor uses the standard Arduino PWM libraries and thus Timer0 is used, which by default is also used for the function delay(). The PWM frequency is not changed and is around 1 kHz. The RuneWork2 library uses Timer1 for the taskmanaging system and Timer2 for playing sounds. The VirtualButton library doesn't use any timers.  

- How does the RuneWork2 taskmanager handle tasks that take a lot of time? Can I use delays in those tasks/functions?

   The RuneWork2 taskmanager is not designed to handle tasks that take more time than the defined period (see RuneWork2 README). I strongly disadvise the use of delays inside RuneWork2 tasks, but if you really want, you can.

/* Example_02.ino - Example Arduino sketch for the RuneMotor library
 * Copyright (C) 2017  Arne Baeyens
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *
 * Motor functions are inspired by the DwengoMotor library for PIC microcontrollers.
 * 
 */

#include <RuneMotor.h>

// A global variable.
int a;

void setup() {
  // Initiate the motor pins.
  // You can change the pin numbers in the library file if necessary.
  initMotors();

  // We'll use the serial port 
  Serial.begin(9600);
}

void loop() {
  // Let's set the speeds of motor 1 to a speed of choice.
  setSpeedMotor1(135);

  // We can now read the speed with the function getMotorSpeed1().
  a = getSpeedMotor1();

  // We can send it over the serial port to the computer.
  Serial.print("Speed of motor 1: ");
  Serial.println(a);

  delay(1000);
}

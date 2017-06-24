/* Example_01 - Example Arduino skecth for the RuneMotor library
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
 * Motor functions are inspired by the DwengoMotor library for PIC microcontrollers.
 */

#include <RuneMotor.h>

void setup() {
  // Initiate the motor pins.
  // You can change the pin numbers in the library file if necessary.
  initMotors();
}

void loop() {
  // Let's start with going full speed forward!
  // Full speed forward is 255. Using a higher value will not increase the speed.
  setSpeedMotor1(255);  // Motor 1
  setSpeedMotor2(255);  // Motor 2

  // Now take some time to go forward
  delay(1000);

  // Better to stop, we might hit something!
  stopMotors();

  // And wait again.
  delay(1000);

  // Thanks to PWM, we can also change the speed gradually.
  // A for-loop is used to go trough all the speeds.
  // Increase speed from 0 to 255 (maximum).
  for(int i=0; i<255; i++){
    setSpeedMotor1(i);
    setSpeedMotor2(i);
    delay(10);
  }
  // Decrease speed from 255 to 0.
  for(int i=256; i>0; i--){
    setSpeedMotor1(i);
    setSpeedMotor2(i);
    delay(10);
  }
  // Stop the motors to be sure.
  stopMotors();
  delay(1000);

  // It's also possible to ride backwards.
  // Full speed backward is -255. Using a lower value will not increase the speed.
  // We now use the value 128 which should give a speed of around 1/3 to 1/2 of the maximum speed.
  setSpeedMotor1(-128);
  setSpeedMotor2(-128);
  delay(1000);

  // Let's stop the demo.
  stopMotors();

  // And start again after five seconds.
  delay(5000);
}

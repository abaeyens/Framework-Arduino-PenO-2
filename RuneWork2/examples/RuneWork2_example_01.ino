/* VirtualButton.h - RuneWork2_example_01.ino - Example Arduino skecth for the RuneWork2 library.
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
 * 
 * Arne Baeyens - Contact: 2arne.baeyens@gmail.com
 * 
 */

#include <RuneWork2.h>

// We'll use the builtin led.
#define ledBuiltIn 13


void myFunction() {
  // Flip the state of the builtin led.
  digitalWrite(ledBuiltIn, !digitalRead(ledBuiltIn));
}

void setup() {
  // Start the RuneWork taskmanager.
  initRuneWork();
  setRuneWorkPeriod(5);

  // We'll use the builtin led.
  pinMode(ledBuiltIn, OUTPUT);

  // Let's call the function myFunction every 500 ms.
  // This should make the builtin led flash with a frequency of 1 Hz.
  scheduleTask(myFunction, 500);
}

void loop() {
  // Do nothing special in the main loop.
  // You're free to do (almost) anything you want.
  delay(100);
}

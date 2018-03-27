/* RuneWork2_example_03.ino - Example Arduino skecth for the RuneWork2 library.
 * Copyright (C) 2018  Arne Baeyens
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


// Define the servo pin
#define servoPin 13

// Variable with the position of the servo.
// Useable range: 0..255, center position = 127 (for most servos).
unsigned char servoPosition = 127;

// The servo function, which is invoked every 20 ms to send the pulse to the servos.
void servoJob(void){
   digitalWrite(servoPin, HIGH);
   delayMicroseconds(1000 + servoPosition<<2);
   digitalWrite(servoPin, LOW);
}

void setup() {
  // Set servoPin as digital output
  pinMode(servoPin, OUTPUT);

  // Initiate the runework taskmanager.
  initRuneWork();
  // Set the period of the taskmanager to a divisor of 20 (e.g. 1, 2, 4, 5 or 10).
  setRuneWorkPeriod(5);
  
  // Ask to invoke the function servoJob regularly
  scheduleTask(servoJob, 20);
}

void loop() {
  // Let's drive the servo!
  servoPosition = 55;
  delay(500);
  servoPosition = 127;
  delay(500);
  servoPosition = 200;
  delay(1000);
}

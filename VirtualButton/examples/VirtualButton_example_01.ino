/* VirtualButton_example_01.ino - Example Arduino sketch for the VirtualButton library
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
 * Arne Baeyens - Contact: 2arne.baeyens@gmail.com
 *
 * Virtual button and pedal objects to emulate the physical characteristics of these devices.
 * Useful for converting the discrete signals of an infrared TV remote to a continuous value.
 */

// Also include the RuneWork2 library.
#include <VirtualButton.h>
#include <RuneWork2.h>

// We'll use the builtin led. Instead of referring to the mystic 'pin number 13', we use a define.
#define ledBuiltIn 13

// A new virtual button object.
// Please note that this is a global object.
VButton SW_Example_1;


void buttonsJob() {
  subtractTimeVButtons(20);
  subtractTimeVPedals(20);
}

void setup() {
  // Start the RuneWork taskmanager.
  initRuneWork();
  setRuneWorkPeriod(5);

  // The virtual button has to be registered.
  // Note the usage of the & in front of the name of the button..
  initVButton(&SW_Example_1);
  
  // The timeout time is the time the button stays high after pushing it.
  // Normally much shorter times are used (around 150 ms) but in this case it is for illustration purposes.
  SW_Example_1.timeOut = 1500;

  // The state of the buttons has to be refreshed regularly.
  // This RuneWork scheduled task will make sure that the function buttonsJob is called every 20 ms.
  scheduleTask(buttonsJob, 20);

  
  // We'll use the serial port.
  Serial.begin(9600);

  // And also the builtin led.
  pinMode(ledBuiltIn, OUTPUT);
}

void loop() {
  // Let's push the button (and also send over the serial port that it is pushed).
  SW_Example_1.push();
  Serial.println("Virtual button pushed");

  // The button doesn't go to high immediately, this takes some time (on average 10 ms as the current update frequency is 20 ms).
  // So we'll wait a bit.
  while(SW_Example_1.state == false){
    delay(1);
  }
  Serial.println("Button gone high");

  // The button has apparently gone high, so let's do this also with led.
  digitalWrite(ledBuiltIn, HIGH);


  // And wait until it goes low.
  while(SW_Example_1.state == true){
    delay(1);
  }
  Serial.println("Button gone low");
  
  // And change the led accordingly.
  digitalWrite(ledBuiltIn, LOW);

  // And repeat after 5 seconds.
  delay(5000);
}

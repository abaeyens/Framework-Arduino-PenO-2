/* RuneMotor.h - Header file of the RuneMotor library
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
 * Developed for a P&O-2 project
 * Arne Baeyens - Contact: 2arne.baeyens@gmail.com
 * 
 * Motor functions are inspired by the DwengoMotor libary for PIC microcontrollers.
 * 
 * 
 * Last edit:
 * 21 may 2017
 * Version 1.0 beta
 */

#ifndef RuneMotor_h
#define RuneMotor_h

#include <Arduino.h>

#define TRANSIENT_DELAY 20

#define motor1PWMPin 5    	// D4
#define motor1ReversePin 7
#define motor2PWMPin 6
#define motor2ReversePin 4

void initMotors();

void setSpeedMotor1(short speed);

void setSpeedMotor2(short speed);

void stopMotors();

short getSpeedMotor1(void);

short getSpeedMotor2(void);

#endif

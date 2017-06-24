/* RuneMotor.cp - Source file of the RuneMotor library
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

#include "RuneMotor.h"

short currentSpeed1;
short currentSpeed2;

void initMotors(){
	pinMode(motor1PWMPin, OUTPUT);
	pinMode(motor1ReversePin, OUTPUT);
	pinMode(motor2PWMPin, OUTPUT);
	pinMode(motor2ReversePin, OUTPUT);
	
	stopMotors();
}

void setSpeedMotor1(short speed){
  static bool prev_dir;
  bool dir;
  
  if(speed>255) speed = 255;
  if(speed<-255) speed = -255;
  
  dir = (speed > 0);

  currentSpeed1 = speed;
	
  if(speed==0){
    digitalWrite(motor1PWMPin,LOW);
    dir=true;
    // Switch off the relay as these consume a lot of current.
    digitalWrite(motor1ReversePin,!dir);
  }else{
    if(dir!=prev_dir){
      digitalWrite(motor1PWMPin,LOW);
      digitalWrite(motor1ReversePin,!dir);
      delay(TRANSIENT_DELAY);
      prev_dir=dir;
    }
    if(dir){    // Forward.
      digitalWrite(motor1ReversePin,LOW);
      analogWrite(motor1PWMPin,speed);
    }else{      // Reverse.
      digitalWrite(motor1ReversePin,HIGH);
      analogWrite(motor1PWMPin,-speed);
    }
  }
}

void setSpeedMotor2(short speed){
  static bool prev_dir;
  bool dir;
  
  if(speed>255) speed = 255;
  if(speed<-255) speed = -255;
  
  dir = (speed > 0);

  currentSpeed2 = speed;
  
  if(speed==0){
    digitalWrite(motor2PWMPin,LOW);
    dir=true;
    digitalWrite(motor2ReversePin,!dir);
  }else{
    if(dir!=prev_dir){
      digitalWrite(motor2PWMPin,LOW);
      digitalWrite(motor2ReversePin,!dir);
      delay(TRANSIENT_DELAY);
      prev_dir=dir;
    }
    if(dir){    // Forward.
      digitalWrite(motor2ReversePin,LOW);
      analogWrite(motor2PWMPin,speed);
    }else{      // Reverse.
      digitalWrite(motor2ReversePin,HIGH);
      analogWrite(motor2PWMPin,-speed);
    }
  }
}

void stopMotors(){
  setSpeedMotor1(0);
  setSpeedMotor2(0);
}

short getSpeedMotor1(void){
  return currentSpeed1;
}

short getSpeedMotor2(void){
  return currentSpeed2;
}

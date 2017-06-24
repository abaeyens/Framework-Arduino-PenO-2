/* VirtualButton.h - Header file of the VirtualButton library
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
 * Virtual button and pedal objects to emulate the physical characteristics of these devices.
 * Useful for converting the discrete signals of an infrared TV remote to a continuous value.
 * 
 * 
 * Last edit:
 * 21 may 2017
 * Version 1.0 beta
 */

#ifndef VirtualButton_h
#define VirtualButton_h

#include <Arduino.h>
#include <RuneWork2.h>

#define NB_BUTTONS 15
#define NB_PEDALS 6

class VButton{  
  public:
    char state;
    bool getted;
    bool active;
    int timeOut;
    int timeOutCounter;
    
    void set( char set_state );
    
    void setTimeOut( int timeOut_local );
    
    void update();
    
    void push();
    
    void release();
    
    bool get();
};

class VPedal{
  public:
	char state;
    bool active;
    int timeOut;
    int timeOutCounter;
    
	int timeUp;	
	int timeDown;
	
	unsigned char maximum_position;
	unsigned char position;
	
	void set( char set_state );
	
	void setTimeOut( int timeOut_local );
	
	void update();
    
    void push();
    
    void release();
    
    void pull();
};

void initVButton( VButton *ptr_button_object );
void initVPedal( VPedal *ptr_pedal_object );

void subtractTimeVButtons( byte elapsed_time );
void subtractTimeVPedals( unsigned char elapsed_time );

#endif

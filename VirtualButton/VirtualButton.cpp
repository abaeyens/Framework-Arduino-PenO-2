/* VirtualButton.cpp - Source file of the VirtualButton library
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
 
#include "VirtualButton.h"
#include "RuneWork2.h"

byte nb_buttons_used=0;
byte nb_pedals_used=0;

VButton *button_ptr[NB_BUTTONS];
VPedal *pedal_ptr[NB_PEDALS];

// VButton functions
void VButton::set( char set_state )
{
  state = !!set_state;
}

void VButton::setTimeOut( int timeOut_local )
{
  timeOut = timeOut_local;
}

void VButton::update()
{
  state=!!timeOutCounter;
  if(state==false){
	  getted = false;
  }
}

void VButton::push()
{
  if(state==false){
	  playFreq(1776, 512);
	  setTask(muteFreq, 50);
  }
  state=true;
  timeOutCounter = timeOut;
}

void VButton::release()
{
  state=false;
  getted=false;
  timeOutCounter = 0;
}

bool VButton::get()
{
	if(getted==false && state==true){
		getted = true;
		return true;
	}
	return false;
}


void VPedal::set( char set_state )
{
  state = !!set_state;
}

void VPedal::setTimeOut( int timeOut_local )
{
  timeOut = timeOut_local;
}

void VPedal::update()
{
  state=!!timeOutCounter;
}

void VPedal::push(){
  /*if(state==false){
	  playFreq(1332, 512);
	  setTask(muteFreq, 50);
  }*/
  state=true;
  timeOutCounter = timeOut;
}

void VPedal::release()
{
  state=false;
}

void VPedal::pull()
{
  state=false;
  timeOutCounter = 0;
  position = 0;
}


void initVButton( VButton *ptr_button_object ){
	button_ptr[nb_buttons_used]=ptr_button_object;
	
	button_ptr[nb_buttons_used]->active=true;
    button_ptr[nb_buttons_used]->state=false;
    button_ptr[nb_buttons_used]->getted=false;
    button_ptr[nb_buttons_used]->timeOut=500;
    button_ptr[nb_buttons_used]->update();
    
    nb_buttons_used+=1;
    
    Serial.print("  VButtons used: ");
    Serial.println(nb_buttons_used);
}

void initVPedal( VPedal *ptr_pedal_object ){
	pedal_ptr[nb_pedals_used]=ptr_pedal_object;
	
	pedal_ptr[nb_pedals_used]->active=true;
	pedal_ptr[nb_pedals_used]->state=false;
	pedal_ptr[nb_pedals_used]->timeOut=500;
    pedal_ptr[nb_pedals_used]->timeUp = 1000;
    pedal_ptr[nb_pedals_used]->timeDown = 1000;
    pedal_ptr[nb_pedals_used]->maximum_position = 255;
    pedal_ptr[nb_pedals_used]->position = 0;
    pedal_ptr[nb_pedals_used]->update();
    
    nb_pedals_used+=1;
    
    Serial.print("  VPedals used:  ");
    Serial.println(nb_pedals_used);
}

void subtractTimeVButtons( byte elapsed_time ){
  char j;
  
  for(j=0;j<NB_BUTTONS;j++){
	if(button_ptr[j]->active==true){
		
	  if(button_ptr[j]->timeOutCounter>elapsed_time){
	    button_ptr[j]->timeOutCounter-=elapsed_time;
	    button_ptr[j]->update();
	  } else if(button_ptr[j]->timeOutCounter>0){
	    button_ptr[j]->timeOutCounter=0;
	    button_ptr[j]->update();
	  }

	}
  }
}

void subtractTimeVPedals( unsigned char elapsed_time ){
  char j;
  unsigned char var;
  
  for(j=0;j<NB_PEDALS;j++){
	if(pedal_ptr[j]->active==true){
		
	  if(pedal_ptr[j]->timeOutCounter>elapsed_time){
	    pedal_ptr[j]->timeOutCounter-=elapsed_time;
	    pedal_ptr[j]->update();
	  } else if(pedal_ptr[j]->timeOutCounter>0){
	    pedal_ptr[j]->timeOutCounter=0;
	    pedal_ptr[j]->update();
	  }
	  
	  if(pedal_ptr[j]->state==true){
		  var = elapsed_time*256/pedal_ptr[j]->timeUp;
		  if(pedal_ptr[j]->position<(pedal_ptr[j]->maximum_position-var)){
			  pedal_ptr[j]->position+=var;
		  } else {
			  pedal_ptr[j]->position=pedal_ptr[j]->maximum_position;
		  }
	  } else if (pedal_ptr[j]->position!=0){
		  var = elapsed_time*256/pedal_ptr[j]->timeDown;
		  if(pedal_ptr[j]->position>var){
			  pedal_ptr[j]->position-=var;
		  } else {
			  pedal_ptr[j]->position=0;
		  }
	  }
	  
	}
  }
}

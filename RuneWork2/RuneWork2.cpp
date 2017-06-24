/* RuneWork2.cpp - Source file of the RuneWork library
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
 * Sound functions are inspired by the DwengoSound libary for PIC microcontrollers.
 * 
 * 
 * Last edit:
 * 21 may 2017
 * Version 1.0 beta
 */
 
#include "Arduino.h"
#include "RuneWork2.h"
#include "TimerOne.h"

const byte DEFAULT_POSTSCALER = 10;

// Variables used by the song player.
int noteCount=0;      // Position of note being played in song.
note* currentSong;    // Holds a pointer to the song data (note array) of the current song.
volatile bool songFlag=false;  // Indicates whether music should be playing or not.
int soundDuty=512;
// Speed to play the the music in Beats Per Minute.
volatile byte BPM=120;


// Variables for task manager.
unsigned char postScaler=DEFAULT_POSTSCALER;

void (*task_buffer_ptr[TASKS_BUFFER_LENGTH])(void);
int task_buffer_time[TASKS_BUFFER_LENGTH];

// Variables for the scheduler.
void (*task_schedule_ptr[TASKS_SCHEDULE_LENGTH])(void);
int task_schedule_time[TASKS_SCHEDULE_LENGTH];
char task_schedule_execs[TASKS_SCHEDULE_LENGTH];


void setRuneWorkPeriod( byte RuneWork_period ){
	setTimer1Period_mine( (long)1000*RuneWork_period );
}

// To start the RuneWork jobmanager.
void initRuneWork(){
  char j;

  Timer1.initialize(1000*DEFAULT_POSTSCALER);
  Timer1.attachInterrupt(interruptCallback,1000*DEFAULT_POSTSCALER);
  
  for(j=0;j<TASKS_BUFFER_LENGTH;j++){
    task_buffer_time[j]=-1;
  }
  for(j=0;j<TASKS_SCHEDULE_LENGTH;j++){
    task_schedule_time[j]=-1;
    task_schedule_execs[j]=-1;
  } 
}
// The interruptCallback function. This function is called every time Timer1 rolls over.
// It manages all the current jobs. It takes care of the timing and calls a job function when necessary.
void interruptCallback()
{
  char i, j;
  
  interrupts();
  
  // For every job left, calculate the time (in ms) until they have to be executed.
  for(j=0;j<TASKS_BUFFER_LENGTH;j++){
    if(task_buffer_time[j]>postScaler){
      task_buffer_time[j]-=postScaler;
    } else if(task_buffer_time[j]>0){
      task_buffer_time[j]=0;
    }
  }
  // For each job, see if time has come to call it.
  for(j=0;j<TASKS_BUFFER_LENGTH;j++){
	if(task_buffer_time[j]==0){
		task_buffer_ptr[j]();
		// If a task is finished but scheduled, reload it from the schedule.
		for(i=0;i<TASKS_SCHEDULE_LENGTH;i++){
			if (task_schedule_execs[i]==0 && task_schedule_ptr[i]==task_buffer_ptr[j]){
				task_buffer_time[j] = task_schedule_time[i];
				break;
			} else if (task_schedule_execs[i]>1 && task_schedule_ptr[i]==task_buffer_ptr[j]){
				task_buffer_time[j] = task_schedule_time[i];
				if (task_schedule_execs[i]>2){
					task_schedule_execs[i]-=1;
				}
				else{
					task_schedule_execs[i]=-1;
					task_schedule_ptr[i]=0;
				}
				break;
			}
		}
	}
	// If the job's timeCount is still zero, disable it by setting a negative time value.
	if(task_buffer_time[j]==0){
      task_buffer_time[j]=-1;
      task_buffer_ptr[j]=0;
    }
  }
}

// Function to create a single task. It will be called once in the time task_time.
void setTask( void(*function_ptr)(void), int task_time ){
	char i;
	for(i=0; i<TASKS_BUFFER_LENGTH; i++){
		if(task_buffer_time[i]==-1){
			task_buffer_ptr[i]=function_ptr;
			task_buffer_time[i]=task_time;
			break;
		}
	}
}
// Function to create a scheduled task.
// It will be called times_to_exec times or indefinetly if not specified (by default).
// task_time is the time between calls of the function.
void scheduleTask( void(*function_ptr)(void), int task_time, char times_to_exec ){
	char i;
	setTask(function_ptr, task_time);
	for(i=0; i<TASKS_SCHEDULE_LENGTH; i++){
		if(task_schedule_execs[i]==-1){
			task_schedule_ptr[i] = function_ptr;
			task_schedule_time[i] = task_time;
			task_schedule_execs[i] = times_to_exec;
			break;
		}
	}
}

void removeTask( void(*function_ptr)(void) ){
	char i;
	for(i=0; i<TASKS_BUFFER_LENGTH; i++){
		if(task_buffer_ptr[i]==function_ptr){
			task_buffer_time[i] = -1;
			task_buffer_ptr[i] = 0;
		}
	}
}

void removeScheduleTask( void(*function_ptr)(void) ){
	char j;
	for(j=0; j<TASKS_SCHEDULE_LENGTH; j++){
		if(task_schedule_ptr[j]==function_ptr){
			task_schedule_execs[j] = -1;
			task_schedule_ptr[j] = 0;
		}
	}
}


bool isScheduleTask( void(*function_ptr)(void) ){
	char j;
	for(j=0; j<TASKS_SCHEDULE_LENGTH; j++){
		if(task_schedule_ptr[j]==function_ptr && task_schedule_execs[j]!=-1){
			return true;
		}
	}
	return false;
}
	
byte nbTasks(void){
	char i;
	byte counter = TASKS_BUFFER_LENGTH;
	for(i=0; i<TASKS_BUFFER_LENGTH; i++){
		if(task_buffer_time[i]==-1){
			counter--;
		}
	}
	return counter;
}

byte nbScheduleTasks(void){
	char j;
	byte counter = TASKS_SCHEDULE_LENGTH;
	for(j=0; j<TASKS_SCHEDULE_LENGTH; j++){
		if(task_schedule_ptr[j]==0){
			counter--;
		}
	}
	return counter;
}

byte getTasksBufferLength(void){
	return TASKS_BUFFER_LENGTH;
}

byte getScheduleBufferLength(void){
	return TASKS_SCHEDULE_LENGTH;
}

// Small function to set Timer1 to the desired period (in us) and to set the postScaler time (in ms).
// The postScaler value is used by the jobmanager.
void setTimer1Period_mine(long timer_period){		// Period in us.
	Timer1.setPeriod(timer_period);
	postScaler=1.00*timer_period/1000;
}

// Initiate the sound functions.
// If using sound, this currently has to be done BEFORE assigning any other functions.
void initSound(){
	//Serial.println("initSound started\n");
	//runeJob_ptr[0].reference_nb = nb_jobs_used;
	setTask(musicJob, 600);
	pinMode(soundPin, OUTPUT);
	
	//Serial.println("initSound successful\n");
}

// The songFlag bool is not available in the main program.
// Thus, a small function is used to read the value of this variable in the main program.
// It is used to see whether a song is (still or already) playing.
bool getSongFlag(){
  return songFlag;
}

// job0: Music player
// This functions is called for every new note (note: rests are also notes).
// Depending on the note, an appropriate action is executed.
// At the end of the song, the frequency of Timer1 is reset to 1000 Hz (as default) to make job timings more consistent.
void musicJob(){
  int frequency;
  
  if(songFlag){
    frequency=noteFrequency(currentSong[noteCount]);
  
    if(frequency==0){   // Play a rest.
      muteFreq();
      setTask(musicJob, noteDuration(currentSong[noteCount]));
      noteCount++;
    }
    else if(frequency==EOS){    // End of song, thus stop playing and reset Timer1.
      muteFreq();
      noteCount=0;
      songFlag=false;
      setTask(musicJob, 100);    // Check in 100 ms whether a song has to be played.
    }
    else{   // Play the note.
      playFreq(frequency, soundDuty);
      setTask(musicJob, noteDuration(currentSong[noteCount]));
      noteCount++;
    }
  }
  else{
	setTask(musicJob, 100);    // Check every 100 ms whether a song has to be played.
  }
}


// Start playing a tone.
void playFreq(int freq, int duty){
  tone(soundPin, freq);
}

// Stop playing a tone.
void muteFreq(){
  //freqPlayFlag=false;
  noTone(soundPin);
  digitalWrite(soundPin,LOW);
}

// Function to start playing a song.
void startSong(note* Song, unsigned int bpm){
  BPM=bpm;
  soundDuty=512;
  currentSong = Song;
  noteCount = 0;
  songFlag=true;
}

void stopSong(){
  muteFreq();
  noteCount=0;
  songFlag=false;
  removeTask(musicJob);
  setTask(musicJob, 100);    // Check in 100 ms whether a song has to be played.
}


// Return the frequency of a note.
unsigned int noteFrequency(note Note){
    int freq;
    switch (Note.pitch){
        case 'C': freq= 4186;
                  break;
        case 'd': freq= 4434;
                  break;
        case 'D': freq= 4698;
                  break;
        case 'e': freq= 4978;
                  break;
        case 'E': freq= 5274;
                  break;
        case 'F': freq= 5587;
                  break;
        case 'g': freq= 5919;
                  break;
        case 'G': freq= 6271;
                  break;
        case 'a': freq= 6644;
                  break;
        case 'A': freq= 7040;
                  break;
        case 'b': freq= 7458;
                  break;
        case 'B': freq= 7902;
                  break;
        case 'r': return 0;
                  break;
        case 'Q': return EOS;
                  break;
        default: return EOS;
    }
    return freq/pow(2,4-Note.octave);
}
// Return the duration in ms of a note.
int noteDuration(note Note){
  return 5000/BPM*Note.duration;
}

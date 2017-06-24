/* RuneWork2.h - Header file of the RuneWork library
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

#ifndef RuneWork2_h
#define RuneWork2_h

#include <Arduino.h>

// Defines for music note durations.
#define H 24  // half 2/4
#define Q 12  // quarter 1/4 
#define E 6   // eighth 1/8
#define S 3   // sixteenth 1/16
#define W 48  // whole 4/4
// The T stands for triplets.
#define HT 16  // half 2/4 in triplet
#define QT 8   // quarter 1/4 in triplet
#define ET 4   // eighth 1/8 in triplet
#define ST 2   // sixteenth 1/16 in triplet
#define WT 36  // whole 4/4 in triplet

// EOS is used to signal the End Of a Song.
#define EOS 1

// The pin for the soundoutput. This must be a pin that has PWM of Timer2.
#define soundPin 3

#define TASKS_BUFFER_LENGTH 16
#define TASKS_SCHEDULE_LENGTH 9

// A note structure to make storing songs more simple.
typedef struct{
    char pitch;
    signed char octave;
    unsigned char duration;
} note;

void setRuneWorkPeriod( byte RuneWork_period );

void setTask( void(*function_ptr)(void), int task_time );
void scheduleTask( void(*function_ptr)(void), int task_time, char times_to_exec=0 );

void removeTask( void(*function_ptr)(void) );
void removeScheduleTask( void(*function_ptr)(void) );

bool isScheduleTask( void(*function_ptr)(void) );

byte nbTasks(void);
byte nbScheduleTasks(void);

byte getTasksBufferLength(void);
byte getScheduleBufferLength(void);

void initRuneWork();
void interruptCallback();

void setTimer1Period_mine(long timer_period);

void initSound();

bool getSongFlag();

void musicJob();

void playFreq(int freq, int duty);
void muteFreq();
void startSong(note* Song, unsigned int bpm);
void stopSong();
unsigned int noteFrequency(note Note);
int noteDuration(note Note);

#endif

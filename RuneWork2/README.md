# RuneWork2
The workings of the RuneWork2 taskmanager are quite complex - it involves function pointers - so I suggest that you just learn to use it and post an issue here on GitHub if something doesn't work as expected. I've made two example Arduino sketches but most of the functionality of the RuneWork2 library is also described here.

## Examples

- RuneWork2_example_01.ino
   Basic usage of the task manager.  

- RuneWork2_example_02.ino
   Basic usage of the sound functions (including two demo songs). The RuneWork2 header file contains some information about the used music format.  

## Usage
### Taskmanager
Initialising the RuneWork2 taskmanager should be done once in the `setup()`. In addition to the init command the period of the taskmanager also has to be defined. The period influences the time accuracy at which tasks will be executed. For example, if you choose a period of 50 ms, the average absolute time difference between the asked and the actual time a task is executed is around 25 ms. In this code example below a period of 5 ms is used. The code of the RuneWork2 taskmanager runs quickly enough to use a period of 1 ms. Please note that the period must be an integer number in the range of 1 to 256 (e.g. excluding 256). It's also best that the period is longer than the time necessary to execute the tasks/functions, otherwise weird things may happen. The sound stuff should also be initialised before use. However if you aren't going to use the sound functions this of course isn't needed.
```cpp
initRuneWork();        // Initiate the RuneWork taskmanager.
setRuneWorkPeriod(5);  // Use a period of 5 ms for the RuneWork taskmanager.
initSound();           // Initiate the sound stuff (not necessary if you're not using the sound functions).
```
You can change the RuneWorkPeriod while in the midst of your program if you need to.

In the following examples we'll use an example function `myFunction()`.

Say we want to call our example function a single time after 750 ms. We can do this very simply with:
```cpp
setTask(myFunction, 750);
```

In can be useful to call a function multiple times. We call this 'scheduling'.
```cpp
scheduleTask(myFunction, 750, 10);     // Call the function myFunction 10 times.
scheduleTask(myFunction, 750, 0);      // Call the function myFunction until the next blue moon.
```

This can become very funny, but luckily we can also remove single tasks and scheduled tasks.
```cpp
removeTask(myFunction);          // Remove a single task.
removeScheduleTask(myFunction);  // Remove a scheduled task.
```

The buffers containing the single tasks and the scheduled tasks are of fixed length. To change the length of these buffers, change the numbers in the `RuneWork2.h` file, they are named `TASKS_BUFFER_LENGTH` and `TASKS_SCHEDULE_LENGTH`. By default the respective lengths are 16 and 9. Due to the O(a\*b) complexity of the RuneWork2 taskmanager (a and b being the respective lengths of the buffers) it's best to keep the buffer lengths as short as possible. These two lengths can be obtained using the following two functions:
```cpp
getTasksBufferLength();
getScheduleBufferLength();
```

There are also two functions to read the current usage of the buffers. They return the number of tasks that are currently in the buffer.
```cpp
nbTasks();
nbScheduleTasks();
```

### Sound
The RuneWork2 sound functions do support the use of triplets. While musical pieces rarely contain more than a few triplets, they give parts of the piece a very characteristic rithm and thus are very important rithmical figures. That said, most simple sound libraries don't support triplets, but this one does. A famous use of triplets is in the main title of Star Wars. The used music notation and memory structures are inspired by those used in the Dwengo library.

Let's start with the music notation. Here's an example:
```cpp
const note Song_example [] = {{'C', 0, Q}, {'E', 0, Q}, {'G', 0, H}, {'Q', 0, 0}};
```
The code above saves a short song of three notes to the variable `Song_example`. Please note that this variable is an array of note structures and that `const` is used to indicate that this is a unchangeable variable. The last note should always be `{'Q', 0, 0}`. The tempo the song will be played has to specified when starting a song.

A single note structure consists of three variables: a character representing the set of pitches, an integer number to denote the octave and one or two letters to specify the length of that particular note. The letters are the standard music letters. For Europeans, an A is la, B is a si, C is a do, ... In the used notation lowercase letters are used for flat notes. For rests, a 'Q' is used.

It's not possible to use sharp notes (for example, F♯). Instead the corresponding flat should be used, in the example this means using a G♭. Flat pitches are written in lowercase, so for this example this will give a g.

For the length of the notes, all possible lengths are shown below:
```cpp
// Defines for music note durations.
H    // half 2/4
Q    // quarter 1/4 
E    // eighth 1/8
S    // sixteenth 1/16
W    // whole 4/4
// The T stands for triplets.
HT   // half 2/4 in triplet
QT   // quarter 1/4 in triplet
ET   // eighth 1/8 in triplet
ST   // sixteenth 1/16 in triplet
WT   // whole 4/4 in triplet
```

Let's now analyse the example `Song_example`. Without the last note - which isn't played and just indicates the end of the song - there are three notes. A C, an E and a G. All are played at octave 0, e.g. the 'normal' tone height. The first and second note have a duration of a quarter note (1/4) and the last note is an eighth note (1/8).

Starting a song is easy. Let's start the example song and play it with a tempo of 120 beats per minute.
```cpp
startSong(Song_example, 120);
```
Please note that the code following the above comment is executed immediately afterwards. In short, you can do other things in your code while the song is playing.

To see whether a song is being played or not the `getSongFlag()` function can be used. It returns a bool which is true if a song is playing, otherwise it return false.

While playing songs is nice, sometimes it's only necessary to produce a single tone of a fixed frequency. The following example demonstrates the use of the `playFreq()` and `muteFreq()` functions.
```cpp
playFreq(1760, 512);    // Start playing a tone with a frequency of 1760 Hz.
delay(1000);            // Wait a bit.
muteFreq();             // Stop playing the tone.
```

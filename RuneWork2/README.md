# RuneWork2
The workings of the RuneWork2 taskmanager are quite complex - it involves function pointers - so I suggest that you just learn to use it and post an issue here on GitHub if something doesn't work as expected. I've made two example Arduino sketches but most of the functionality of the RuneWork2 library is also described here.

## Examples

- RuneWork2_example_01.ino
   Basic usage of the task manager.  

- RuneWork2_example_02.ino
   Basic usage of the sound functions (including two demo songs). The RuneWork2 header file contains some information about the used music format.  

## Usage
### Taskmanager
Initialising the RuneWork2 taskmanager should be done once in the `setup()`. In addition to the init command the period of the taskmanager also has to be defined. The period influences the time accuracy at which tasks will be executed. For example, if you choose a period of 50 ms, the average absolute time difference between the asked and the actual time a task is executed is around 25 ms. In this code example below a period of 5 ms is used. The code of the RuneWork2 taskmanager runs quickly enough to use a period of 1 ms. Please note that the period must be an integer number in the range of 1 to 256 (e.g. excluding 256). The sound stuff should also be initialised before use. However if you aren't going to use the sound functions this of course isn't necessary.
```cpp
initRuneWork();        // Initiate the RuneWork taskmanager.
setRuneWorkPeriod(5);  // Use a period of 5 ms for the RuneWork taskmanager.
initSound();           // Initiate the sound stuff (not necessary if you're not using the sound functions).
```



### Sound
The RuneWork2 sound functions do support the use of triplets. While musical pieces rarely contain more than a few triplets, they give parts of the piece a very characteristic rithm and thus are very important rithmical figures. That said, most simple sound libraries don't support triplets, but this one does. A famous use of triplets is in the main title of Star Wars. The used music notation and memory structures are inspired by those used in the Dwengo library.

Let's start with the music notation. Here's an example:
```cpp
const note Return [] = {{'C', 0, Q}, {'E', 0, Q}, {'G', 0, H}, {'Q', 0, 0}};
```
The code above saves a short song of three notes to the variable `Return`. Please note that this variable is an array of note structures and that `const` is used to indicate that this is a unchangeable variable. The last note should always be `{'Q', 0, 0}`.

A single note structure consists of three variables: a character representing the set of pitches, an integer number to denote the octave and one or two letters to specify the length of that particular note. Let's analyse the example



It's not possible to use sharp notes (for example, F♯). Instead the corresponding flat should be used, in the example this means using a G♭. Flat pitches are written in lowercase, so for this example this will give a g.

```cpp
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
```

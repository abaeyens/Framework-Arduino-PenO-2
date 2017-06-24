/* RuneWork2_example_02.ino - Example Arduino sketch for the RuneWork library
 * The two songs are arrangements from the original works of John Williams and Europe.
 * 
 * Arne Baeyens - Contact: 2arne.baeyens@gmail.com
 * 
 * Sound functions are inspired by the DwengoSound libary for PIC microcontrollers.
 * 
 */

#include <RuneWork2.h>

// Two songs...
// Imperial March (John Williams)
// This is fan art.
const note StarWars [] = {{'G', 0, E + S}, {'r', 0, S}, {'G', 0, E + S}, {'r', 0, S}, {'G', 0, E + S}, {'r', 0, S}, {'e', 0, E + S}, {'b', 0, S},
  {'G', 0, E + S}, {'r', 0, S}, {'e', 0, E + S}, {'b', 0, S}, {'G', 0, Q + E + S}, {'r', 0, S},
  {'D', 1, E + S}, {'r', 0, S}, {'D', 1, E + S}, {'r', 0, S}, {'D', 1, E + S}, {'r', 0, S}, {'e', 1, E + S}, {'b', 0, S},

  {'g', 0, E + S}, {'r', 0, S}, {'e', 0, E + S}, {'b', 0, S}, {'G', 0, Q + E + S}, {'r', 0, S},
  {'G', 1, E + S}, {'r', 0, S}, {'G', 0, E}, {'r', 0, S}, {'G', 0, S}, {'G', 1, E + S}, {'r', 0, S}, {'g', 1, E + S}, {'F', 1, S},
  {'E', 1, S}, {'e', 1, S}, {'E', 1, E}, {'r', 0, E}, {'a', 0, E}, {'d', 1, Q}, {'C', 1, E + S}, {'B', 0, S},

  {'b', 0, S}, {'A', 0, S}, {'b', 0, E}, {'r', 0, E}, {'e', 0, E}, {'G', 0, E + S}, {'r', 0, S}, {'e', 0, E + S}, {'G', 0, S},
  {'b', 0, E + S}, {'r', 0, S}, {'G', 0, E + S}, {'G', 0, S}, {'D', 1, Q + E + S}, {'r', 0, S},
  {'G', 1, E + S}, {'r', 0, S}, {'G', 0, E + S}, {'G', 0, S}, {'G', 1, E + S}, {'r', 0, S}, {'g', 1, E + S}, {'F', 1, S},

  {'E', 1, S}, {'e', 1, S}, {'E', 1, E}, {'r', 0, E}, {'a', 0, E}, {'d', 1, Q}, {'C', 1, E + S}, {'B', 0, S},
  {'b', 0, S}, {'A', 0, S}, {'b', 0, E}, {'r', 0, E}, {'e', 0, E}, {'G', 0, Q}, {'e', 0, E + S}, {'b', 0, S},
  {'G', 0, Q}, {'e', 0, E + S}, {'b', 0, S}, {'G', 0, Q + E + S}, {'Q', 0, 0}
};

// Final Countdown (Europe)
// This is also fan art.
const note Final [] = {{'A', -1, Q}, {'r', 0, S}, {'d', 1, S}, {'B', 0, S}, {'d', 1, Q}, {'g', 0, Q},
  {'D', 1, Q}, {'r', 0, S}, {'D', 1, S}, {'d', 1, S}, {'D', 1, E}, {'d', 1, E}, {'B', 0, Q},
  {'D', 0, Q}, {'r', 0, S}, {'D', 1, S}, {'d', 1, S}, {'D', 1, Q}, {'g', 0, Q},
  {'a', 0, Q}, {'r', 0, S}, {'B', 0, S}, {'A', 0, S}, {'B', 0, E}, {'A', 0, E}, {'a', 0, E}, {'A', 0, S}, {'r', 0, S},


  {'A', 0, Q}, {'r', 0, S}, {'d', 1, S}, {'B', 0, S}, {'d', 1, Q}, {'g', 0, Q},
  {'D', 1, Q}, {'r', 0, S}, {'D', 1, S}, {'d', 1, S}, {'D', 1, E}, {'d', 1, E}, {'B', 0, Q},
  {'D', 0, Q}, {'r', 0, S}, {'D', 1, S}, {'d', 1, S}, {'D', 1, Q}, {'g', 0, Q},
  {'a', 0, Q}, {'r', 0, S}, {'B', 0, S}, {'A', 0, S}, {'B', 0, E}, {'A', 0, E}, {'a', 0, E}, {'A', 0, S}, {'r', 0, S},

  {'A', 0, Q + E}, {'a', 0, S}, {'A', 0, S}, {'B', 0, Q + E}, {'A', 0, S}, {'B', 0, S},
  {'d', 1, E}, {'B', 0, E}, {'A', 0, E}, {'a', 0, E}, {'g', 0, Q}, {'D', 1, Q},
  {'d', 1, H + E}, {'r', 0, E}, {'d', 1, S}, {'D', 1, S}, {'d', 1, S}, {'B', 0, S},
  {'d', 1, H + Q + E}, {'r', 0, E},
  {'d', 0, W}, {'d', 0, Q + E}, {'r', 0, E}, {'g', 0, Q}, {'E', 0, Q},
  {'d', 0, Q}, {'A', 0, Q}, {'a', 0, Q}, {'E', 0, Q}, {'g', 0, W}, {'Q', 0, 0}
};

void setup() {
  // Initiate the RuneWork task manager.
  initRuneWork();
  setRuneWorkPeriod(5);
  
  // Initiate the sound stuff of the RuneWork taskmanager.
  // The default sound pin is pin 3.
  // If you want to drive a speaker it's best to use a transistor as a switch to the speaker
  // as the Arduino can't output much current.
  // Not using a transistor may damage your Arduino.
  initSound();
}

void loop() {
  // Let's start a song!
  startSong(StarWars, 120);

  // While the song is playing, other things can be done. Now we don't wan't to do much
  // so we'll just wait until this song is finished.
  while(getSongFlag() == true){
    delay(50);
  }

  delay(1000);


  // Start the next song.
  startSong(Final, 118);

  while(getSongFlag() == true){
    delay(50);
  }

  delay(1000);
}

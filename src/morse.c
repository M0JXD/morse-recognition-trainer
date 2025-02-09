#include "morse.h"

// Plays the given letter
void PlayMorse(int letter) {
    static int letterPlaying = 41;
    static int onPart = 0;

    // 41 is passed to signal we keep playing if something is playing
    // If both are 41 then nothing is playing right now.
    if (letter == 41 && letterPlaying == 41) {
        return;
    }

    // We have a new letter to start playing
    if (letterPlaying == 41 && letter < 40) {
        // if 
    }

    // Keep playing the current letter
    if (letterPlaying < 41) {

    }
 
}

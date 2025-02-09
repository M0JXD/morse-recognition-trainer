#include "raylib.h"
#include "morse.h"

extern Sound dot;
extern Sound dash;

// Plays the given letter
void PlayMorse(int letter) {
    
    static int letterPlaying = 41;
    static int onPart = 0;

    // 41 is passed to allow us to keep playing if something is playing
    // If both are 41, then nothing is playing right now.
    if (letter == 41 && letterPlaying == 41) {
        return;
    }

    // We have a new letter to start playing
    if (letterPlaying == 41 && letter < 40) {
        onPart = 0;
        PlaySound(dash);
        // if 
    }

    // We've been asked to play a new letter but the previous one is still playing
    if (letter < 40 && letterPlaying < 40) {
        // TODO: Handle this situation
    }

    // Keep playing the current letter
    if (letterPlaying < 41) {
        switch (onPart) {
            case 0:
                onPart = 1;
            case 1:
                onPart = 2;
        }
    }
}

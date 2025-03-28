#include "raylib.h"
#include "stdio.h"  // sprintf

#include "game_save.h"
#include "letters.h"
#include "morse.h"

extern Sound dot;
extern Sound dash;
extern SaveState gameSave;

void LoadMorseSounds(void) {
    static int unload = 0;
    if(unload) {
        UnloadSound(dot);
        UnloadSound(dash);
    }
    char dotPath[32], dashPath[34];
#if defined(PLATFORM_ANDROID)
    sprintf(dotPath, "%dWPM_%dHZ_DOT.wav", gameSave.WPM, gameSave.tone);
    sprintf(dashPath, "%dWPM_%dHZ_DASH.wav", gameSave.WPM, gameSave.tone);
#else
    sprintf(dotPath, "assets/%dWPM_%dHZ_DOT.wav", gameSave.WPM, gameSave.tone);
    sprintf(dashPath, "assets/%dWPM_%dHZ_DASH.wav", gameSave.WPM, gameSave.tone);
#endif
    // printf("Loading tones for %dWPM %dHz.\n", gameSave.WPM, gameSave.tone);
    dot = LoadSound(dotPath);
    dash = LoadSound(dashPath);
    unload = 1;
}

void GetMorseText(int letter, char* text) {
    static int currentLetter = NOT_LETTER;

    if (letter < 40) {
        currentLetter = letter;
    }

    // We're not playing a sound anymore
    if (letter == (NOT_LETTER + 1)) {
        currentLetter = NOT_LETTER;
    }

    if (letter == NOT_LETTER && currentLetter < 40 && text != NULL) {
        sprintf(text, "Currently playing '%s' ...", lettersQwerty[currentLetter]);
    }
}

void PlayMorse(int letter) {
    
    static int letterPlaying = NOT_LETTER;
    static int onPart = 0;

    // NOT_LETTER is passed to allow us to keep playing if something is playing
    // If both are NOT_LETTER, then nothing is playing right now, promptly return
    if (letter == NOT_LETTER && letterPlaying == NOT_LETTER) return;

    // We have a new letter to start playing
    if (letterPlaying == NOT_LETTER && letter < 40) {
        letterPlaying = letter;
        if (firstCodePart[letterPlaying] == '.') PlaySound(dot);
        else PlaySound(dash);
        GetMorseText(letterPlaying, NULL);
        onPart = 1;
        return;
    }

    // Keep playing the current letter
    if (letterPlaying < NOT_LETTER && letter == NOT_LETTER) {
        // If a sound is current playing, just return.
        if (IsSoundPlaying(dot) || IsSoundPlaying(dash)) return;

        // If we reach here we're ready to start playing the next part.
        switch (onPart) {
            case 1:
                if (secondCodePart[letterPlaying] == '.') PlaySound(dot);
                else if (secondCodePart[letterPlaying] == '-') PlaySound(dash);
                else {  // Must be null, we're done...
                    onPart = 0;
                    letterPlaying = NOT_LETTER;
                    GetMorseText((NOT_LETTER + 1), NULL);
                    return;
                }
                onPart = 2;
                break;

            case 2:
                if (thirdCodePart[letterPlaying] == '.') PlaySound(dot);
                else if (thirdCodePart[letterPlaying] == '-') PlaySound(dash);
                else {  // Must be null, we're done...
                    onPart = 0;
                    letterPlaying = NOT_LETTER;
                    GetMorseText((NOT_LETTER + 1), NULL);
                    return;
                }
                onPart = 3;
                break;

            case 3:
                if (fourthCodePart[letterPlaying] == '.') PlaySound(dot);
                else if (fourthCodePart[letterPlaying] == '-') PlaySound(dash);
                else {  // Must be null, we're done...
                    onPart = 0;
                    letterPlaying = NOT_LETTER;
                    GetMorseText((NOT_LETTER + 1), NULL);
                    return;
                }
                onPart = 4;
                break;

            case 4:
                if (fifthCodePart[letterPlaying] == '.') PlaySound(dot);
                else if (fifthCodePart[letterPlaying] == '-') PlaySound(dash);
                else {  // Must be null, we're done...
                    onPart = 0;
                    letterPlaying = NOT_LETTER;
                    GetMorseText((NOT_LETTER + 1), NULL);
                    return;
                }
                onPart = 5;
                break;

            case 5:
                if (sixthCodePart[letterPlaying] == '.') PlaySound(dot);
                else if (sixthCodePart[letterPlaying] == '-') PlaySound(dash);
                else {  // Must be null, we're done...
                    onPart = 0;
                    letterPlaying = NOT_LETTER;
                    GetMorseText((NOT_LETTER + 1), NULL);
                    return;
                }
                onPart = 6;
                break;

            case 6: // All done!
                onPart = 0;
                letterPlaying = NOT_LETTER;
                GetMorseText((NOT_LETTER + 1), NULL);
                break;

            default:
                onPart = 0;
                letterPlaying = NOT_LETTER;
                GetMorseText((NOT_LETTER + 1), NULL);
                break;
        }
        return;
    }

    // We've been asked to play a new letter but the previous one is still playing
    // TODO: Handle this situation?
    // if (letter < 40 && letterPlaying < 40)
}


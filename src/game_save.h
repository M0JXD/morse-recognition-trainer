/* This defines saving aspects; WPM, Tone, Colour Theme, Levels */ 

#ifndef GAME_SAVE_H
#define GAME_SAVE_H

typedef struct SaveState {
    int windowWidth, windowLength;
    int WPM, tone;
    int theme;
    int levels[40] = { 0 };  // Koch method levels
} saveState;


void LoadState();
void SaveState();
void UpdateLevel(char* letterToUpdate);

#endif  // GAME_SAVE_H
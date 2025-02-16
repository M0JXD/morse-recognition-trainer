/* This defines saving aspects; WPM, Tone, Colour Theme, Levels */ 

#ifndef GAME_SAVE_H
#define GAME_SAVE_H

#define SAVE_FILE "save.mrt"

typedef struct SaveState {
    int windowWidth, windowLength;
    int WPM, tone;
    int theme;
    int levels[40];  // Koch method levels, Koch order
    int activatedLetters[40];  // Active letters are !0, Koch order.
} SaveState;


void LoadData(SaveState *saveState);

void SaveData(SaveState *saveState);

#endif  // GAME_SAVE_H
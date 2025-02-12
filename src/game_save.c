#include "game_save.h"
#include "raylib.h"
#include "string.h"

void LoadData(SaveState *saveState) {
    // Check that save exists
    // mrt is arbritary, for "morse recognition trainer"
    if (FileExists(SAVE_FILE)) {
        // I have a lot of expectations here. 
        // If the file is not as anticipated the program will likely segfault.
        int dataSize;
        unsigned char* file = LoadFileData("save.mrt", &dataSize);

        saveState->windowWidth = (int)file[0];
        saveState->windowLength = (int)file[1];
        saveState->theme = (int)file[2];
        saveState->tone = (int)file[4];
        saveState->WPM = (int)file[5];

        // Now the fun part...
        for (int i = 0; i < 40; i++) {
            saveState->activatedLetters[i] = (int)file[6 + i];
            saveState->levels[i] = (int)file[47 + i];
        }
        UnloadFileData(file);

    } else {
        // There's no save to load, set some defaults
        saveState->windowWidth = 640;
        saveState->windowLength = 480;
        saveState->theme = 1; // Light theme
        saveState->tone = 700;
        saveState->WPM = 20;
        memset(saveState->activatedLetters, 0, 40);
        memset(saveState->levels, 0, 40);

        // Testing
        // saveState->activatedLetters[0] = 1;  
        // saveState->activatedLetters[1] = 1;
        // saveState->levels[0] = 1;
        // saveState->levels[1] = 4;
    }
}

void SaveData(SaveState *saveState) {
    int dataSize;
    if(!FileExists(SAVE_FILE)){
        // I think if the file doesn't exist, LoadFileData makes it anyways.
        unsigned char *file = LoadFileData(SAVE_FILE, &dataSize);
    }

    unsigned char newData[90] = {
        saveState->windowWidth,
        saveState->windowLength,
        saveState->theme,
        saveState->tone,
        saveState->WPM,
    };

    for (int i = 0; i < 40; i++) {
        newData[6 + i] = saveState->activatedLetters[i];
        newData[47 + i] = saveState->levels[i];
    }

    SaveFileData(SAVE_FILE, newData, 90);
}
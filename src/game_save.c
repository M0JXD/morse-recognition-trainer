#include "game_save.h"
#include "raylib.h"
#include "string.h"

void LoadData(SaveState *saveState) {
    // Check that save exists
    // mrt is arbritary, for "morse recognition trainer"
    if (FileExists("save.mrt")) {
        // I have a lot of expectations here. 
        // If the file is not as anticipated the program will likely segfault.
        int dataSize;
        unsigned char* file = LoadFileData("save.mrt", &dataSize);

        saveState->windowWidth = file[0];
        saveState->windowLength = file[1];
        saveState->theme = file[2];
        saveState->tone = file[4];
        saveState->WPM = file[5];

        // Now the fun part...
        for (int i = 0; i < 40; i++) {
            saveState->activated_letters[i] = file[6 + i];
            saveState->levels[i] = file[46 + i];
        }
        UnloadFileData(file);

    } else {
        // There's no save to load, set some defaults
        saveState->windowWidth = 640;
        saveState->windowLength = 480;
        saveState->theme = 1; // Light theme
        saveState->tone = 700;
        saveState->WPM = 20;
        memset(saveState->activated_letters, 0, 40);
        memset(saveState->levels, 0, 40);
    }
}

void SaveData(SaveState *saveState) {
    
}
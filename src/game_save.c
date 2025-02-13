#include "game_save.h"
#include "raylib.h"
#include "string.h"
#include "stdio.h"

void LoadData(SaveState *saveState) {
    // Check that save exists
    // mrt is arbritary, for "morse recognition trainer"
    if (FileExists(SAVE_FILE)) {
        // I have a lot of expectations here. 
        // If the file is not as anticipated the program will likely segfault.
        // int dataSize;
        // unsigned char* file = LoadFileData("save.mrt", &dataSize);

        FILE *file;
        file = fopen(SAVE_FILE, "r");
        int saveData[90];

        int failCheck = fread(saveData, sizeof(int), 90, file);

        if (!failCheck) {
            puts("Bad fail trying to get data!");
            return;
        }

        saveState->windowWidth  = saveData[0];
        saveState->windowLength = saveData[1];
        saveState->theme        = saveData[2];
        saveState->tone         = saveData[3];
        saveState->WPM          = saveData[4];

        for (int i = 0; i < 40; i++) {
            saveState->activatedLetters[i] = (int)saveData[6 + i];
            saveState->levels[i] = (int)saveData[47 + i];
        }
        fclose(file);

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

    FILE *file = fopen(SAVE_FILE, "w");

    int newData[90] = {
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

    fwrite(newData, sizeof(int), 90, file);
    fclose(file);
}
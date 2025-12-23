#if defined(PLATFORM_ANDROID)
#include "raymob.h"
#else
#include "raylib.h"
#endif
#include "stdio.h"  // FILE
#include "string.h"  // memset

#include "game_save.h"

void LoadData(SaveState *saveState) {
    // I have a lot of expectations here.
    // If the file is not as anticipated the program will likely segfault.
#if defined(PLATFORM_ANDROID)
    const char* saveFilePath = TextFormat(
            "%s/%s", GetAndroidApp()->activity->internalDataPath, SAVE_FILE);
#endif

#if defined(PLATFORM_ANDROID)
    if (FileExists(saveFilePath)) {
#else
    if (FileExists(SAVE_FILE)) {
#endif

#if defined(PLATFORM_ANDROID)
        FILE *file = fopen(saveFilePath, "r");
#else
        FILE *file = fopen(SAVE_FILE, "r");
#endif
        int saveData[90];
        int failCheck = fread(saveData, sizeof(int), 90, file);

        if (failCheck < 90) {
            //puts("Bad fail trying to get data!");
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
        saveState->theme = 0; // Light green
        saveState->tone = 700;
        saveState->WPM = 20;
        memset(saveState->activatedLetters, 0, 40);
        memset(saveState->levels, 0, 40);
    }
}

void SaveData(SaveState *saveState) {

#if defined(PLATFORM_ANDROID)
    const char* saveFilePath = TextFormat(
            "%s/%s", GetAndroidApp()->activity->internalDataPath, SAVE_FILE);
#endif

#if defined(PLATFORM_ANDROID)
       FILE *file = fopen(saveFilePath, "w");
#else
       FILE *file = fopen(SAVE_FILE, "w");
#endif

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

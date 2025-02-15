#include "raylib.h"
#include "stdio.h"  // sprintf
#include "stdlib.h" // rand

#include "lessons.h"
#include "letters.h"
#include "morse.h"
#include "game_save.h"

#define COUNTER_DELAY 25

extern Sound dot, dash, incorrect;
extern SaveState gameSave;
extern int inLesson;
extern int oldInLesson;

static int currentLetter = 0;
static enum LessonState {
    ASKING,
    WAITING,
    LAST_INCORRECT,
    CONGRATS,
} lessonState = WAITING;

void GetLessonText(char *string) {
    switch (lessonState) {
        case ASKING:
            sprintf(string, "Playing Letter...");
        case WAITING:
            sprintf(string, "Which letter was played?");
            break;
        case LAST_INCORRECT:
            sprintf(string, "Wrong, repeating letter...");
            break;
        case CONGRATS:
            sprintf(string, "Correct!");
            break;
        default:
            sprintf(string, "I am lost, what happened?");
            break;
    }
}

int UpdateLevel(int kochLetterToUpdate) {
    gameSave.levels[kochLetterToUpdate]++;
    if (gameSave.levels[kochLetterToUpdate] > 8) {
        gameSave.levels[kochLetterToUpdate] = 8;
    }
    // If the level is more than two, and the next Koch letter is not activated, activate it.
    if (gameSave.levels[kochLetterToUpdate] >= 3 && !gameSave.activatedLetters[kochLetterToUpdate + 1]) {
        // Force it to be the next letter
        gameSave.activatedLetters[kochLetterToUpdate + 1] = 1;
        return kochLetterToUpdate + 1;
    }
    return NOT_LETTER;
}

void RegressLevel(int kochLetterToRegress) {
    if (!gameSave.levels[kochLetterToRegress]) {
        ResetDueToZeroLevel(kochLetterToRegress);
    }
    gameSave.levels[kochLetterToRegress]--;
    if (!gameSave.levels[kochLetterToRegress]) {
        ResetDueToZeroLevel(kochLetterToRegress);
    }
    if (gameSave.levels[kochLetterToRegress] < 0) {
        gameSave.levels[kochLetterToRegress] = 0;
    }
}

int GetRandomActiveLetter(int mode, int introducedLetter) {
    // For Everything mode
    if (mode) {
        return (rand() % (40)); 
    }

    // if only the first letter is active, we must send it!
    if (!gameSave.activatedLetters[1]) {
        return 0;
    }

    static char lastLetter = '*';
    static char lastLastLetter = '*';

    // It's a newly introduced letter
    if (introducedLetter != NOT_LETTER) {
        lastLastLetter = lastLetter;
        lastLetter = introducedLetter;
        return introducedLetter;
    }

    // Get the amount of active letters
    int amountOfLetters;
    for (amountOfLetters = 0; amountOfLetters < 40; ++amountOfLetters) {
        if(!gameSave.activatedLetters[amountOfLetters])
            break;
    }

    // Let's start by choosing a random active letter anyways
    int nextLetter = (rand() % (amountOfLetters));

    // 60% of the time, force it to be a low level letter
    // There should always be one with less then three sections except when all letters are activated
    if ((((rand() % 5) + 1) <= 3) && !gameSave.activatedLetters[39]) {
        while (gameSave.levels[nextLetter] >= 3) {
            nextLetter = (rand() % (amountOfLetters));
        }
    }

    // If the last two letters were the same, force it to be different
    if (lastLastLetter == lastLetter) {
        while (nextLetter == lastLetter) {
            nextLetter = (rand() % (amountOfLetters));
        }
    }

    lastLastLetter = lastLetter;
    lastLetter = nextLetter;
    return nextLetter;
}

void ResetDueToZeroLevel(int letterThatReachedZero) {
    for (int i = letterThatReachedZero + 1; i < 40; i++) {
        gameSave.activatedLetters[i] = 0;
        gameSave.levels[i] = 0;
    }

    if (!gameSave.activatedLetters[0]) {
        gameSave.activatedLetters[0] = 1;
    }
}

void UpdateLesson(int characterDetected) {
    static int counter = 0;  // Used to delay between asking letters
    static int newLetter = NOT_LETTER;
    static enum Marker {PLAYING_INCORRECT, NO_MARKER} incorrectMarker = NO_MARKER;

    // Just entered Lesson Mode, force a letter to be asked
    if ((oldInLesson != inLesson) && inLesson) {
        lessonState = CONGRATS;
        counter = 1;
    }

    // Must be first ever play if this occurs
    if (!gameSave.activatedLetters[0]) {
        gameSave.activatedLetters[0] = 1;
    }

    switch (lessonState) {
        case ASKING:
            if (IsSoundPlaying(dot) || IsSoundPlaying(dash)) {
                break;
            } else {
                lessonState = WAITING;
            }
            break;

        case WAITING:
            if (characterDetected == currentLetter) {
                lessonState = CONGRATS;  // Last letter was correct
                counter = COUNTER_DELAY;
                newLetter = UpdateLevel(characterDetected);
            } else if (characterDetected != NOT_LETTER) {
                RegressLevel(currentLetter);
                // Repeat letter
                PlaySound(incorrect);
                incorrectMarker = PLAYING_INCORRECT;
                lessonState = LAST_INCORRECT;
            }
            break;

        case CONGRATS:
            if (counter == 1) {
                currentLetter = GetRandomActiveLetter(0, newLetter);
                PlayMorse(getQwertyFromKoch(currentLetter));
                lessonState = ASKING;
                newLetter = NOT_LETTER;
            } else if (counter) {
                counter--;
            }
            break;

        case LAST_INCORRECT:
            if (characterDetected == currentLetter) {
                lessonState = CONGRATS;
                counter = COUNTER_DELAY;
            } else if (characterDetected != NOT_LETTER) {
                incorrectMarker = PLAYING_INCORRECT;
                PlaySound(incorrect);
            }
            break;
    }

    // Repeat the morse after the incorrect sound is finished playing
    if (!IsSoundPlaying(incorrect) && incorrectMarker == PLAYING_INCORRECT) {
        PlayMorse(getQwertyFromKoch(currentLetter));
        incorrectMarker = NO_MARKER;
    }
        

    oldInLesson = inLesson;
}
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
extern int mode;
extern int oldMode;

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
            break;
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
    int letterToReturn = NOT_LETTER;
    if (mode == LESSON) {
        gameSave.levels[kochLetterToUpdate]++;
        if (gameSave.levels[kochLetterToUpdate] > 8) {
            gameSave.levels[kochLetterToUpdate] = 8;
        }
        // If the level is more than two, and the next Koch letter is not activated, activate it.
        // Provided we haven't already activated everything that is!
        if (gameSave.levels[kochLetterToUpdate] >= 3 
            && !gameSave.activatedLetters[kochLetterToUpdate + 1]
            && kochLetterToUpdate < 39) {
            // Force it to be the next letter
            gameSave.activatedLetters[kochLetterToUpdate + 1] = 1;
            letterToReturn = kochLetterToUpdate + 1;
        } else {
            letterToReturn = NOT_LETTER;
        }
    }
    return letterToReturn;
}

void RegressLevel(int kochLetterToRegress) {
    if (mode == LESSON) {
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
}

int GetRandomActiveLetter(int introducedLetter) {
    static char lastLetter = '*';
    static char lastLastLetter = '*';
    int nextLetter = '*';

    // For Everything mode
    if (mode == EVERYTHING) {
        nextLetter = (rand() % (40));
        // If the last two letters were the same, force it to be different
        if (lastLastLetter == lastLetter) {
            while (nextLetter == lastLetter) {
                nextLetter = (rand() % (40));
            }
        }
    } else if (mode == LESSON) {
        // Only do random stuff if needed
        if (introducedLetter == NOT_LETTER && gameSave.activatedLetters[1]) {
            int amountOfLetters;
            // Get the amount of active letters
            for (amountOfLetters = 0; amountOfLetters < 40; ++amountOfLetters) {
                if(!gameSave.activatedLetters[amountOfLetters])
                    break;
            }

            // Let's start by choosing a random active letter anyways
            nextLetter = (rand() % (amountOfLetters));

            // 40% of the time, force it to be a low level letter
            // There should always be one with less then three sections except when all letters are activated
            if ((((rand() % 5) + 1) <= 2) && !gameSave.activatedLetters[39]) {
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
        } else if (introducedLetter != NOT_LETTER) {
            // Send the introduced letter
            nextLetter = introducedLetter;
        } else if (!gameSave.activatedLetters[1]) {
            // We must send the first letter
            nextLetter = 0;
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

    // Just entered new Lesson-style Mode, force a letter to be asked
    if ((oldMode != mode) && ((mode == LESSON) || (mode == EVERYTHING))) {
        lessonState = CONGRATS;
        counter = 1;
    }
    oldMode = mode;

    // Must be first ever play if this occurs
    if (!gameSave.activatedLetters[0] && mode != EVERYTHING) {
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
                currentLetter = GetRandomActiveLetter(newLetter);
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
}
#include "raylib.h"

#include "lessons.h"
#include "letters.h"
#include "morse.h"
#include "game_save.h"

#include "stdio.h"
#include "stdlib.h"

#define COUNTER_DELAY 25


extern Sound dot, dash;
extern int inLesson;
extern int oldInLesson;
extern SaveState gameSave;
static int currentLetter = 0;

static enum LessonState {
    ASKING,
    WAITING,
    LAST_INCORRECT,
    CONGRATS,
    TEACHING
} lessonState = WAITING;

void GetLessonText(char *string) {
    int lessonStateCheck = lessonState;
    switch (lessonState) {
        case ASKING:
            sprintf(string, "Playing Letter...");
        case WAITING:
            sprintf(string, "Which letter was played?");
            break;
        case LAST_INCORRECT:
            sprintf(string, "Wrong, try again.");
            break;
        case CONGRATS:
            sprintf(string, "Correct!");
            break;
        case TEACHING:
            TeachLesson(NOT_LETTER, string, NULL);
            break;
        default:
            sprintf(string, "I am lost, what happened?");
            break;
    }
}

void UpdateLevel(int kochLetterToUpdate, int* externalCounter) {
    gameSave.levels[kochLetterToUpdate]++;
    // If the level is more than two, and the next Koch letter is not activated, activate it.
    if (gameSave.levels[kochLetterToUpdate] >= 2 && !gameSave.activatedLetters[kochLetterToUpdate + 1]) {
        gameSave.activatedLetters[kochLetterToUpdate + 1] = 1;
        TeachLesson(kochLetterToUpdate + 1, NULL, externalCounter);
        lessonState = TEACHING;
    }
}

int RegressLevel(int kochLetterToRegress) {
    if (!gameSave.levels[kochLetterToRegress]) {
        ResetDueToZeroLevel(kochLetterToRegress);
    }
    gameSave.levels[kochLetterToRegress]--;
    if (!gameSave.levels[kochLetterToRegress]) {
        ResetDueToZeroLevel(kochLetterToRegress);
    }
}

int GetRandomActiveLetter(void) {
    int amountOfLetters;
    for (amountOfLetters = 0; amountOfLetters < 40; ++amountOfLetters) {
        if(!gameSave.activatedLetters[amountOfLetters])
            break;
    }
    int randomLetter = (rand() % (amountOfLetters)); 
    return randomLetter;
}

void ResetDueToZeroLevel(int letterThatReachedZero) {
    for (int i = letterThatReachedZero; i < 40; i++) {
        gameSave.activatedLetters[i] = 0;
        gameSave.levels[i] = 0;
    }
}

void UpdateLesson(int characterDetected) {
    static int counter = 0;  // Used to delay between asking letters


    // Just entered Lesson Mode
    if ((oldInLesson != inLesson) && inLesson) {
        lessonState = CONGRATS;
        counter = 1;
    }

    // Must be first ever play, no save present
    if (!gameSave.activatedLetters[0]) {
        gameSave.activatedLetters[0] = 1;
        TeachLesson(0, NULL, &counter);
        lessonState = TEACHING;
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
                UpdateLevel(characterDetected, &counter);
            } else if (characterDetected != NOT_LETTER) {
                RegressLevel(characterDetected);
                lessonState = LAST_INCORRECT;
            }
            break;

        case CONGRATS:
            if (counter == 1) {
                currentLetter = GetRandomActiveLetter();
                PlayMorse(getQwertyFromKoch(currentLetter));
                lessonState = ASKING;
            } else if (counter) {
                counter--;
            }
            break;
        case LAST_INCORRECT:
            if (characterDetected == currentLetter) {
                lessonState = CONGRATS;
                counter = COUNTER_DELAY;
            } else if (characterDetected != NOT_LETTER) {
                lessonState = LAST_INCORRECT;
            }
            break;
        case TEACHING:
            if (IsSoundPlaying(dot) || IsSoundPlaying(dash) || counter) {
                counter--;
                break;
            } else {
                lessonState = CONGRATS;
                counter = 1;
            }
            break;
    }
    oldInLesson = inLesson;
}

void TeachLesson(int letterToTeach, char* string, int* externalCounter) {
    static int rememberLetter = 0;
    rememberLetter = (letterToTeach == NOT_LETTER) ? rememberLetter : letterToTeach;
    
    // Being called for the string
    if(letterToTeach == NOT_LETTER && string != NULL) {
        sprintf(string, "This is letter %s", lettersKoch[rememberLetter]);
    } else {
        // Being called to teach
        PlayMorse(getQwertyFromKoch(rememberLetter));
        lessonState = TEACHING;
        *externalCounter = COUNTER_DELAY + 20;
    }
}




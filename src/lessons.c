#include "lessons.h"
#include "letters.h"
#include "morse.h"
#include "game_save.h"

#include "stdio.h"
#include "stdlib.h"

extern int inLesson;
extern SaveState gameSave;
int currentLetter = 0;

enum LessonState {
    ASKING,
    WAITING,
    LAST_INCORRECT,
    CONGRATS,
    TEACHING
} lessonState;

void GetLessonText(char *string) {
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
            sprintf(string, "Correct! Status updated.");
            break;
        case TEACHING:
            TeachLesson(NOT_LETTER, string);
        default:
            sprintf(string, "I am lost, what happened?");
            break;
    }
}

void UpdateLevel(int kochLetterToUpdate) {
    gameSave.levels[kochLetterToUpdate] += 1;
    // If the level is more than two, and the next Koch letter is not activated, activate it.
    if (gameSave.levels[kochLetterToUpdate] >= 2 && !gameSave.activatedLetters[kochLetterToUpdate + 1]) {
        gameSave.activatedLetters[kochLetterToUpdate + 1] = 1;
        TeachLesson(kochLetterToUpdate + 1, NULL);
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
    int randomLetter = (rand() % (amountOfLetters + 1)); 
    return randomLetter;
}

void ResetDueToZeroLevel(int letterThatReachedZero) {
    for (int i = 1; i < 40; i++) {
        
    }
}

void UpdateLesson(int characterDetected) {
    static int counter = 0;  // Used to delay between asking letters
    static int oldInLesson = 0;

    // Just entered Lesson Mode
    if ((oldInLesson != inLesson) && inLesson) {
        lessonState = CONGRATS;
        counter = 1;
    }

    switch (lessonState) {
        case ASKING:
            char string[40];
            GetMorseText(NOT_LETTER, string);
            if (string[0]) {
                break;
            } else {
                lessonState = WAITING;
            }
            break;
        case WAITING:
            if (characterDetected == currentLetter) {
                lessonState = CONGRATS;  // Last letter was correct
                counter = 50;
                UpdateLevel(characterDetected);
            } else if (characterDetected != NOT_LETTER){
                RegressLevel(characterDetected);
                lessonState = LAST_INCORRECT;
            }
            break;

        case CONGRATS:
            if (counter == 1) {
                //currentLetter = GetRandomActiveLetter();
                PlayMorse(getQwertyFromKoch(currentLetter));
                lessonState = ASKING;
            } else if (counter) {
                counter--;
            }
            break;
        case LAST_INCORRECT:
            if (characterDetected == currentLetter) {
                lessonState = CONGRATS;  // Last letter was correct
                counter = 50;
                UpdateLevel(characterDetected);
            } else {
                lessonState = LAST_INCORRECT;
            }
            break;
        case TEACHING:
            if (1) ;
            break;
    }
    oldInLesson = inLesson;
}

void TeachLesson(int letterToTeach, char* string) {
    static int rememberLetter = 0;
    rememberLetter = (letterToTeach == NOT_LETTER) ? rememberLetter : letterToTeach;
    if(letterToTeach == NOT_LETTER && string != NULL) {
        sprintf(string, "This is letter %s", lettersKoch[rememberLetter]);
    }
}




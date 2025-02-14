#include "raylib.h"

#include "lessons.h"
#include "letters.h"
#include "morse.h"
#include "game_save.h"

#include "stdio.h"
#include "stdlib.h"

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
    int lessonStateCheck = lessonState;
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

void UpdateLevel(int kochLetterToUpdate) {
    gameSave.levels[kochLetterToUpdate]++;
    // If the level is more than two, and the next Koch letter is not activated, activate it.
    if (gameSave.levels[kochLetterToUpdate] >= 2 && !gameSave.activatedLetters[kochLetterToUpdate + 1]) {
        gameSave.activatedLetters[kochLetterToUpdate + 1] = 1;
    }

    if (gameSave.levels[kochLetterToUpdate] > 8) {
        gameSave.levels[kochLetterToUpdate] = 8;
    }
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
    for (int i = letterThatReachedZero + 1; i < 40; i++) {
        gameSave.activatedLetters[i] = 0;
        gameSave.levels[i] = 0;
    }
}

void UpdateLesson(int characterDetected) {
    static int counter = 0;  // Used to delay between asking letters
    static enum Marker {PLAYING_INCORRECT, NO_MARKER} marker;

    // Just entered Lesson Mode
    if ((oldInLesson != inLesson) && inLesson) {
        lessonState = CONGRATS;
        counter = 1;
    }

    // Must be first ever play, no save present
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
                UpdateLevel(characterDetected);
            } else if (characterDetected != NOT_LETTER) {
                RegressLevel(currentLetter);
                // Repeat letter
                PlaySound(incorrect);
                marker = PLAYING_INCORRECT;
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
                marker = PLAYING_INCORRECT;
                PlaySound(incorrect);
            }
            break;
    }

    // To repeat the morse after the incorrect sound
    if (!IsSoundPlaying(incorrect) && marker == PLAYING_INCORRECT) {
        PlayMorse(getQwertyFromKoch(currentLetter));
        marker = NO_MARKER;
    }
        

    oldInLesson = inLesson;
}
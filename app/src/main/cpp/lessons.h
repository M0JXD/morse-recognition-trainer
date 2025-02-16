#ifndef LESSONS_H
#define LESSONS_H

enum Modes {REPEAT = 0, LESSON = 1, EVERYTHING = 2};

void GetLessonText(char* string);  // Provides the appropriate lesson text for the statusbar depending on current lesson state
void UpdateLesson(int characterDetected);  // Passes the last pressed character so the lesson state can update.
int UpdateLevel(int kochLetterToUpdate); // Returns newly activated letter, otherwise NOT_LETTER
void RegressLevel(int kochLetterToRegress); 
void ResetDueToZeroLevel(int letterThatReachedZero);
int GetRandomActiveLetter(int introducedLetter);  // If introduced Letter is not NOT_LETTER and we're in Lesson mode it'll return it.

#endif
#ifndef LESSONS_H
#define LESSONS_H

void GetLessonText(char* string);  // Provides the appropriate lesson text for the statusbar depending on current lesson state
void UpdateLesson(int characterDetected);  // Passes the last pressed character so the lesson state can update.
void UpdateLevel(int kochLetterToUpdate, int* externalCounter);  // NO
int RegressLevel(int kochLetterToRegress);  // Returns 1 if it went to zero.
void ResetDueToZeroLevel(int letterThatReachedZero);

#endif
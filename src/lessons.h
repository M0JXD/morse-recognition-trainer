#ifndef LESSONS_H
#define LESSONS_H

void GetLessonText(char* string);  // Provides the appropriate lesson text for the statusbar depending on current lesson state
void UpdateLesson(int characterDetected);  // Passes the last pressed character so the lesson state can update.
int UpdateLevel(int kochLetterToUpdate); // Returns newly activated letter, otherwise NOT_LETTER
void RegressLevel(int kochLetterToRegress); 
void ResetDueToZeroLevel(int letterThatReachedZero);
int GetRandomActiveLetter(int mode, int introducedLetter);  // Mode specifies whether to be random for Everything mode 

#endif
#ifndef LESSONS_H
#define LESSONS_H

extern int inLesson;

int StartLesson(void);  // Checks the current global gamesave and starts the appropriate lesson
int EndLesson(int force);  // Always called at end of the loop, ends the lesson if it's done.
void GetLessonText(char* string);  // Provides the appropriate lesson text for the statusbar depending on current lesson state
void UpdateLesson(int characterDetected);  // Passes the last pressed character so the lesson state can update.
void UpdateLevel(char* kochLetterToUpdate);

#endif
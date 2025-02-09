#include "lessons.h"

int StartLesson(void) {
    return 1;
}

int EndLesson(int force) {
    return 0;
}

char* GetLessonText(void) {
    // "Lesson: %d"
    // "Playing Letter..." 
    // "Which Letter Was Played?"
    // "Wrong, try again."
    // "Repeating letter as wrong 3 times..."
    // "Correct! Status updated"
    // DrawText(GetLessonText())
}

void UpdateLesson(int characterDetected) {

}


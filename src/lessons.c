#include "lessons.h"
#include "letters.h"

int StartLesson(void) {
    return 1;
}

int EndLesson(int force) {
    return 0;
}

void GetLessonText(char *string) {
    // "Lesson: %d"
    // "Playing Letter..." 
    // "Which Letter Was Played?"
    // "Wrong, try again."
    // "Repeating letter as wrong 3 times..."
    // "Correct! Status updated"
}

void UpdateLesson(int characterDetected) {

}


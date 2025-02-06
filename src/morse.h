/* This header defines audio functions for morse output
 *
 * See for reference: https://morsecode.world/international/timing.html
 * Also: https://en.wikipedia.org/wiki/Morse_code */

#ifndef MORSE_H
#define MORSE_H

#include "raylib.h"

Wave CalculateDot(int WPM, int tone);
Wave CalculateDash(int WPM, int tone);
void FreeDotOrDashSamples(Wave toFree);
Wave ConcatWaves(int n, ...);
Sound CalculateMorseLetter(int letter, Wave dot, Wave dash);
void playMorse(int letter);

// For words and sentences, at some point[]
// Sound calculateGroup(const char* group, int farnsworthTiming);

#endif  // MORSE_H

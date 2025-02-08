/* Defines audio functions for morse output
 *
 * See for reference: https://morsecode.world/international/timing.html
 * Also: https://en.wikipedia.org/wiki/Morse_code */

#ifndef MORSE_H
#define MORSE_H

#include "raylib.h"

// These are sized to be big enough for the lowest allowed WPM
// no dynamic memory aspects
extern Wave dot;
extern Wave dash;

Wave CalculateDotAndDash(int WPM, int tone);
Wave ConcatWaves(int n, ...);
Sound CalculateMorseLetter(int letter, Wave dot, Wave dash);
void playMorse(int letter);

// For words and sentences, at some point
// Sound calculateGroup(const char* group, int farnsworthTiming);

#endif  // MORSE_H

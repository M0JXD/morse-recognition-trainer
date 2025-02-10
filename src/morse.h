/* Defines audio functions for morse output
 *
 * See for reference: https://morsecode.world/international/timing.html
 * Also: https://en.wikipedia.org/wiki/Morse_code */

#ifndef MORSE_H
#define MORSE_H

#include "raylib.h"

/* A selection of wav files are included to play the morse sounds. 
 * The original intention was to generate on the fly, but for a measly 48kB this is much easier!
 * Included options are:
 * 650Hz 10WPM
 * 650Hz 15WPM
 * 650Hz 20WPM
 * 650Hz 25WPM
 * 700Hz 10WPM
 * 700Hz 15WPM
 * 700Hz 20WPM
 * 700Hz 25WPM
 * 800Hz 10WPM
 * 800Hz 15WPM
 * 800Hz 20WPM
 * 800Hz 25WPM
 * This site was used to generate them: https://www.meridianoutpost.com/resources/etools/calculators/calculator-morse-code.php?
 * Generated using letters "E" and "T". I checked in Audacity and they contain the appropriate gaps after the sound already. 
 * Please use the site to generate the ones you need should you're requirements not be provided for */

void PlayMorse(int letter);

char* GetMorseText(void);


#endif  // MORSE_H

/* Defines functions relating to morse output
 *
 * See for reference: https://morsecode.world/international/timing.html
 * Also: https://en.wikipedia.org/wiki/Morse_code */

 /* A selection of wav files are included to play the morse sounds. 
 * The original intention was to generate on the fly, but for a couple hundred kilobytes this is much easier!
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
 * Generated using letters "E" and "T". They need trimmed, there is a script called trimmer.py that will do this. */

#ifndef MORSE_H
#define MORSE_H

void LoadMorseSounds(void);

/* If passed NOT_LETTER then sets @text appropriate string for current state.
 * Is passed letters in PlayMorse so it knows what letter we're on.
 * If passed (NOT_LETTER + 1) that tells it nothing is playing (done in PlayMorse) */
void GetMorseText(int letter, char* text);

void PlayMorse(int letter);

#endif  // MORSE_H

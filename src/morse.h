/* This header defines audio functions for morse output
 * Yes, code in the header. I'm a naughty boy.
 *
 * See for reference: https://morsecode.world/international/timing.html
 * Also: https://en.wikipedia.org/wiki/Morse_code */

#ifndef MORSE_H
#define MORSE_H

#include "raylib.h"
#include <stdlib.h>
#include <math.h>

/* These calculate and returns Wave 'files' for the dot and dash given the WPM and Tone.
 * A given Wave file lasts the length of a dot (1 unit) or dash (3 units) plus the Intra-character space (1 unit) */
Wave CalculateDot(int WPM, int tone) {
    // What I'm hoping to acheive is to calculate all the PCM samples and mush them into a raylib "Wave" construct.
    // Then a raylib "Sound" can be made which is easy to play.
    Wave dot;
        dot.sampleRate = 44100;
        dot.sampleSize = 32;  // chosen for convienience, can use float type
        dot.channels = 1;
    
    // Calculate how long (in seconds) the sample should be from WPM. Rounded to integer value!
    // NB: Paris standard. CODEX would be nice to have.
    float length = (60 / (50 * WPM)) * 2; // 2x as is one dot AND one space
    dot.frameCount = length * 44100;
    
    // See LoadWaveSamples(), I think for 32 bit depth they are float sized
    float* samples = malloc(sizeof(float) * dot.frameCount);
    
    for(unsigned int i = 0; i < dot.frameCount; i++) {
        // Half of the sample is the dot
        if (i < (dot.frameCount / 2)) {
            samples[i] = sinf(tone * i);
        } else {
            // The rest is blank space
            samples[i] = 0.0f;
        }
    }

    dot.data = samples;
    // free(samples);
    return dot;
}


Wave CalculateDash(int WPM, int tone) {
    Wave dash;
        dash.sampleRate = 44100;
        dash.sampleSize = 32;
        dash.channels = 1;
    
    // Calculate how long (in seconds) the sample should be from WPM.
    // NB: Paris standard. CODEX would be nice to have.
    float length = (60 / (50 * WPM)) * 4; // 2x as is one dash (3 units) AND one space
    dash.frameCount = length * 44100;
    
    // See LoadWaveSamples()
    float* samples = malloc(sizeof(float) * dash.frameCount);
    
    for(unsigned int i = 0; i < dash.frameCount; i++) {
        // 3/4 of the sample is the dash
        if (i < (dash.frameCount * 0.75)) {
            samples[i] = sinf(tone * i);
        } else {
            // The rest is blank space
            samples[i] = 0.0f;
        }
    }

    dash.data = samples;
    // free(samples);
    return dash;
}

void FreeDotOrDashSamples(Wave toFree) {
    // The samples need freed
    // Note that the samples are shallow copies!
    free(toFree.data);
}

/* Calculates the complete Sound file for a given letter.
 * NB: DUE TO NATURE OF OF OTHER CALCULATE FUNCTIONS IT WILL END WITH ONE UNIT OF SPACE. */
Sound CalculateMorseLetter(char letter, Wave dot, Wave dash) {
    switch (letter) {
        // Numbers
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            break;
        case '9':
            break;
        case '0':
            break;
        
        // Letters
        case 'A':
            break;
        case 'B':
            break;
        case 'C':
            break;
        case 'D':
            break;
        case 'E':
            break;
        case 'F':
            break;
        case 'G':
            break;
        case 'H':
            break;
        case 'I':
            break;
        case 'J':
            break;
        case 'K':
            break;
        case 'L':
            break;
        case 'M':
            break;
        case 'N':
            break;
        case 'O':
            break;
        case 'P':
            break;
        case 'Q':
            break;
        case 'R':
            break;
        case 'S':
            break;
        case 'T':
            break;
        case 'U':
            break;
        case 'V':
            break;
        case 'W':
            break;
        case 'X':
            break;
        case 'Y':
            break;
        case 'Z':
            break;
            
        // Special
        case ',':
            break;
        case '.':
            break;
        case '/':
            break;
        case '?':
            break;
    }
        
}

// For words and sentences, at some point[]
// Sound calculateGroup(const char* group, int farnsworthTiming)

#endif  // MORSE_H

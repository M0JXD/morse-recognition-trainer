#include "morse.h"

#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

extern Wave dot;
extern Wave dash;

/* These operate on the global dot and dash Waves to calculate them if the wpm or tone changes
 * A given Wave file lasts the length of a dot (1 unit) or dash (3 units) plus the Intra-character space (1 unit) */
Wave CalculateDotAndDash(int WPM, int tone) {
    // What I'm hoping to acheive is to calculate all the PCM samples and mush them into a raylib "Wave" construct.
    // Then a raylib "Sound" can be made which is easy to play.

    dot.sampleRate = 44100;
    dot.sampleSize = 32;  // chosen for convienience, can use float type
    dot.channels = 1;
    
    // Calculate how long (in seconds) the sample should be from WPM. Rounded to integer value!
    // NB: Paris standard. CODEX would be nice to have.
    float lengthDot = (60 / (50 * WPM)) * 2; // 2x as is one dot AND one space
    dot.frameCount = lengthDot * 44100;
    
    // See LoadWaveSamples(), I think for 32 bit depth they are float sized
    float* samplesDot = malloc(sizeof(float) * dot.frameCount);
    
    for(unsigned int i = 0; i < dot.frameCount; i++) {
        // Half of the sample is the dot
        if (i < (dot.frameCount / 2)) {
            samplesDot[i] = sinf(tone * i);
        } else {
            // The rest is blank space
            samplesDot[i] = 0.0f;
        }
    }

    dot.data = samplesDot;
    // free(samples);
    return dot;

    //--------------------------------------------------------------------------------
    // MAIN LOOP
    //--------------------------------------------------------------------------------
    dash.sampleRate = 44100;
    dash.sampleSize = 32;
    dash.channels = 1;

    // Calculate how long (in seconds) the sample should be from WPM.
    // NB: Paris standard. CODEX would be nice to have.
    float lengthDash = (60 / (50 * WPM)) * 4; // 2x as is one dash (3 units) AND one space
    dash.frameCount = lengthDash * 44100;

    // See LoadWaveSamples()
    float* samplesDash = malloc(sizeof(float) * dash.frameCount);

    for(unsigned int i = 0; i < dash.frameCount; i++) {
        // 3/4 of the sample is the dash
        if (i < (dash.frameCount * 0.75)) {
            samplesDash[i] = sinf(tone * i);
        } else {
            // The rest is blank space
            samplesDash[i] = 0.0f;
        }
    }

    dash.data = samplesDash;
    // free(samples);
    return dash;

}

Wave CalculateDash(int WPM, int tone) {

}

// Pass your waves in order
Wave ConcatWaves(int n, ...) {
    va_list waves;
    va_start(waves, n);
}

/* Calculates the complete Sound file for a given letter.
 * NB: DUE TO NATURE OF OF OTHER CALCULATE FUNCTIONS IT WILL END WITH ONE UNIT OF SPACE. */
Sound CalculateMorseLetter(int letter, Wave dot, Wave dash) {
    switch (letter) {
        // Numbers
        case 0: // 1
            break;
        case 1: // 2
            break;
        case 2: // 3
            break;
        case 3: // 4
            break;
        case 4: // 5
            break;
        case 5: // 6
            break;
        case 6: // 7
            break;
        case 7: // 8
            break;
        case 8: // 9
            break;
        case 9: // 10
            break;
        
        // Letters
        case 10: // A

            break;
        case 11: // B
            break;
        case 12: // C
            break;
        case 13: // D
            break;
        case 14: // E
            break;
        case 15:  // F
            break;
        case 16:  // G
            break;
        case 17:  // H
            break;
        case 18:  // I
            break;
        case 19:  // J
            break;
        case 20:  // K
            break;
        case 21:  // L
            break;
        case 22:  // M
            break;
        case 23:  // N
            break;
        case 24:  // O
            break;
        case 25:  // P
            break;
        case 26:  // Q
            break;
        case 27:  // R
            break;
        case 28:  // S
            break;
        case 29:  // T
            break;
        case 30:  // U
            break;
        case 31:  // V
            break;
        case 32:  // W
            break;
        case 33:  // X
            break;
        case 34: // Y
            break;
        case 35: // Z
            break;

        // Special
        case 36: // ','
            break;
        case 37:  // '.'
            break;
        case 38:  // '/'
            break;
        case 39:  // '?'
            break;
    }  
}

// Plays the given letter
void PlayMorse(int letter) {
    
}
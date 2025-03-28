#include "raylib.h"
#include "stdio.h"  // FILE
// #include "string.h"

#include "letters.h"

const char* lettersQwerty[40] = {
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    // Letters
    "Q",
    "W",
    "E",
    "R",
    "T",
    "Y",
    "U",
    "I",
    "O",
    "P",
    "A",
    "S",
    "D",
    "F",
    "G",
    "H",
    "J",
    "K",
    "L",
    "Z",
    "X",
    "C",
    "V",
    "B",
    "N",
    "M",
    // Special
    ",",
    ".",
    "/",
    "?"
};

// See https://www.qsl.net/kb5wck/super.html
// And: https://lcwo.net/forum/628
// Using LCWO's order
char lettersKoch[40][2] = {
    "K",
    "M",
    "U",
    "R",
    "E",
    "S",
    "N",
    "A", 
    "P",
    "T",
    "L",
    "W",
    "I",
    ".", 
    "J",
    "Z",
    // "=", // Removed as not in app copied!
    "F",
    "O",
    "Y",
    ",",
    "V",
    "G",
    "5",
    "/",
    "Q",
    "9",
    "2",
    "H",
    "3",
    "8",
    "B",
    "?",
    "4",
    "7",
    "C",
    "1",
    "D",
    "6",
    "0", 
    "X" 
};
 
// Yes, I did these by hand. No, it was not fun.
const char firstCodePart[40] = {
    '.', // 1
    '.', // 2
    '.', // 3
    '.', // 4
    '.', // 5
    '-', // 6
    '-', // 7
    '-', // 8
    '-', // 9
    '-', // 0

    '-',  // Q
    '.',  // W
    '.',  // E
    '.',  // R
    '-',  // T
    '-',  // Y
    '.',  // U
    '.',  // I
    '-',  // O
    '.',  // P
    '.',  // A
    '.',  // S
    '-',  // D
    '.',  // F
    '-',  // G
    '.',  // H
    '.',  // J
    '-',  // K
    '.',  // L
    '-',  // Z
    '-',  // X
    '-',  // C
    '.',  // V
    '-',  // B
    '-',  // N
    '-',  // M

    '-', // ,
    '.', // .
    '-', // /
    '.'  // ?
};

const char secondCodePart[40] = {
    '-', // 1
    '.', // 2
    '.', // 3
    '.', // 4
    '.', // 5
    '.', // 6
    '-', // 7
    '-', // 8
    '-', // 9
    '-', // 0

    '-',  // Q
    '-',  // W
    0,    // E
    '-',  // R
    0,    // T
    '.',  // Y
    '.',  // U
    '.',  // I
    '-',  // O
    '-',  // P
    '-',  // A
    '.',  // S
    '.',  // D
    '.',  // F
    '-',  // G
    '.',  // H
    '-',  // J
    '.',  // K
    '-',  // L
    '-',  // Z
    '.',  // X
    '.',  // C
    '.',  // V
    '.',  // B
    '.',  // N
    '-',  // M

    '-', // ,
    '-', // .
    '.', // /
    '.'  // ?

};

const char thirdCodePart[40] = {
    '-', // 1
    '-', // 2
    '.', // 3
    '.', // 4
    '.', // 5
    '.', // 6
    '.', // 7
    '-', // 8
    '-', // 9
    '-', // 0

    '.',  // Q
    '-',  // W
    0,    // E
    '.',  // R
    0,    // T
    '-',  // Y
    '-',  // U
    0,    // I
    '-',  // O
    '-',  // P
    0,  // A
    '.',  // S
    '.',  // D
    '-',  // F
    '.',  // G
    '.',  // H
    '-',  // J
    '-',  // K
    '.',  // L
    '.',  // Z
    '.',  // X
    '-',  // C
    '.',  // V
    '.',  // B
    0,    // N
    0,    // M

    '.', // ,
    '.', // .
    '.', // /
    '-'  // ?
};

const char fourthCodePart[40] = {
    '-', // 1
    '-', // 2
    '-', // 3
    '.', // 4
    '.', // 5
    '.', // 6
    '.', // 7
    '.', // 8
    '-', // 9
    '-', // 0

    '-',  // Q
    0,    // W
    0,    // E
    0,    // R
    0,    // T
    '-',  // Y
    0,    // U
    0,    // I
    0,    // O
    '.',  // P
    0,    // A
    0,    // S
    0,    // D
    '.',  // F
    0,    // G
    '.',  // H
    '-',  // J
    0,    // K
    '.',  // L
    '.',  // Z
    '-',  // X
    '.',  // C
    '-',  // V
    '.',  // B
    0,    // N
    0,    // M

    '.', // ,
    '-', // .
    '-', // /
    '-'  // ?
};

const char fifthCodePart[40] = {
    '-', // 1
    '-', // 2
    '-', // 3
    '-', // 4
    '.', // 5
    '.', // 6
    '.', // 7
    '.', // 8
    '.', // 9
    '-', // 0

    0,  // Q
    0,  // W
    0,  // E
    0,  // R
    0,  // T
    0,  // Y
    0,  // U
    0,  // I
    0,  // O
    0,  // P
    0,  // A
    0,  // S
    0,  // D
    0,  // F
    0,  // G
    0,  // H
    0,  // J
    0,  // K
    0,  // L
    0,  // Z
    0,  // X
    0,  // C
    0,  // V
    0,  // B
    0,  // N
    0,  // M

    '-', // ,
    '.', // .
    '.', // /
    '.'  // ?
};

const char sixthCodePart[40] = {
    0, // 1
    0, // 2
    0, // 3
    0, // 4
    0, // 5
    0, // 6
    0, // 7
    0, // 8
    0, // 9
    0, // 0

    0,  // Q
    0,  // W
    0,  // E
    0,  // R
    0,  // T
    0,  // Y
    0,  // U
    0,  // I
    0,  // O
    0,  // P
    0,  // A
    0,  // S
    0,  // D
    0,  // F
    0,  // G
    0,  // H
    0,  // J
    0,  // K
    0,  // L
    0,  // Z
    0,  // X
    0,  // C
    0,  // V
    0,  // B
    0,  // N
    0,  // M

    '-', // ,
    '-', // .
    0, // /
    '.'  // ?
};


// TODO: I could maybe optimise these to O(1) with a long switch case?
int getKochFromQwerty(int qwertyIndex) {
    for(int i = 0; i < 40; i++) {
        if (lettersKoch[i][0] == lettersQwerty[qwertyIndex][0])
            return i;
    }
    return NOT_LETTER;
}

int getQwertyFromKoch(int kochIndex){
    for(int i = 0; i < 40; i++) {
        if (lettersQwerty[i][0] == lettersKoch[kochIndex][0])
            return i;
    }
    return NOT_LETTER;
}

void LoadCustomOrder(void) {
    if (FileExists("CustomLetters.mrt")) {
        FILE *file = fopen("CustomLetters.mrt", "r");
        char letterBuffer[5] = {0};
        // Overwrite the Koch buffer
        for (int i = 0; i < 40; i++) {
            fgets(letterBuffer, 5, file);
            letterBuffer[1] = '\0';
            // printf("Buffer Read: %s\n", letterBuffer);
            // printf("lettersKoch[%d] was: %s\n", i, lettersKoch[i]);
            lettersKoch[i][0] = letterBuffer[0];
            // printf("lettersKoch[%d] is now: %s\n\n", i, lettersKoch[i]);
        }
        fclose(file);
    }
}
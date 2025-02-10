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
const char* lettersKoch[40] = {
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

// TODO: These are going to be tedious... 
// no, I will not use AI!!!!!!!!!
const char firstCodePart[40] = {
    '.',  // A
    '-',  // B
    '-',  // C
};

const char secondCodePart[40] = {};
const char thirdCodePart[40] = {};
const char fourthCodePart[40] = {};
const char fifthCodePart[40] = {};
const char sixthCodePart[40] = {};
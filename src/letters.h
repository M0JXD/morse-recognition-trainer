/* This header defines letters for printing */ 

#ifndef LETTERS_H
#define LETTERS_H

// Strings with all the letters
extern const char* letters_qwerty[40];
extern const char* letters_koch[40];

int getKochFromQwerty(int qwertyIndex);
int getQwertyFromKoch(int kochIndex);

#endif  // LETTERS_H

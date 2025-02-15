/* This header defines letters tables */ 

#ifndef LETTERS_H
#define LETTERS_H

#define NOT_LETTER 41

// Strings with all the letters
extern const char* lettersQwerty[40];
extern char lettersKoch[40][2];

/* These are in alignment with lettersQwerty.
 * Basically, each one returns the . or - for the character, then NULLs for unused characters
 *
 * e.g. for "F", which is "..-.":
 *   firstCodePart[23]  == '.'
 *   secondCodePart[23] == '.'
 *   thirdCodePart[23]  == '-'
 *   fourthCodePart[23] == '.'
 *   fifthCodePart[23]  == NULL
 *   sixthCodePart[23]  == NULL
 */
extern const char firstCodePart[40];
extern const char secondCodePart[40];
extern const char thirdCodePart[40];
extern const char fourthCodePart[40];
extern const char fifthCodePart[40];
extern const char sixthCodePart[40];

int getKochFromQwerty(int qwertyIndex);
int getQwertyFromKoch(int kochIndex);
void LoadCustomOrder(void);

#endif  // LETTERS_H

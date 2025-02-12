#include "raylib.h"
#include "rlgl.h"  // Needed to set line widths for functions like "DrawCircleOutline()"

#include "stdio.h"  // printf debugging
#include "ctype.h"  // for toupper
#include "string.h"

#include "letters.h"
#include "morse.h"
#include "lessons.h"
#include "game_save.h"

#define BUTTON_ROUNDNESS 0.4f
#define BUTTON_SEGMENTS 5.0f
#define FONT_SIZE 20

// These are needed all the time, I think it's fair they're global.
Sound dot;
Sound dash;
SaveState gameSave;

void SetTheme(Color *mainTheme, Color *oppositeMainTheme, Color *progressColour) {
    if (gameSave.theme) {
        *mainTheme = LIGHTGRAY;
        *oppositeMainTheme = BLACK;
        *progressColour = GREEN;
    } else {
        *mainTheme = DARKGRAY;
        *oppositeMainTheme = WHITE;
        *progressColour = VIOLET;
    }
}

//--------------------------------------------------------------------------------
// ENTRY
//--------------------------------------------------------------------------------
int main(void) {
    SetTraceLogLevel(LOG_NONE);
    puts("----- MORSE RECOGNITION TRAINER -----");
    InitWindow(640, 480, "Morse Recognition Trainer");
    SetTargetFPS(30);
    SetWindowMinSize(410, 300);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    Image icon = LoadImage("assets/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    InitAudioDevice();
    
    // Default line width is a bit thin.
    float defaultLineWidth = rlGetLineWidth();
    rlSetLineWidth(defaultLineWidth * 2.3);
    
    int layoutWidth = 10;
    int layoutHeight = 4;

    LoadData(&gameSave);
    SetWindowSize(gameSave.windowWidth, gameSave.windowLength);

    // Load morse sounds
    LoadMorseSounds();

    // Set up initial theme;
    Color mainTheme;
    Color oppositeMainTheme;
    Color progressColour;
    SetTheme(&mainTheme, &oppositeMainTheme, &progressColour);

    //--------------------------------------------------------------------------------
    // MAIN LOOP
    //--------------------------------------------------------------------------------
    bool inLesson = false;  // Is a lesson running
    while (!WindowShouldClose()) {
        //--------------------------------------------------------------------------------
        // LAYOUT ADAPTING
        //--------------------------------------------------------------------------------
        float width = GetScreenWidth();
        float height = GetScreenHeight();
        float circleSpaceX = width;
        float circleSpaceY = height - 30;  // Save space at the top for buttons
        float radius = 10.0f;
        int divisionsX, divisionsY;
        
        if (width > height) {
            // Normal Desktop Layout 10 x 4
            layoutWidth = 10; layoutHeight = 4;
            divisionsX = (3 * layoutWidth) + 1;
            divisionsY = (3 * layoutHeight) + 1;
            radius = (circleSpaceX / divisionsX);
            if (circleSpaceX > 3.6 * circleSpaceY) radius = 32;  // Edge case, ugly but prevents overlap
        } else {
            // Phone style layout 5 x 8
            layoutWidth = 5; layoutHeight = 8;
            divisionsX = (3 * layoutWidth) + 1;
            divisionsY = (3 * layoutHeight) + 1;
            radius = (circleSpaceY / divisionsY);
            if (circleSpaceY > 2.2 * circleSpaceX) radius = 28;  // Edge case, ugly but prevents overlap
        }

        float singleDivX = circleSpaceX / divisionsX;
        float singleDivY = circleSpaceY / divisionsY;
        if (height > width) singleDivY = circleSpaceY / divisionsY * 0.96;  // Save some space for status messages at bottom
        
        //--------------------------------------------------------------------------------
        // DRAWING & COLLISION
        //--------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(mainTheme);
            char string[40] = {0};  // This should always be enough. Not used as a user input path!
            
            // Top Buttons
            Rectangle LessonButton = { 10, 10, 80, 30 };
            inLesson ? DrawRectangleRounded(LessonButton, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, BLUE) 
                     : DrawRectangleRoundedLines(LessonButton, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, BLUE);
            DrawText("Lesson", 14, 15, FONT_SIZE, oppositeMainTheme);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), LessonButton)) {
                inLesson = !inLesson;
                SetLessonMode(inLesson);
                //printf("Lesson pressed, inLesson now = %d\n", inLesson);
            }
                
            Rectangle wpmButton = { width - 307, 10, 90 ,30 };
            DrawRectangleRoundedLines(wpmButton, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, RED);
            sprintf(string, "WPM: %d", gameSave.WPM);
            DrawText(string, width - 302, 15, FONT_SIZE, oppositeMainTheme);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), wpmButton)) {
                if (gameSave.WPM == 25) gameSave.WPM = 10; else gameSave.WPM += 5;
                LoadMorseSounds();
                // printf("WPM changed, is now = %d\n", gameSave.WPM);
            }

            Rectangle toneButton = { width - 205, 10, 110 ,30 };
            DrawRectangleRoundedLines(toneButton, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, GREEN);
            sprintf(string, "Tone: %d", gameSave.tone);
            DrawText(string, width - 200, 15, FONT_SIZE, oppositeMainTheme);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), toneButton)) {
                switch (gameSave.tone) {
                    case 650:
                        gameSave.tone = 700;
                        break;
                    case 700:
                        gameSave.tone = 800;
                        break;
                    case 800:
                        gameSave.tone = 650;
                        break;
                    default:
                        gameSave.tone = 700;
                        break;
                }
                LoadMorseSounds();
                // printf("Tone changed, is now = %d\n", gameSave.tone);
            }

            Rectangle switchThemeButton = { (width - 85), 10, 75, 30 };
            DrawRectangleRoundedLines(switchThemeButton, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, PURPLE);
            DrawText("Theme", width - 80, 15, 20, oppositeMainTheme);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), switchThemeButton)) {
                gameSave.theme = !gameSave.theme;
                SetTheme(&mainTheme, &oppositeMainTheme, &progressColour);
            }

            // Statusbar at bottom
            memset(string, 0, 40);
            inLesson ? GetLessonText(string) : GetMorseText(NOT_LETTER, string);     
            int centering = MeasureText(string, radius * 0.8) / 2;
            string[0] ? DrawText(string, (width / 2) - centering, height * 0.95, radius * 0.8, oppositeMainTheme) : 0;

            // This loops draws the main circles, but also does collision detection 
            for (int k = 0, y = 2; k < layoutHeight; k++, y += 3) {
                for (int i = 0, x = 2; i < layoutWidth;  i++, x += 3) {
                    int kochIndex = getKochFromQwerty(i + (k * layoutWidth)); 
                    Vector2 circleCentre = {x * singleDivX, (y * singleDivY) + 30};

                    // Draw progress first so lines are clear on top
                    if (gameSave.activatedLetters[kochIndex]) {
                        DrawCircleV(circleCentre, radius * 0.6, progressColour);
                    }

                    if (gameSave.levels[kochIndex] && gameSave.activatedLetters[kochIndex]) {
                        DrawRing(circleCentre, radius * 0.6, radius, -90, 
                                ((gameSave.levels[kochIndex]) * (360 / 8)) - 90,
                                20, progressColour
                        );
                    }

                    // Outer Circle & Smaller inner circle 
                    DrawCircleLinesV(circleCentre, radius, oppositeMainTheme);
                    DrawCircleLinesV(circleCentre, radius * 0.6, oppositeMainTheme);

                    // Add lines for the segments
                    DrawLine(circleCentre.x, circleCentre.y + radius * 0.6, 
                             circleCentre.x, circleCentre.y + radius, oppositeMainTheme);

                    DrawLine(circleCentre.x, circleCentre.y - radius * 0.6, 
                             circleCentre.x, circleCentre.y - radius, oppositeMainTheme);

                    DrawLine(circleCentre.x + radius * 0.6, circleCentre.y, 
                             circleCentre.x + radius, circleCentre.y, oppositeMainTheme);

                    DrawLine(circleCentre.x - radius * 0.6, circleCentre.y,
                             circleCentre.x - radius, circleCentre.y, oppositeMainTheme);

                    // sin(45) = 0.707
                    DrawLine(circleCentre.x + (radius * 0.6) * 0.707, circleCentre.y + (radius * 0.6) * 0.707, 
                             circleCentre.x + radius * 0.707, circleCentre.y + radius * 0.707, oppositeMainTheme);
   
                    DrawLine(circleCentre.x - (radius * 0.6) * 0.707, circleCentre.y + (radius * 0.6) * 0.707, 
                             circleCentre.x - radius * 0.707, circleCentre.y + radius * 0.707, oppositeMainTheme);

                    DrawLine(circleCentre.x - (radius * 0.6) * 0.707, circleCentre.y - (radius * 0.6) * 0.707, 
                             circleCentre.x - radius * 0.707, circleCentre.y - radius * 0.707, oppositeMainTheme);

                    DrawLine(circleCentre.x + (radius * 0.6) * 0.707, circleCentre.y - (radius * 0.6) * 0.707, 
                             circleCentre.x + radius * 0.707, circleCentre.y - radius * 0.707, oppositeMainTheme);

                    // Used for centering the letters in each circle
                    Vector2 offsets = MeasureTextEx(
                        GetFontDefault(),
                        lettersQwerty[i + (k * layoutWidth)],
                        radius * 0.9,
                        2  // Is the default in rText.C I think this is an unused parameter 
                    );  // TODO: Double check and issue report to raylib
                    
                    // Letter in circle
                    DrawText(
                        lettersQwerty[i + (k * layoutWidth)], 
                        circleCentre.x - (offsets.x / 2), 
                        circleCentre.y - (offsets.y / 2), 
                        radius * 0.9,
                        oppositeMainTheme
                    );
                    
                    //--------------------------------------------------------------------------------
                    // Detection
                    //--------------------------------------------------------------------------------
                    int wasDetected = NOT_LETTER;
                    // Check if one was clicked by the mouse
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(circleCentre, GetMousePosition(), radius)) {  
                            wasDetected = i + (k * layoutWidth);
                    } else {  // Check if it was typed
                        char pressed[2] = "\0"; 
                        pressed[0] = toupper(GetCharPressed());
                        if(pressed[0]) {
                            // Sets wasDetected to the letter pressed
                            for (wasDetected = 0; wasDetected < 40; wasDetected++) {
                                if (lettersQwerty[wasDetected][0] == pressed[0]) { break; }
                            }
                        }
                    }
                    // Do something if it's been clicked/typed
                    if (wasDetected < 40) {
                        printf("Pressed %s\n", lettersQwerty[wasDetected]);
                        inLesson ? UpdateLesson(wasDetected) : PlayMorse(wasDetected);
                        // UpdateLesson(wasDetected);
                    }
                }
            }
        EndDrawing();
        PlayMorse(NOT_LETTER);
        //--------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------
    // Save and De-initialise
    //--------------------------------------------------------------------------------
    // SaveData(&gameSave);
    UnloadSound(dot);
    UnloadSound(dash);
    CloseWindow();
    return 0;
}

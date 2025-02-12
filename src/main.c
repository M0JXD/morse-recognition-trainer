#include "raylib.h"
#include "rlgl.h"  // Needed to set line widths for functions like "DrawCircleOutline()"

#include "stdio.h"  // printf debugging
#include "ctype.h"  // for toupper

#include "letters.h"
#include "morse.h"
#include "lessons.h"
#include "game_save.h"

// These are needed all the time, I think it's fair they're global.
Sound dot;
Sound dash;
SaveState gameSave;

//--------------------------------------------------------------------------------
// ENTRY
//--------------------------------------------------------------------------------
int main(void) {
    SetTraceLogLevel(LOG_NONE);
    puts("----- MORSE RECOGNITION TRAINER -----");
    InitWindow(640, 480, "Morse Recognition Trainer");
    SetTargetFPS(30);
    SetWindowMinSize(300, 300);
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
    char dotPath[32];
    sprintf(dotPath, "assets/%dWPM_%dHZ_DOT.wav", gameSave.WPM, gameSave.tone);
    char dashPath[34];
    sprintf(dashPath, "assets/%dWPM_%dHZ_DASH.wav", gameSave.WPM, gameSave.tone);

    printf("Loading tones for %dWPM %dHz.\n", gameSave.WPM, gameSave.tone);

    dot = LoadSound(dotPath);
    dash = LoadSound(dashPath);

    //--------------------------------------------------------------------------------
    // MAIN LOOP
    //--------------------------------------------------------------------------------
    bool inLesson = false;  // Is a lesson running
    while (!WindowShouldClose()) {
        //--------------------------------------------------------------------------------
        // THEME
        //--------------------------------------------------------------------------------
        Color mainTheme;
        Color oppositeMainTheme;

        if (gameSave.theme) {
            mainTheme = LIGHTGRAY;
            oppositeMainTheme = BLACK;
        } else {
            mainTheme = DARKGRAY;
            oppositeMainTheme = WHITE;
        }

        //--------------------------------------------------------------------------------
        // LAYOUT ADAPTING
        //--------------------------------------------------------------------------------
        float width = GetScreenWidth();
        float height = GetScreenHeight();
        float circleSpaceX = width;
        float circleSpaceY = height - 30;  // Save space at the top for buttons
        float radius = 10.0f;
        int divisionsX;
        int divisionsY;
        
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
            if (circleSpaceY > 2.2 * circleSpaceX) radius = 24;  // Edge case, ugly but prevents overlap
        }
        
        float singleDivX = circleSpaceX / divisionsX;
        float singleDivY = circleSpaceY / divisionsY;
        
        //--------------------------------------------------------------------------------
        // DRAWING & COLLISION
        //--------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(mainTheme);
            // DrawLine(0, 50, width, 50, BLACK);  // Split the screen into buttons and circles sections
            
            // Top Buttons
            Rectangle LessonButton = { 10, 10, 80, 30 };
            inLesson ? DrawRectangleRounded(LessonButton, 0.4f, 10.0f, BLUE) : DrawRectangleRoundedLines(LessonButton, 0.4f, 10.0f, BLUE);
            DrawText("Lesson", 14, 15, 20, oppositeMainTheme);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), LessonButton)) {
                inLesson = !inLesson;
                printf("Lesson Pressed, inLesson = %d\n", inLesson);  // StartLesson();
            }
                
            
            // TODO: WPM & Tone Settings, Save/Load buttons

            Rectangle switchThemeButton = { (width - 85), 10, 75, 30 };
            DrawRectangleRounded(switchThemeButton, 0.4f, 0.0f, PURPLE);
            DrawText("Theme", width - 80, 15, 20, oppositeMainTheme);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), switchThemeButton)) 
                gameSave.theme = !gameSave.theme;

            // TODO: Statusbar at bottom
            if (inLesson) {

            } else {
                char string[40] = {0};  // This should always be enough. Not a user input path!
                GetMorseText(NOT_LETTER, string); 
                //printf("String is %s\n", string);
                int centering = MeasureText(string, radius * 0.8) / 2;
                string[0] ? DrawText(string, (width / 2) - centering, height * 0.95, radius * 0.8, oppositeMainTheme) : 0;
            }

            // This loops draws the main circles, but also does collision detection 
            for (int k = 0, y = 2; k < layoutHeight; k++, y += 3) {
                for (int i = 0, x = 2; i < layoutWidth;  i++, x += 3) {

                    // Outer Circle
                    Vector2 circleCentre = {x * singleDivX, (y * singleDivY) + 30};
                    DrawCircleLinesV(circleCentre, radius, oppositeMainTheme);

                    // Smaller inner circle  // TODO: Fill when activated by lesson
                    DrawCircleLinesV(circleCentre, radius * 0.6, oppositeMainTheme);

                    // Fill with ring as per progress
                    // DrawRing();

                    // Add 8 lines for the segments
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
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {  // Check if one was clicked by the mouse
                        if (CheckCollisionPointCircle(circleCentre, GetMousePosition(), radius)) {
                            wasDetected = i + (k * layoutWidth);
                        }
                    } else {  // Check if it was typed
                        char pressed[2] = "\0"; 
                        pressed[0] = toupper(GetCharPressed());
                        if(pressed[0]) {
                            for (wasDetected = 0; wasDetected < 40; wasDetected++) {
                                if (lettersQwerty[wasDetected][0] == pressed[0]) { break; }
                            }
                        }
                    }
                    // Do something if it's been clicked/typed
                    if (wasDetected < 40) {
                        printf("Pressed %s\n", lettersQwerty[wasDetected]);
                        PlayMorse(wasDetected);
                        // UpdateLesson(wasDetected);
                    }
                }
            }
        EndDrawing();
        PlayMorse(NOT_LETTER);
        //--------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------
    // De-initialise
    //--------------------------------------------------------------------------------
    EndLesson(1); // If we reach here we should stop the lesson and save!
    UnloadSound(dot);
    UnloadSound(dash);
    CloseWindow();
    return 0;
}

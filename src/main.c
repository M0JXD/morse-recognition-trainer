#include "raylib.h"
#include "stdio.h"  // printf debugging
#include "ctype.h"  // for toupper
#include "rlgl.h"  // Needed to set line widths for functions like "DrawCircleOutline()"

#include "letters.h"
#include "morse.h"

Wave dot;
Wave dash;

//--------------------------------------------------------------------------------
// ENTRY
//--------------------------------------------------------------------------------
int main(void) {
    InitWindow(640, 480, "Morse Recognition Trainer");
    SetTargetFPS(60);
    SetWindowMinSize(400, 300);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    
    // Default line width is a bit thin.
    float defaultLineWidth = rlGetLineWidth();
    rlSetLineWidth(defaultLineWidth * 2.3);
    
    int layoutWidth = 10;
    int layoutHeight = 4;
    int whatTheme = 1;

    // Initialise the dot and dash Waves
    

    // TODO: Load game save and generate waves for Morse
    // Maybe I need a loading screen for when it generates?

    //--------------------------------------------------------------------------------
    // MAIN LOOP
    //--------------------------------------------------------------------------------
    while (!WindowShouldClose()) {
        float width = GetScreenWidth();
        float height = GetScreenHeight();
        Color mainTheme;
        Color oppositeMainTheme;

        if (whatTheme) {
            mainTheme = LIGHTGRAY;
            oppositeMainTheme = BLACK;
        } else {
            mainTheme = DARKGRAY;
            oppositeMainTheme = WHITE;
        }

        //--------------------------------------------------------------------------------
        // LAYOUT ADAPTING
        //--------------------------------------------------------------------------------
        float circleSpaceX = width;
        float circleSpaceY = height - 50;  // Save space at the top for buttons
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
            if (circleSpaceY > 3.6 * circleSpaceX) radius = 32;  // Edge case, ugly but prevents overlap
        }
        
        float singleDivX = circleSpaceX / divisionsX;
        float singleDivY = circleSpaceY / divisionsY;
        
        //--------------------------------------------------------------------------------
        // DRAWING & COLLISION
        //--------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(mainTheme);
            DrawLine(0, 50, width, 50, BLACK);  // Split the screen into buttons and circles sections
            
            // Top Buttons
            Rectangle startLessonButton = { 10, 10, 180, 30 };
            DrawRectangleRoundedLines(startLessonButton, 0.4f, 0.0f, BLUE);
            DrawText("Start Lesson", 32, 15, 20, oppositeMainTheme);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), startLessonButton))
                ;
            
            // TODO: WPM & Tone Settings

            Rectangle switchThemeButton = { (width - 85), 10, 75, 30 };
            DrawRectangleRoundedLines(switchThemeButton, 0.4f, 0.0f, PURPLE);
            DrawText("Theme", width - 80, 15, 20, oppositeMainTheme);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), switchThemeButton)) 
                whatTheme = !whatTheme;

            // This loops draws the main circles, but also does collision detection 
            // TODO: Improve this now that top bar is constant size.
            for (int k = 0, y = 2; k < layoutHeight; k++, y += 3) {
                for (int i = 0, x = 2; i < layoutWidth;  i++, x += 3) {
                    // TODO: Add animation to the circle that is playing

                    // Outer Circle
                    Vector2 circleCentre = {x * singleDivX, (y * singleDivY) + 50};
                    DrawCircleLinesV(circleCentre, radius, oppositeMainTheme);

                    // Smaller inner circle
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
                        letters_qwerty[i + (k * layoutWidth)],
                        radius * 0.9,
                        2  // Is the default in rText.C I think this is an unused parameter 
                    );  // TODO: Double check and issue report to raylib
                    
                    // Letter in circle
                    DrawText(
                        letters_qwerty[i + (k * layoutWidth)], 
                        circleCentre.x - (offsets.x / 2) + 1, 
                        circleCentre.y - (offsets.y / 2) + 1, 
                        radius * 0.9,
                        oppositeMainTheme
                    );
                    
                    //--------------------------------------------------------------------------------
                    // Detection
                    //--------------------------------------------------------------------------------
                    int wasDetected = 41;
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {  // Check if one was clicked by the mouse
                        if (CheckCollisionPointCircle(circleCentre, GetMousePosition(), radius)) {
                            wasDetected = i + (k * layoutWidth);
                        }
                    } else {  // Check if it was typed
                        char pressed[2] = "\0"; 
                        pressed[0] = toupper(GetCharPressed());
                        if(pressed[0]) {
                            for (wasDetected = 0; wasDetected < 40; wasDetected++) {
                                if (letters_qwerty[wasDetected][0] == pressed[0]) { break; }
                            }
                        }
                    }
                    // Do something if it's been clicked/typed
                    if (wasDetected < 40) {
                        printf("Pressed %s\n", letters_qwerty[wasDetected]);
                        //playMorse(wasDetected);
                    }   
                }
            }
        EndDrawing();
        //--------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------
    // De-initialise
    //--------------------------------------------------------------------------------
    
    CloseWindow();
    return 0;
}

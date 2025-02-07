#include "stdio.h"

#include "raylib.h"
#include "rlgl.h"  // Needed to set line widths for functions like "DrawCircleOutline()"

#include "letters.h"
#include "morse.h"

int layoutWidth = 10;
int layoutHeight = 4;

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
    rlSetLineWidth(defaultLineWidth * 3);
    
    int layoutWidth = 10;
    int layoutHeight = 4;
    
    bool wasKeyPress = false;
    int keyPressed = KEY_A;
    int whatTheme = 1;
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
        float circleSpaceY = height * 0.9;  // Save space at the top for buttons
        float radius = 10.0f;
        int divisionsX;
        int divisionsY;
        
        if (width > height) {
            // Normal Desktop Layout 10 x 4
            layoutWidth = 10;
            layoutHeight = 4;
            divisionsX = (3 * layoutWidth) + 1;
            divisionsY = (3 * layoutHeight) + 1;
            radius = (circleSpaceX / divisionsX);
            if (circleSpaceX > 3.6 * circleSpaceY) radius = 32;  // Edge case, ugly but prevents overlap
        } else {
            // Phone style layout 5 x 8
            layoutWidth = 5;
            layoutHeight = 8;
            divisionsX = (3 * layoutWidth) + 1;
            divisionsY = (3 * layoutHeight) + 1;
            radius = (circleSpaceY / divisionsY);
        }
        
        float singleDivX = circleSpaceX / divisionsX;
        float singleDivY = circleSpaceY / divisionsY;
        
        //--------------------------------------------------------------------------------
        // DRAWING, CHECKING, PLAYING
        //--------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(mainTheme);
            
            // Split the screen into buttons and circles sections
            DrawLine(0, 50, width, 50, BLACK);
            
            // Draw Buttons
            Rectangle startLessonButton = { 10, 10, 180, 30 };
            DrawRectangleRoundedLines(startLessonButton, 0.4f, 0.0f, BLUE);
            DrawText("Start Lesson", 32, 15, 20, oppositeMainTheme);
            
            Rectangle switchThemeButton = { (width - 190), 10, 180, 30 };
            DrawRectangleRoundedLines(switchThemeButton, 0.4f, 0.0f, PURPLE);
            DrawText("Switch Theme", width - 167, 15, 20, oppositeMainTheme);

            // Detect Buttons
            CheckCollisionPointRec(GetMousePosition(), startLessonButton);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), switchThemeButton)) whatTheme = !whatTheme;


            // This loops draws the main circles, but also does collision detection 
            for (int k = 0, y = 2; k < layoutHeight; k++, y += 3) {
                for (int i = 0, x = 2; i < layoutWidth;  i++, x += 3) {
                
                    Vector2 circleCentre = {x * singleDivX, y * singleDivY + (height * 0.1)};

                    //--------------------------------------------------------------------------------
                    // Drawing parts
                    //--------------------------------------------------------------------------------
                    DrawCircleLinesV(circleCentre, radius, oppositeMainTheme);
                    
                    // Used for Centering the letters in each circle
                    Vector2 offsets = MeasureTextEx(
                        GetFontDefault(),
                        letters[i + (k * layoutWidth)],
                        radius,
                        2  // Is the default in rText.C I think this is an unused parameter 
                    );  // TODO: Check and issue report to raylib
                    
                    DrawText(
                        letters[i + (k * layoutWidth)], 
                        x * singleDivX - (offsets.x / 2), 
                        y * singleDivY + (height * 0.105) - (offsets.y / 2), 
                        radius,
                        oppositeMainTheme
                    );
                    
                    //--------------------------------------------------------------------------------
                    // Detection
                    //--------------------------------------------------------------------------------
                    int wasDetected = 41;
                    // Check if one was clicked by the mouse
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        if (CheckCollisionPointCircle(circleCentre, GetMousePosition(), radius)) {
                            wasDetected = i + (k * layoutWidth);
                        }
                    } else {  // Check if it was typed
                        
                    }             
                    // Check if it was typed
                    if (wasDetected < 40) {
                        printf("Pressed %s\n", letters[wasDetected]);
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

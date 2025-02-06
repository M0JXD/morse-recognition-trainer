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
    //--------------------------------------------------------------------------------
    // MAIN LOOP
    //--------------------------------------------------------------------------------
    while (!WindowShouldClose()) {
    
        //--------------------------------------------------------------------------------
        // LAYOUT ADAPTING
        //--------------------------------------------------------------------------------
        
        float circleSpaceX = GetScreenWidth();
        float circleSpaceY = GetScreenHeight() * 0.9;  // Save space at the top for buttons
        float radius = 10.0f;
        int divisionsX;
        int divisionsY;
        
        if (GetScreenWidth() > GetScreenHeight()) {
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
            ClearBackground(LIGHTGRAY);
            
            // Split the screen into buttons and circles sections
            DrawLine(
                0, 
                (GetScreenHeight() * 0.1), 
                GetScreenWidth(),
                (GetScreenHeight() * 0.1), 
                BLACK
            );
            
            // TODO: Draw Buttons
            Rectangle startButton = { 10, 10, GetScreenWidth() / 4, GetScreenHeight() * 0.05 };
            DrawRectangleRoundedLines(startButton, 3, 0.0f, BLUE);
            //DrawText()
            
            // This loops draws the main circles, but also does collision detection 
            for (int k = 0, y = 2; k < layoutHeight; k++, y += 3) {
                for (int i = 0, x = 2; i < layoutWidth;  i++, x += 3) {
                
                    Vector2 circleCentre = {x * singleDivX, y * singleDivY + (GetScreenHeight() * 0.1)};

                    //--------------------------------------------------------------------------------
                    // Drawing parts
                    //--------------------------------------------------------------------------------
                    DrawCircleLinesV(
                        circleCentre,
                        radius,
                        BLACK
                    );
                    
                    // Used for Centering the letters in each circle
                    Vector2 offsets = MeasureTextEx(
                        GetFontDefault(),
                        letters[i + (k * layoutWidth)],
                        radius,
                        2  // Is set to to by default in rText.C I think this is an unused parameter TODO: Check and issue report
                    );
                    
                    DrawText(
                        letters[i + (k * layoutWidth)], 
                        x * singleDivX - (offsets.x / 2), 
                        y * singleDivY + (GetScreenHeight() * 0.105) - (offsets.y / 2), 
                        radius,
                        BLACK
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

#include "raylib.h"
#include "rlgl.h"  // Needed to set line widths for functions like "DrawCircleOutline()"

#include "letters.h"

int layout_width = 10;
int layout_height = 4;

//--------------------------------------------------------------------------------
// ENTRY
//--------------------------------------------------------------------------------
int main(void) {
    const int screenWidth = 400;
    const int screenHeight = 300;
    int layout_width = 10;
    int layout_height = 4;
    
    InitWindow(640, 480, "Morse Recognition Trainer");
    SetTargetFPS(18);
    SetWindowMinSize(screenWidth, screenHeight);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    
    float defaultLineWidth = rlGetLineWidth();
    rlSetLineWidth(defaultLineWidth * 3);
    
    
    //--------------------------------------------------------------------------------
    // MAIN LOOP
    //--------------------------------------------------------------------------------
    while (!WindowShouldClose()) {
    
        //--------------------------------------------------------------------------------
        // LAYOUT ADAPTING
        //--------------------------------------------------------------------------------
        
        float circle_space_x = GetScreenWidth();
        float circle_space_y = GetScreenHeight() * 0.9;  // Save space at the top for buttons
        float radius = 10.0f;
    
        int x_divisions;
        int y_divisions;
        
        //  y = -0.8x + 12 therefore y = (-4x + 60) / 5, see LAYOUT_HGT
        if (GetScreenWidth() > GetScreenHeight()) {
            // Normal Desktop Layout 10 x 4
            layout_width = 10;
            layout_height = 4;
            x_divisions = (3 * layout_width) + 1;
            y_divisions = (3 * layout_height) + 1;
            radius = (circle_space_x / x_divisions);
            if (circle_space_x > 3.6 * circle_space_y) radius = 32;  // Edge case, ugly but prevents overlap
        } else {
            // Phone style layout 5 x 8
            layout_width = 5;
            layout_height = 8;
            x_divisions = (3 * layout_width) + 1;
            y_divisions = (3 * layout_height) + 1;
            radius = (circle_space_y / y_divisions);
        }
        
        float single_x_div = circle_space_x / x_divisions;
        float single_y_div = circle_space_y / y_divisions;
        
        //--------------------------------------------------------------------------------
        // KEY CHECKING
        //--------------------------------------------------------------------------------
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if CheckCollisionPointCircle(Vector2 point, Vector2 center, radius)
        }
        
        if ()
   
        //--------------------------------------------------------------------------------
        // DRAWING
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
            
            // Draw Buttons
            
            // Draw Circles with text in them
            for (int k = 0, y = 2; k < layout_height; k++, y += 3) {
                for (int i = 0, x = 2; i < layout_width;  i++, x += 3) {
                    DrawCircleLines(
                        x * single_x_div,
                        y * single_y_div + (GetScreenHeight() * 0.1),
                        radius,
                        BLACK
                    );
                    
                    DrawText(
                        letters[i + (k * layout_width)], 
                        x * single_x_div - radius / 4.7, 
                        y * single_y_div + (GetScreenHeight() * 0.1) - radius / 2.2, 
                        radius, 
                        BLACK
                    );
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

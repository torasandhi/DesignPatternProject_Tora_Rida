#include <raylib.h>
#include "ball.h"

int main() 
{
    const Color backgroundColor = {20, 160, 133, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    
    //initialize window size & set target FPS
    InitWindow(screenWidth, screenHeight, "Design Pattern Project Tora & Rida");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
            ClearBackground(backgroundColor);



            EndDrawing();
    }
    
    CloseWindow();
}
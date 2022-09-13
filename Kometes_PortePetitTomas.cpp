#include "raylib.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.0");

    SetTargetFPS(60);               
    while (!WindowShouldClose()) 
    {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Congrats! You created your first window!", 190, 200, 20, WHITE);

        EndDrawing();
        
    }

   
    CloseWindow();        

}

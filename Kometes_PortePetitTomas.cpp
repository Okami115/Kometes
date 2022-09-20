#include "raylib.h"

int main()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.0");

    Vector2 v1 = { screenWidth / 2, 0 };
    Vector2 v2 = { 0 ,0 };
    Vector2 v3 = { screenWidth, screenHeight};

    Rectangle Rec1 = { screenWidth / 2, screenHeight / 2, 300, 300 };
    Vector2 Origin = { Rec1.width / 2, Rec1.height / 2 };

    int rotated = 0;
    SetTargetFPS(60);               
    while (!WindowShouldClose()) 
    {
        rotated = rotated + 1;

        BeginDrawing();

        ClearBackground(BLACK);

        //DrawTriangle(v1, v2, v3, WHITE);
        DrawRectanglePro(Rec1, Origin, rotated, ORANGE);

        EndDrawing();
        
    }

   
    CloseWindow();        

}

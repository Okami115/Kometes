#include "raylib.h"

namespace OkamiIndustries
{

    void MoveSpaceShip(Rectangle& SpaceShip)
    {
        Vector2 Cursor = GetMousePosition();

        Vector2 Dif;

        Dif.x = SpaceShip.x - Cursor.x;
        Dif.y = SpaceShip.y - Cursor.y;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            SpaceShip.x -= Dif.x * GetFrameTime();
            SpaceShip.y -= Dif.y * GetFrameTime();
        }

    }

    int main()
    {
        const int screenWidth = 1920;
        const int screenHeight = 1080;

        InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.05");

        Vector2 v1 = { screenWidth / 2, 0 };
        Vector2 v2 = { 0 ,0 };
        Vector2 v3 = { screenWidth, screenHeight};

        Rectangle Rec1 = { screenWidth / 2, screenHeight / 2, 30, 30 };

        Vector2 Origin = { Rec1.width / 2, Rec1.height / 2 };

        int rotated = 0;
        SetTargetFPS(60); 

        while (!WindowShouldClose()) 
        {
            MoveSpaceShip(Rec1);

            BeginDrawing();

            ClearBackground(BLACK);
            DrawRectanglePro(Rec1, Origin, rotated, ORANGE);

            EndDrawing();
        }

        CloseWindow();        
    }

}
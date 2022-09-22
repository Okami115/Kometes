#include "raylib.h"
#include "raymath.h"
#include "SpaceShip.h"
#include "GameLoop.h"

namespace OkamiIndustries
{
    void gameloop()
    {
        const int screenWidth = 1920;
        const int screenHeight = 1080;

        InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.10");

        Texture2D SpaceShip = LoadTexture("assets/SpaceShip.png");

        Vector2 OriginSpaceShip = { SpaceShip.width / 2, SpaceShip.height / 2 };
        Vector2 shipPosition = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
        Rectangle shipRectangle = { 0, 0, SpaceShip.width, SpaceShip.height };

        SetTargetFPS(60);

        while (!WindowShouldClose())
        {

            MoveSpaceShip(shipPosition);

            BeginDrawing();
            ClearBackground(BLACK);

            DrawSpaceShip(shipRectangle, OriginSpaceShip, shipPosition, SpaceShip);

            EndDrawing();
        }

        UnloadTexture(SpaceShip);
        CloseWindow();


    }

}

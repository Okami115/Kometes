#include "raylib.h"
#include "raymath.h"
#include "SpaceShip.h"
#include "Comets.h"
#include "GameLoop.h"
#include <iostream> 
#include <time.h> 

namespace OkamiIndustries
{
    void gameloop()
    {
        const int screenWidth = 1920;
        const int screenHeight = 1080;

        srand(time(NULL));

        InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.10");

        Texture2D SpaceShip = LoadTexture("assets/SpaceShip.png");

        Vector2 OriginSpaceShip = { SpaceShip.width / 2, SpaceShip.height / 2 };
        Vector2 shipPosition = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
        Rectangle shipRectangle = { 0, 0, SpaceShip.width, SpaceShip.height };

        Circle Comets;
        Circle SpaceShipColider;

        spawnComets(Comets);

        SetTargetFPS(60);

        while (!WindowShouldClose())
        {

            MoveSpaceShip(shipPosition);

            MoveComets(Comets);
            
            BeginDrawing();
            ClearBackground(BLACK);

            DrawSpaceShip(shipRectangle, OriginSpaceShip, shipPosition, SpaceShip, SpaceShipColider, Comets);

            DrawComets(Comets);
            
            

            EndDrawing();
        }

        UnloadTexture(SpaceShip);
        CloseWindow();


    }

}

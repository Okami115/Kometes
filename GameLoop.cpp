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

        InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.14");

        Texture2D SpaceShip = LoadTexture("assets/SpaceShip.png");

        Texture2D Background = LoadTexture("assets/Background.png");
        Vector2 BackgroudPosition = { 0, 0 };

        Vector2 OriginSpaceShip = { SpaceShip.width / 2, SpaceShip.height / 2 };
        Vector2 shipPosition = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
        Rectangle shipRectangle = { 0, 0, SpaceShip.width, SpaceShip.height };

        Circle Comets;
        Circle SpaceShipColider;

        spawnComets(Comets);
        Texture2D SmallComets = LoadTexture("assets/Comets Small.png");
        Vector2 CometsPositionCenter = { Comets.Position.x + Comets.Radius / 2, Comets.Position.y + Comets.Radius / 2 };

        extern const int maxArmmo;
        extern Circle bullet[100];

        inicializedBullets();

        SetTargetFPS(60);

        while (!WindowShouldClose())
        {
            CometsPositionCenter = { Comets.Position.x + Comets.Radius, Comets.Position.y };

            MoveSpaceShip(shipPosition);

            MoveComets(Comets);
            
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureEx(Background, BackgroudPosition, 0, 1, WHITE);

            DrawSpaceShip(shipRectangle, OriginSpaceShip, shipPosition, SpaceShip, SpaceShipColider, Comets);

            DrawTextureEx(SmallComets, CometsPositionCenter, 140, 1, WHITE);
            
            DrawBullets();

            EndDrawing();
        }

        UnloadTexture(SpaceShip);
        CloseWindow();


    }

}

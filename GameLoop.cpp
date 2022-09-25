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
        SpaceShip.width = SpaceShip.width / 2;
        SpaceShip.height = SpaceShip.height / 2;

        Texture2D Background = LoadTexture("assets/Background.png");
        Vector2 BackgroudPosition = { 0, 0 };

        Vector2 OriginSpaceShip = { SpaceShip.width / 2, SpaceShip.height / 2 };
        Vector2 shipPosition = { GetScreenWidth() / 2, GetScreenHeight() / 2 };
        Rectangle shipRectangle = { 0, 0, SpaceShip.width, SpaceShip.height };

        Circle SpaceShipColider;

        spawnComets();
        Texture2D SmallComets = LoadTexture("assets/Comets Small.png");

        extern const int maxArmmo;
        extern Circle bullet[100];

        extern Circle comets[10];

        inicializedBullets();

        while (!WindowShouldClose())
        {

            MoveSpaceShip(shipPosition);

            MoveComets();

            BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureEx(Background, BackgroudPosition, 0, 1, WHITE);

            for (int i = 0; i < 10; i++)
            {

                DrawSpaceShip(shipRectangle, OriginSpaceShip, shipPosition, SpaceShip, SpaceShipColider, comets[i]);
            }

            DrawComets(SmallComets);
            
            DrawBullets();

            EndDrawing();
        }

        UnloadTexture(SpaceShip);
        UnloadTexture(Background);
        UnloadTexture(SmallComets);
        CloseWindow();


    }

}

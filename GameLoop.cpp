#include "raylib.h"
#include "raymath.h"
#include "SpaceShip.h"
#include "Comets.h"
#include "GameLoop.h"
#include <iostream> 
#include <time.h> 
#include "menu.h"

namespace OkamiIndustries
{
    void gameloop()
    {
        const int screenWidth = 1920;
        const int screenHeight = 1080;

        SetRandomSeed(NULL);

        InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.22");

        InitAudioDevice();

        Sound Shoot = LoadSound("assets/Shoot.wav");
        Sound Boom = LoadSound("assets/boom.wav");
        Sound Hit = LoadSound("assets/Hit.wav");

        Texture2D SpaceShip = LoadTexture("assets/SpaceShip.png");
        SpaceShip.width = SpaceShip.width / 2;
        SpaceShip.height = SpaceShip.height / 2;

        Texture2D Background = LoadTexture("assets/Background.png");
        Vector2 BackgroudPosition = { 0, 0 };

        spawnComets();
        spawnShip();
        Texture2D SmallComets = LoadTexture("assets/Comets Small.png");
        Texture2D MidComets = LoadTexture("assets/Mid Comets.png");
        Texture2D BigComets = LoadTexture("assets/Big Comets.png");

        extern int asteroidsCounter;

        //int selectMenu = 0;
        //int setLoop = 0;

        initBullets();

        while (!WindowShouldClose())
        {

            //LoopMenu(selectMenu, setLoop);

            MoveSpaceShip(Shoot, Hit);

            MoveComets(Boom);

            BeginDrawing();

            ClearBackground(BLACK);
            //DrawMenu(selectMenu);

            DrawTextureEx(Background, BackgroudPosition, 0, 1, WHITE);

            DrawSpaceShip(SpaceShip);
            
            DrawComets(SmallComets,MidComets, BigComets);
            
            DrawBullets();

            DrawText(TextFormat("Counter %i", asteroidsCounter), 100, 100, 20, WHITE);

            EndDrawing();
        }

        UnloadTexture(SpaceShip);
        UnloadTexture(Background);
        UnloadTexture(SmallComets);
        UnloadTexture(MidComets);
        UnloadTexture(BigComets);
        UnloadSound(Boom); 
        UnloadSound(Shoot);
        UnloadSound(Hit);

        CloseAudioDevice();
        CloseWindow();
    }
}

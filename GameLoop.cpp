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
    extern int asteroidsCounter;
    extern int ShootInpact;
    extern int totalShoots;
    extern int lives;
    extern int score;

    int accurancy = 1;

    Rectangle bannerRec = { static_cast <float>(GetScreenWidth()) / 2, 20, 1000, 50};
    Vector2 bannerPos = { bannerRec.x, bannerRec.y };

    void gameloop(Sound Hit, Sound Shoot, Sound boom)
    {
        MoveSpaceShip(Shoot, Hit);
        accurancy = (ShootInpact * 100) / totalShoots;
        MoveComets(boom);
    }

    void DrawGame(Texture2D Background, Vector2 BackgroudPosition, Texture2D SpaceShip, Texture2D SmallComets, Texture2D MidComets, Texture2D BigComets, Texture2D banner)
    {
        DrawTextureEx(Background, BackgroudPosition, 0, 1, WHITE);

        DrawSpaceShip(SpaceShip);

        DrawComets(SmallComets, MidComets, BigComets);

        DrawBullets();

        DrawTextureEx(banner,bannerPos, 0, 1, WHITE);
        DrawText(TextFormat("Asteroids Counter: %i", asteroidsCounter), GetScreenWidth() - 300, 35, 20, BLACK);
        DrawText(TextFormat("Accurancy: %i", accurancy), 300, 35, 20, BLACK);
        DrawText(TextFormat("Lives: %i", lives), 500, 35, 20, BLACK);
        DrawText(TextFormat("Score: %i", score * 100), 100, 35, 20, BLACK);
    }
}

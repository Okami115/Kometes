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
    void gameloop(Sound Hit, Sound Shoot, Sound boom)
    {
        MoveSpaceShip(Shoot, Hit);

        MoveComets(boom);
    }

    void DrawGame(Texture2D Background, Vector2 BackgroudPosition, Texture2D SpaceShip, Texture2D SmallComets, Texture2D MidComets, Texture2D BigComets, int asteroidsCounter)
    {
        DrawTextureEx(Background, BackgroudPosition, 0, 1, WHITE);

        DrawSpaceShip(SpaceShip);

        DrawComets(SmallComets, MidComets, BigComets);

        DrawBullets();

        DrawText(TextFormat("Counter %i", asteroidsCounter), 100, 100, 20, WHITE);
    }
}

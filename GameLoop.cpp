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
    extern Sound Shoot;
    extern Sound Boom;
    extern Sound Hit;
    extern Texture2D Background;
    extern Vector2 BackgroudPosition;
    extern Texture2D SpaceShip;
    extern Texture2D SmallCometsTexture;
    extern Texture2D MidCometsTexture;
    extern Texture2D BigCometsTexture;
    extern Texture2D banner;
    extern Texture2D Pause;
    extern Texture2D PauseSelect;
    extern Texture2D PauseMenu;
    extern Texture2D BackMenu;
    extern Texture2D BackMenuSelect;
    extern Texture2D Resume;
    extern Texture2D ResumeSelect;

    Rectangle pauseButton;
    Vector2 pauseOrigin;
    Vector2 pausePos;

    Rectangle backMenuButton;
    Vector2 backMenuOrigin;
    Vector2 backMenuPos;

    Rectangle resumeButton;
    Vector2 resumeOrigin;
    Vector2 resumePos;

    Vector2 PauseMenuPos;

    Rectangle bannerRec = { static_cast <float>(GetScreenWidth()) / 2, 20, 1000, 50};
    Vector2 bannerPos = { bannerRec.x, bannerRec.y };

    static Circle Mouse;

    extern int asteroidsCounter;
    extern int ShootInpact;
    extern int totalShoots;
    extern int lives;
    extern int score;

    extern int setLoop;

    bool isPause = false;
    int selectButtom = 0;

    int accurancy = 1;


    void gameloop()
    {
        pauseButton.x = (static_cast <float>(GetScreenWidth()) / 2) - pauseButton.width / 2;
        pauseButton.y = static_cast <float>(GetScreenHeight()) / 1.2f;
        pauseButton.width = 500;
        pauseButton.height = 100;
        pauseOrigin = { 0, 0 };
        pausePos = { pauseButton.x, pauseButton.y };

        backMenuButton.x = (static_cast <float>(GetScreenWidth()) / 2) - backMenuButton.width / 2;
        backMenuButton.y = static_cast <float>(GetScreenHeight()) / 1.7f;
        backMenuButton.width = 500;
        backMenuButton.height = 100;
        backMenuOrigin = { 0, 0 };
        backMenuPos = { backMenuButton.x, backMenuButton.y };

        resumeButton.x = (static_cast <float>(GetScreenWidth()) / 2) - resumeButton.width / 2;
        resumeButton.y = static_cast <float>(GetScreenHeight()) / 2.5f;
        resumeButton.width = 500;
        resumeButton.height = 100;
        resumeOrigin = { 0, 0 };
        resumePos = { resumeButton.x, resumeButton.y };


        Mouse.Position.x = GetMousePosition().x;
        Mouse.Position.y = GetMousePosition().y + 20;
        Mouse.Radius = 3;

        if (!isPause)
        {
            MoveSpaceShip(Shoot, Hit);
            accurancy = (ShootInpact * 100) / totalShoots;
            MoveComets(Boom);
            if (CheckCollisionPointRec(Mouse.Position, pauseButton))
            {
                selectButtom = 1;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    isPause = true;
                }
            }
            else
            {
                selectButtom = 0;
            }
        }
        else
        {
            if (CheckCollisionPointRec(Mouse.Position, resumeButton))
            {
                selectButtom = 3;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    isPause = false;
                }
            }
            else if (CheckCollisionPointRec(Mouse.Position, backMenuButton))
            {
                selectButtom = 2;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    setLoop = 0;
                }
            }
            else
            {
                selectButtom = 0;
            }

        }
    }

    void DrawGame()
    {

        DrawTextureEx(Background, BackgroudPosition, 0, 1, WHITE);

        DrawSpaceShip(SpaceShip);

        DrawComets();

        DrawBullets();

        if (selectButtom == 1)
        {
            DrawTextureEx(PauseSelect, pausePos, 0, 1, WHITE);
        }
        else
        {
            DrawTextureEx(Pause, pausePos, 0, 1, WHITE);
        }
        bannerPos = { static_cast <float>(GetScreenWidth()) / 2 - banner.width / 2, bannerRec.y};
        DrawTextureEx(banner,bannerPos, 0, 1, WHITE);
        DrawText(TextFormat("Asteroids: %i", asteroidsCounter), GetScreenWidth() / 2 + 300, 35, 20, BLACK);
        DrawText(TextFormat("Accurancy: %i", accurancy), GetScreenWidth() / 2 , 35, 20, BLACK);
        DrawText(TextFormat("Lives: %i", lives), GetScreenWidth() / 2 - 200 , 35, 20, BLACK);
        DrawText(TextFormat("Score: %i", score * 100), GetScreenWidth() / 2 - 400, 35, 20, BLACK);

        if (isPause)
        {
            
            PauseMenuPos = {(static_cast <float>(GetScreenWidth()) / 2) - PauseMenu.width / 2, (static_cast <float>(GetScreenHeight()) / 2) - PauseMenu.height / 2,};
            DrawTextureEx(PauseMenu, PauseMenuPos, 0, 1, WHITE);
            DrawText("PAUSE", GetScreenWidth() / 2 - 80, GetScreenHeight() / 4, 50, BLACK);
            if (selectButtom == 2)
            {
                DrawTextureEx(BackMenuSelect, backMenuPos, 0, 1, WHITE);
            }
            else
            {
                DrawTextureEx(BackMenu, backMenuPos, 0, 1, WHITE);
            }
            if (selectButtom == 3)
            {
                DrawTextureEx(ResumeSelect, resumePos, 0, 1, WHITE);
            }
            else
            {
                DrawTextureEx(Resume, resumePos, 0, 1, WHITE);
            }
            
        }
    }
}

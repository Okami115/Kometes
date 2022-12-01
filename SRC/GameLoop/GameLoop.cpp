#include "GameLoop.h"
#include <cmath>
#include <iostream> 
#include "raylib.h"
#include <time.h> 
#include "../PowerUps/PowerUpsLoop.h"
#include "../SpaceShip/SpaceShip.h"
#include "../Comets/Comets.h"
#include "../Hunter/Hunter.h"
#include "../MenuLoop/menu.h"

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
    extern Texture2D Sight;
    extern Texture2D Cursor;

    extern Texture2D boomAnimation;

    extern int asteroidsCounter;
    extern int ShootInpact;
    extern int totalShoots;
    extern int lives;
    extern int score;
    extern int AutoCounter;
    extern bool isFullAutoActive;

    extern float timerKaboom;
    extern float timerFullAuto;

    extern int setLoop;

    bool isPause = false;
    int selectButtom = 0;

    int accurancy = 1;

    void gameloop()
    {
        HideCursor();
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


        Mouse.Position.x = GetMousePosition().x - Sight.width / 2;
        Mouse.Position.y = GetMousePosition().y - Sight.height / 2;
        Mouse.Radius = 3;

        if (!isPause && lives > 0)
        {
            MoveSpaceShip(Shoot, Hit);
            accurancy = (ShootInpact * 100) / totalShoots;
            MoveComets(Boom);
            HunterLoop();
            PowerUpsLoop();
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
        else if (isPause && lives > 0)
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
                    isPause = false;
                    score = 0;
                    lives = 3;
                    ShootInpact = 1;
                    totalShoots = 1;
                    timerKaboom = 0;
                    timerFullAuto = 0;
                    isFullAutoActive = false;
                    AutoCounter = 0;
                    destroyComets();
                    DestroyHunter();
                    setLoop = 0;
                }
            }
            else
            {
                selectButtom = 0;
            }

        }
        else if (lives <= 0)
        {
            if (CheckCollisionPointRec(Mouse.Position, backMenuButton))
            {
                selectButtom = 4;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    isPause = false;
                    score = 0;
                    lives = 3;
                    ShootInpact = 1;
                    totalShoots = 1;
                    timerKaboom = 0;
                    timerFullAuto = 0;
                    isFullAutoActive = false;
                    AutoCounter = 0;
                    destroyComets();
                    DestroyHunter();
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
        DrawHunter();

        DrawBullets();

        DrawPowerUps();

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
            DrawText("PAUSE", static_cast <int>(PauseMenuPos.x) + 115, static_cast <int>(PauseMenuPos.y) + 50, 50, BLACK);
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
            DrawTextureEx(Cursor, Mouse.Position, 0, 1, WHITE);
        }
        else if (lives == 0)
        {
            PauseMenuPos = { (static_cast <float>(GetScreenWidth()) / 2) - PauseMenu.width / 2, (static_cast <float>(GetScreenHeight()) / 2) - PauseMenu.height / 2, };
            DrawTextureEx(PauseMenu, PauseMenuPos, 0, 1, WHITE);
            DrawText("YOU LOSS", static_cast <int>(PauseMenuPos.x) + 80, static_cast <int>(PauseMenuPos.y) + 50, 50, BLACK);
            DrawText(TextFormat("Score: %06i", score * 100), GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 - 100, 40, BLACK);
            if (selectButtom == 4)
            {
                DrawTextureEx(BackMenuSelect, backMenuPos, 0, 1, WHITE);
            }
            else
            {
                DrawTextureEx(BackMenu, backMenuPos, 0, 1, WHITE);
            }
            DrawTextureEx(Cursor, Mouse.Position, 0, 1, WHITE);
        }
        else
        {
            DrawTextureEx(Sight, Mouse.Position, 0, 1, WHITE);

        }


    }
}

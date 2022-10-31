#include "SpaceShip.h"
#include "raymath.h"
#include <iostream> 
#include "raylib.h"
#include "../GameLoop/GameLoop.h"
#include "../Comets/Comets.h"
#include "../Hunter/Hunter.h"

namespace OkamiIndustries
{
    //SpaceShip
    Circle SpaceShipColider;

    Vector2 shipPosition = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    int lives = 3;
    bool isShipTravelling = false;
    Vector2 trayectoryShip = { 0, 0 };
    float spaceShipAceleration = 100.0f;


    //bullets
    const int maxAmmo = 100;
    Circle bullet[maxAmmo];

    int bulletCounter;
    bool isBulletTravelling[maxAmmo];
    Vector2 trayectory[maxAmmo];
    int currentBullet = 0;
    int totalShoots = 1;

    float rotated = 0;

    extern int asteroidsCounter;
    extern int score;
    extern Comets comets[100];
    extern Hunter hunter;

    extern bool isFullAutoActive;
    int AutoCounter = 0;
    float timer = 0;

    void spawnShip()
    {
        totalShoots = 1;
        shipPosition = { static_cast <float>(GetScreenWidth()) / 2, static_cast <float>(GetScreenHeight()) / 2 };
        lives = 3;
        isShipTravelling = false;
        trayectoryShip = { 0, 0 };
    }

    void initBullets()
    {
        currentBullet = 0;

        for (int i = 0; i < maxAmmo; i++)
        {
            bullet[i] = { Vector2 {-100, -100}, 4 };
            isBulletTravelling[i] = false;
            trayectory[i] = { 0,0 };
        }
    }

    void MoveSpaceShip(Sound Shoot, Sound Hit)
    {
        Vector2 Cursor = GetMousePosition();
        Vector2 normalDir = {0,0};
        Vector2 Dif;

        Dif.x = shipPosition.x - Cursor.x;
        Dif.y = shipPosition.y - Cursor.y;

        float bulletAceleration = 1000.0f;  

        float arcTan = static_cast <float>(atan(Dif.y / Dif.x));

        float angle = arcTan * 180 / PI;

        float Module = static_cast <float>(sqrt(pow(Dif.x, 2) + pow(Dif.y, 2)));

        normalDir = { Dif.x / Module, Dif.y / Module };

        if (GetMousePosition().x < shipPosition.x && GetMousePosition().y < shipPosition.y)
        {
            angle += 180;
        }
        if (GetMousePosition().x < shipPosition.x && GetMousePosition().y > shipPosition.y)
        {
            angle += 180;
        }
        if (GetMousePosition().x > shipPosition.x && GetMousePosition().y > shipPosition.y)
        {
            angle += 360;
        }

        rotated = angle + 90;
        for (int i = 0; i < asteroidsCounter + 1; i++)
        {
            if (CheckCollision(SpaceShipColider, comets[i].cometsCollider))
            {
                lives--;
                totalShoots = 1;
                PlaySound(Hit);
                shipPosition = { static_cast <float>(GetScreenWidth()) / 2, static_cast <float>(GetScreenHeight()) / 2 };
                isShipTravelling = false;
                destroyComets();
            }

        }

        if (CheckCollision(SpaceShipColider, hunter.hunterCollider))
        {
            lives--;
            totalShoots = 1;
            PlaySound(Hit);
            shipPosition = { static_cast <float>(GetScreenWidth()) / 2, static_cast <float>(GetScreenHeight()) / 2 };
            isShipTravelling = false;
            destroyComets();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            trayectoryShip = normalDir;
            isShipTravelling = true;
        }

        if (isShipTravelling)
        {
            spaceShipAceleration++;
            if (spaceShipAceleration > 200.0f)
            {
                spaceShipAceleration = 200.0f;
            }
            shipPosition.x -= trayectoryShip.x * spaceShipAceleration * GetFrameTime();
            shipPosition.y -= trayectoryShip.y * spaceShipAceleration * GetFrameTime();

            if (shipPosition.x > static_cast <float>(GetScreenWidth()))
            {
                shipPosition.x = 0;
            }
            if (shipPosition.y > static_cast <float>(GetScreenHeight()))
            {
                shipPosition.y = 0;
            }
            if (shipPosition.x < 0)
            {
                shipPosition.x = static_cast <float>(GetScreenWidth());
            }
            if (shipPosition.y < 0)
            {
                shipPosition.y = static_cast <float>(GetScreenHeight());
            }
            if (shipPosition.x == trayectoryShip.x && shipPosition.y == trayectoryShip.y)
            {
                isShipTravelling = false;
            }
        }

        // Shoot
        timer += GetFrameTime();
        if (isFullAutoActive)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                if (timer > 0.1f)
                {
                    trayectory[currentBullet] = normalDir;
                    isBulletTravelling[currentBullet] = true;
                    bullet[currentBullet].Position.x = shipPosition.x;
                    bullet[currentBullet].Position.y = shipPosition.y;
                    currentBullet++;
                    totalShoots++;
                    AutoCounter++;
                    if (AutoCounter == 50)
                    {
                        isFullAutoActive = false;
                        AutoCounter = 0;
                    }
                    PlaySound(Shoot);
                    timer = 0;
                    if (currentBullet >= maxAmmo)
                    {
                        currentBullet = 0;
                    }
                }
            }
        }
        else
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (timer > 0.1f)
                {
                    trayectory[currentBullet] = normalDir;
                    isBulletTravelling[currentBullet] = true;
                    bullet[currentBullet].Position.x = shipPosition.x;
                    bullet[currentBullet].Position.y = shipPosition.y;
                    currentBullet++;
                    totalShoots++;
                    PlaySound(Shoot);
                    if (currentBullet >= maxAmmo)
                    {
                        currentBullet = 0;
                    }
                }
            }
        }

        for (int i = 0; i < maxAmmo; i++)
        {
            if (isBulletTravelling[i])
            {
                bullet[i].Position.x -= (trayectory[i].x * 2) * bulletAceleration * GetFrameTime();
                bullet[i].Position.y -= (trayectory[i].y * 2) * bulletAceleration * GetFrameTime();

                if (bullet[i].Position.x > GetScreenWidth() || bullet[i].Position.y > GetScreenHeight() || bullet[i].Position.x < 0 || bullet[i].Position.y < 0)
                {
                    isBulletTravelling[i] = false;
                    bullet[i].Position.x = -100;
                    bullet[i].Position.y = -100;
                }
            }
        }

    }

    void DrawSpaceShip(Texture2D SpaceShip)
    {
        Vector2 OriginSpaceShip = { static_cast <float>(SpaceShip.width) / 2, static_cast <float>(SpaceShip.height) / 2 };
        Rectangle shipRectangle = { 0, 0, static_cast <float>(SpaceShip.width), static_cast <float>(SpaceShip.height) };
        Rectangle destRec = { shipPosition.x, shipPosition.y, shipRectangle.width, shipRectangle.height };

        SpaceShipColider = { shipPosition, SpaceShip.width / 3 };

        SpaceShipColider.Position.x = shipPosition.x;
        SpaceShipColider.Position.y = shipPosition.y;
        //DrawRectanglePro(destRec, OriginSpaceShip, rotated, WHITE);
        DrawTexturePro(SpaceShip, shipRectangle, destRec, OriginSpaceShip, rotated, WHITE);
        
    }

    bool CheckCollision(Circle collider, Circle Comets)
    {
#pragma warning (disable:26451)
        float distX = collider.Position.x - Comets.Position.x;
        float distY = collider.Position.y - Comets.Position.y;
        float distance = static_cast <float>(sqrt((distX * distX) + (distY * distY)));
#pragma warning (default:26451)

        if (distance <= collider.Radius + Comets.Radius)
            return true;
        else
            return false;
    }

    void DrawBullets()
    {
        for (int i = 0; i < 100; i++)
        {
            DrawCircle(static_cast <int>(bullet[i].Position.x), static_cast <int>(bullet[i].Position.y), static_cast <float>(bullet[i].Radius), SKYBLUE);
        }
    }

}
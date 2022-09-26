#include "raylib.h"
#include "raymath.h"
#include "SpaceShip.h"
#include "GameLoop.h"

namespace OkamiIndustries
{
    //bullets
    const int maxAmmo = 100;
    Circle bullet[maxAmmo];
    int bulletCounter;
    bool isBulletTravelling[maxAmmo];
    Vector2 trayectory[maxAmmo];

    float rotated = 0;
    bool isShipTravelling = false;
    Vector2 trayectoryShip = {0, 0};

    int currentBullet = 0;

    void inicializedBullets()
    {
        for (int i = 0; i < maxAmmo; i++)
        {
            bullet[i] = { Vector2 {-100, -100}, 4 };
            isBulletTravelling[i] = false;
            trayectory[i] = { 0,0 };
        }
    }

    void MoveSpaceShip(Vector2& shipPosition)
    {
        Vector2 Cursor = GetMousePosition();
        Vector2 normalDir = {0,0};
        Vector2 Dif;

        Dif.x = shipPosition.x - Cursor.x;
        Dif.y = shipPosition.y - Cursor.y;

        float aceleration = 1000.0f;

        float Module = sqrt(pow(Dif.x, 2) + pow(Dif.y, 2));

        normalDir = { Dif.x / Module, Dif.y / Module };

        float arcTan = atan(Dif.y / Dif.x);

        float angle = arcTan * 180 / PI;

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

        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
        {
            trayectoryShip = normalDir;
            isShipTravelling = true;
        }

        if (isShipTravelling)
        {
            shipPosition.x -= trayectoryShip.x * aceleration * GetFrameTime();
            shipPosition.y -= trayectoryShip.y * aceleration * GetFrameTime();

            if (shipPosition.x == trayectoryShip.x && shipPosition.y == trayectoryShip.y)
            {
                isShipTravelling = false;
            }
        }


        // Shoot
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            trayectory[currentBullet] = normalDir;
            isBulletTravelling[currentBullet] = true;
            bullet[currentBullet].Position.x = shipPosition.x;
            bullet[currentBullet].Position.y = shipPosition.y;
            currentBullet++;
            if (currentBullet > maxAmmo)
            {
                currentBullet = 0;
            }
        }

        for (int i = 0; i < maxAmmo; i++)
        {
            if (isBulletTravelling[i])
            {
                bullet[i].Position.x -= (trayectory[i].x * 2) * aceleration * GetFrameTime();
                bullet[i].Position.y -= (trayectory[i].y * 2) * aceleration * GetFrameTime();

                if (bullet[i].Position.x > GetScreenWidth() || bullet[i].Position.y > GetScreenHeight() || bullet[i].Position.x < 0 || bullet[i].Position.y < 0)
                {
                    isBulletTravelling[i] = false;
                    bullet[i].Position.x = -100;
                    bullet[i].Position.y = -100;
                }
            }
        }

    }

    void DrawSpaceShip(Rectangle shipRectangle, Vector2 OriginSpaceShip, Vector2 shipPosition, Texture2D SpaceShip, Circle& SpaceShipColider, Circle Comets)
    {
        SpaceShipColider = { shipPosition, SpaceShip.width / 3 };

        SpaceShipColider.Position.x = shipPosition.x;
        SpaceShipColider.Position.y = shipPosition.y;
        Rectangle destRec = { shipPosition.x, shipPosition.y, shipRectangle.width, shipRectangle.height };
        //DrawRectanglePro(destRec, OriginSpaceShip, rotated, WHITE);

        DrawTexturePro(SpaceShip, shipRectangle, destRec, OriginSpaceShip, rotated, WHITE);

        if (CheckCollision(SpaceShipColider, Comets))
        {
            //DrawCircle(SpaceShipColider.Position.x, SpaceShipColider.Position.y, SpaceShipColider.Radius, RED);
        }
        else
        {
            //DrawCircle(SpaceShipColider.Position.x, SpaceShipColider.Position.y, SpaceShipColider.Radius, WHITE);
        }
        
    }

    bool CheckCollision(Circle collider, Circle Comets)
    {
        float distX = collider.Position.x - Comets.Position.x;
        float distY = collider.Position.y - Comets.Position.y;
        float distance = sqrt((distX * distX) + (distY * distY));

        if (distance <= collider.Radius + Comets.Radius)
            return true;
        
        return false;
    }

    void DrawBullets()
    {
        for (int i = 0; i < 100; i++)
        {
            DrawCircle(bullet[i].Position.x, bullet[i].Position.y, bullet[i].Radius, SKYBLUE);
        }
    }

}
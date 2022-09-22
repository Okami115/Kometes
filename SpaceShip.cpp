#include "raylib.h"
#include "raymath.h"
#include "SpaceShip.h"
#include "GameLoop.h"

namespace OkamiIndustries
{
    
    float rotated = 0;

    void MoveSpaceShip(Vector2& shipPosition)
    {
        Vector2 Cursor = GetMousePosition();

        Vector2 Dif;

        float aceleration = 1000.0f;

        Dif.x = shipPosition.x - Cursor.x;
        Dif.y = shipPosition.y - Cursor.y;

        float arcTan = atan(Dif.y / Dif.x);

        float angle = arcTan * 180 / PI;

        float Module = sqrt(pow(Dif.x, 2) + pow(Dif.y, 2));

        Vector2 normalDir = { Dif.x / Module, Dif.y / Module };

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

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            shipPosition.x -= normalDir.x * aceleration * GetFrameTime();
            shipPosition.y -= normalDir.y * aceleration * GetFrameTime();
        }

    }

    void DrawSpaceShip(Rectangle shipRectangle, Vector2 OriginSpaceShip, Vector2 shipPosition, Texture2D SpaceShip, Circle& SpaceShipColider, Circle Comets)
    {
        SpaceShipColider = { shipPosition, SpaceShip.width / 3 };

        SpaceShipColider.Position.x = shipPosition.x;
        SpaceShipColider.Position.y = shipPosition.y;
        Rectangle destRec = { shipPosition.x, shipPosition.y, shipRectangle.width, shipRectangle.height };
        DrawRectanglePro(destRec, OriginSpaceShip, rotated, WHITE);

        DrawTexturePro(SpaceShip, shipRectangle, destRec, OriginSpaceShip, rotated, WHITE);
        if (CheckCollisionSpaceShip(SpaceShipColider, Comets))
        {
            DrawCircle(SpaceShipColider.Position.x, SpaceShipColider.Position.y, SpaceShipColider.Radius, RED);
        }
        else
        {
            DrawCircle(SpaceShipColider.Position.x, SpaceShipColider.Position.y, SpaceShipColider.Radius, WHITE);
        }
        
    }

    bool CheckCollisionSpaceShip(Circle SpaceShipColider, Circle Comets)
    {
        float distX = SpaceShipColider.Position.x - Comets.Position.x;
        float distY = SpaceShipColider.Position.y - Comets.Position.y;
        float distance = sqrt((distX * distX) + (distY * distY));

        if (distance <= SpaceShipColider.Radius + Comets.Radius) 
            return true;
        
        return false;
    }


}
#include "raylib.h"
#include "raymath.h"
#include "SpaceShip.h"

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

        rotated = angle;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            shipPosition.x -= normalDir.x * aceleration * GetFrameTime();
            shipPosition.y -= normalDir.y * aceleration * GetFrameTime();
        }

    }

    void DrawSpaceShip(Rectangle shipRectangle, Vector2 OriginSpaceShip, Vector2 shipPosition, Texture2D SpaceShip)
    {
        Rectangle destRec = { shipPosition.x, shipPosition.y, shipRectangle.width, shipRectangle.height };

        DrawTexturePro(SpaceShip, shipRectangle, destRec, OriginSpaceShip, rotated, WHITE);
    }


}
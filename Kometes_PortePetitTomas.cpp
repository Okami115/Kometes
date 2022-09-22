#include "raylib.h"
#include "raymath.h"

namespace OkamiIndustries
{
    void MoveSpaceShip(Vector2& SpaceShip, float& rotated)
    {
        Vector2 Cursor = GetMousePosition();

        Vector2 Dif;

        float aceleration = 1000.0f;

        Dif.x = SpaceShip.x - Cursor.x;
        Dif.y = SpaceShip.y - Cursor.y;

        float arcTan = atan(Dif.y / Dif.x);

        float angle = arcTan * 180 / PI;

        float Module = sqrt(pow(Dif.x, 2) + pow(Dif.y, 2));

        Vector2 normalDir = { Dif.x / Module, Dif.y / Module };

        rotated = angle;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            SpaceShip.x -= normalDir.x * aceleration * GetFrameTime();
            SpaceShip.y -= normalDir.y * aceleration * GetFrameTime();
        }

    }

}

int main()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.05");

    //SpaceShip
    Texture2D SpaceShip = LoadTexture("SpaceShip.png");
    Vector2 Origin = { SpaceShip.width / 2, SpaceShip.height / 2 };
    Vector2 shipPosition = { screenWidth / 2, screenHeight / 2 };
    Rectangle shipRectangle = { shipPosition.x, shipPosition.y, SpaceShip.width, SpaceShip.height };
    float rotated = 0;

    

    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        //SpaceShip Update
        OkamiIndustries::MoveSpaceShip(shipPosition, rotated);
        Rectangle destRec = { shipPosition.x, shipPosition.y, shipRectangle.width, shipRectangle.height };

        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexturePro(SpaceShip, shipRectangle, destRec, Origin, rotated, WHITE);

        EndDrawing();
    }

    UnloadTexture(SpaceShip);
    CloseWindow();

    return 0;
}
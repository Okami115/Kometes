#include "raylib.h"
#include "raymath.h"

namespace OkamiIndustries
{

    

    void MoveSpaceShip(Rectangle& SpaceShip)
    {
        Vector2 Cursor = GetMousePosition();

        Vector2 Dif;

        float aceleration = 1000.0f;

        Dif.x = SpaceShip.x - Cursor.x;
        Dif.y = SpaceShip.y - Cursor.y;

        Vector2 DifNormalizated;
        DifNormalizated.x = Dif.x / Vector2Length(Dif);
        DifNormalizated.y = Dif.y / Vector2Length(Dif);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            SpaceShip.x -= DifNormalizated.x * aceleration * GetFrameTime();
            SpaceShip.y -= DifNormalizated.y * aceleration * GetFrameTime();
        }

    }
}

int main()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.05");

    Texture2D SpaceShip = LoadTexture("SpaceShip.png");

    Rectangle Rec1 = { screenWidth / 2, screenHeight / 2, 110, 110 };

    Vector2 Origin = { Rec1.width / 2, Rec1.height / 2 };
    Vector2 SpritePos = { Rec1.x, Rec1.y };

    float rotated = 0;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        OkamiIndustries::MoveSpaceShip(Rec1);
        SpritePos = { Rec1.x, Rec1.y };

        BeginDrawing();

        ClearBackground(BLACK);
        DrawRectanglePro(Rec1, Origin, rotated, BLACK);
        DrawTexture(SpaceShip, Rec1.x - Rec1.width / 2, Rec1.y - Rec1.height / 2, WHITE);

        EndDrawing();
    }

    UnloadTexture(SpaceShip);
    CloseWindow();

    return 0;
}
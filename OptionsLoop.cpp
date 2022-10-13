#include "raylib.h"
#include "SpaceShip.h"
#include "CoreLoop.h"

namespace OkamiIndustries
{
	Rectangle XGAButtom;
	Vector2 XGAOrigin;
	Vector2 XGAPos;

	Rectangle HDButtom;
	Vector2 HDButtomOrigin;
	Vector2 HDButtomPos;

	Rectangle FHDButtom;
	Vector2 FHDButtomOrigin;
	Vector2 FHDButtomPos;

	Rectangle FullScreenButtom;
	Vector2 FullScreenButtomOrigin;
	Vector2 FullScreenButtomPos;

	extern Texture2D Cursor;
	extern Texture2D BackgroundMenu;
	extern Vector2 BackgroudMenuPosition;

	extern Texture2D XGA;
	extern Texture2D XGASelect;
	extern Texture2D HD;
	extern Texture2D HDSelect;
	extern Texture2D FHD;
	extern Texture2D FHDSelect;
	extern Texture2D FullScreen;
	extern Texture2D FullScreenSelect;

	extern int setLoop;
	extern int selectMenu;

	extern int screenWidth;
	extern int screenHeight;
	extern bool isGameActive;

	extern Vector2 BackgroudMenuPosition;
	extern Vector2 BackgroudCreditsPosition;

	static Circle Mouse;

	void OptionsLoop()
	{
		HideCursor();
		Mouse.Position.x = GetMousePosition().x;
		Mouse.Position.y = GetMousePosition().y;
		Mouse.Radius = 3;

		XGAButtom.x = (static_cast <float>(GetScreenWidth()) / 2) - XGAButtom.width / 2;
		XGAButtom.y = static_cast <float>(GetScreenHeight()) / 3;
		XGAButtom.width = 500;
		XGAButtom.height = 100;
		XGAOrigin = { 0, 0 };
		XGAPos = { XGAButtom.x, XGAButtom.y };

		HDButtom.x = (static_cast <float>(GetScreenWidth()) / 2) - HDButtom.width / 2;
		HDButtom.y = static_cast <float>(GetScreenHeight()) / 2.1f;
		HDButtom.width = 500;
		HDButtom.height = 100;
		HDButtomOrigin = { 0 , 0 };
		HDButtomPos = { HDButtom.x, HDButtom.y };

		FHDButtom.x = (static_cast <float>(GetScreenWidth()) / 2) - FHDButtom.width / 2;
		FHDButtom.y = static_cast <float>(GetScreenHeight()) / 1.6f;
		FHDButtom.width = 500;
		FHDButtom.height = 100;
		FHDButtomOrigin = { 0, 0 };
		FHDButtomPos = { FHDButtom.x, FHDButtom.y };

		FullScreenButtom.x = (static_cast <float>(GetScreenWidth()) / 2) - FullScreenButtom.width / 2;
		FullScreenButtom.y = static_cast <float>(GetScreenHeight()) / 1.3f;
		FullScreenButtom.width = 500;
		FullScreenButtom.height = 100;
		FullScreenButtomOrigin = { 0, 0 };
		FullScreenButtomPos = { FullScreenButtom.x, FullScreenButtom.y };

		if (CheckCollisionPointRec(Mouse.Position, XGAButtom))
		{
			selectMenu = 1;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				screenWidth = 1024;
				screenHeight = 768;
				CloseWindow();
				initWin();
			}
		}

		if (CheckCollisionCircleRec(Mouse.Position, static_cast <float>(Mouse.Radius), HDButtom))
		{
			selectMenu = 2;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				screenWidth = 1280;
				screenHeight = 720;
				CloseWindow();
				initWin();
			}
		}

		if (CheckCollisionCircleRec(Mouse.Position, static_cast <float>(Mouse.Radius), FHDButtom))
		{
			selectMenu = 3;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				screenWidth = 1920;
				screenHeight = 1080;
				CloseWindow();
				InitWindow(screenWidth, screenHeight, "Nose");
				setLoop = 0;
			}
		}

		if (CheckCollisionCircleRec(Mouse.Position, static_cast <float>(Mouse.Radius), FullScreenButtom))
		{
			selectMenu = 4;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				ToggleFullscreen();
			}
		}
	}

	void DrawOptions()
	{
		DrawTextureEx(BackgroundMenu, BackgroudMenuPosition, 0, 1, WHITE);

		if (selectMenu == 1)
		{
			DrawTextureEx(XGASelect, XGAPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(XGA, XGAPos, 0, 1, WHITE);
		}

		if (selectMenu == 2)
		{
			DrawTextureEx(HDSelect, HDButtomPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(HD, HDButtomPos, 0, 1, WHITE);
		}

		if (selectMenu == 3)
		{
			DrawTextureEx(FHDSelect, FHDButtomPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(FHD, FHDButtomPos, 0, 1, WHITE);
		}

		if (selectMenu == 4)
		{
			DrawTextureEx(FullScreenSelect, FullScreenButtomPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(FullScreen, FullScreenButtomPos, 0, 1, WHITE);
		}

		DrawTextureEx(Cursor, Mouse.Position, 0, 1, WHITE);
	}
}
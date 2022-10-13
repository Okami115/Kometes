#include "raylib.h"
#include "SpaceShip.h"
#include <iostream>

namespace OkamiIndustries
{
	Rectangle BackButton;
	Vector2 BackOrigin;
	Vector2 BackPos;

	extern Texture2D Cursor;
	static Circle Mouse;

	void CreditsLoop(int& selectMenu, int& setLoop)
	{
		Mouse.Position.x = GetMousePosition().x;
		Mouse.Position.y = GetMousePosition().y + 20;
		Mouse.Radius = 3;

		BackButton.x = (static_cast <float>(GetScreenWidth()) / 2) - BackButton.width / 2;
		BackButton.y = static_cast <float>(GetScreenHeight()) / 1.2f;
		BackButton.width = 500;
		BackButton.height = 100;
		BackOrigin = { 0, 0 };
		BackPos = { BackButton.x, BackButton.y };

		if (CheckCollisionPointRec(Mouse.Position, BackButton))
		{
			selectMenu = 0;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = selectMenu;
			}
		}
		else
		{
			selectMenu = 3;
		}
	}

	void DrawCredits(Texture2D BackgroundCredits, Vector2 BackgroudCreditsPosition, Texture2D Back, Texture2D BackSelect, int selectMenu)
	{
		DrawTextureEx(BackgroundCredits, BackgroudCreditsPosition, 0, 1, WHITE);
		if (selectMenu == 0)
		{
			DrawTextureEx(BackSelect, BackPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(Back, BackPos, 0, 1, WHITE);
		}
		DrawTextureEx(Cursor, Mouse.Position, 0, 1, WHITE);
	}

}
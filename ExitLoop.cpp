#include "raylib.h"
#include "SpaceShip.h"

namespace OkamiIndustries
{

	Rectangle exitButtom;
	Vector2 exitButtomOrigin;
	Vector2 exitButtomPos;

	Rectangle cancelButtom;
	Vector2 cancelButtomOrigin;
	Vector2 cancelButtomPos;

	static Circle Mouse;

	extern Texture2D exit;
	extern Texture2D exitSelect;
	extern Texture2D Cancel;
	extern Texture2D CancelSelect;

	extern Texture2D BackgroundMenu;
	extern Vector2 BackgroudMenuPosition;

	extern int selectMenu;
	extern int setLoop;
	extern bool isGameActive;

	void ExitLoop()
	{
		Mouse.Position.x = GetMousePosition().x;
		Mouse.Position.y = GetMousePosition().y + 20;
		Mouse.Radius = 3;

		exitButtom.x = (static_cast <float>(GetScreenWidth()) / 4) - exitButtom.width / 2;
		exitButtom.y = static_cast <float>(GetScreenHeight()) / 2;
		exitButtom.width = 500;
		exitButtom.height = 100;
		exitButtomOrigin = { 0, 0 };
		exitButtomPos = { exitButtom.x, exitButtom.y };

		cancelButtom.x = (static_cast <float>(GetScreenWidth()) / 4) * 3 - cancelButtom.width / 2;
		cancelButtom.y = static_cast <float>(GetScreenHeight()) / 2;
		cancelButtom.width = 500;
		cancelButtom.height = 100;
		cancelButtomOrigin = { 0 , 0 };
		cancelButtomPos = { cancelButtom.x, cancelButtom.y };

		if (CheckCollisionPointRec(Mouse.Position, exitButtom))
		{
			selectMenu = 1;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = 0;
				isGameActive = false;
			}
		}

		if (CheckCollisionCircleRec(Mouse.Position, static_cast <float>(Mouse.Radius), cancelButtom))
		{
			selectMenu = 2;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = 0;
			}

		}
	}

	void DrawExit()
	{
		DrawTextureEx(BackgroundMenu, BackgroudMenuPosition, 0, 1, WHITE);

		if (selectMenu == 1)
		{
			DrawTextureEx(exitSelect, exitButtomPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(exit, exitButtomPos, 0, 1, WHITE);
		}

		if (selectMenu == 2)
		{
			DrawTextureEx(CancelSelect, cancelButtomPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(Cancel, cancelButtomPos, 0, 1, WHITE);
		}

	}

}
#include "raylib.h"
#include "SpaceShip.h"

namespace OkamiIndustries
{
	Rectangle gameButtom;
	Vector2 gameOrigin;
	Vector2 gamePos;

	Rectangle options;
	Vector2 optionsOrigin;
	Vector2 optionsPos;

	Rectangle credits;
	Vector2 creditsOrigin;
	Vector2 creditsPos;

	Rectangle exit;
	Vector2 exitOrigin;
	Vector2 exitPos;

	extern Texture2D Cursor;

	static Circle Mouse;

	void LoopMenu(int& selectMenu, int& setLoop)
	{
		HideCursor();
		Mouse.Position.x = GetMousePosition().x;
		Mouse.Position.y = GetMousePosition().y;
		Mouse.Radius = 3;

		gameButtom.x = (static_cast <float>(GetScreenWidth()) / 2) - gameButtom.width / 2;
		gameButtom.y = static_cast <float>(GetScreenHeight()) / 3;
		gameButtom.width = 500;
		gameButtom.height = 100;
		gameOrigin = { 0, 0};
		gamePos = { gameButtom.x, gameButtom.y };

		options.x = (static_cast <float>(GetScreenWidth()) / 2) - options.width / 2;
		options.y = static_cast <float>(GetScreenHeight()) / 2.1f;
		options.width = 500;
		options.height = 100;
		optionsOrigin = { 0 , 0 };
		optionsPos = { options.x, options.y };

		credits.x = (static_cast <float>(GetScreenWidth()) / 2) - credits.width / 2;
		credits.y = static_cast <float>(GetScreenHeight()) / 1.6f;
		credits.width = 500;
		credits.height = 100;
		creditsOrigin = { 0, 0 };
		creditsPos = { credits.x, credits.y };

		exit.x = (static_cast <float>(GetScreenWidth()) / 2) - exit.width / 2;
		exit.y = static_cast <float>(GetScreenHeight()) / 1.3f;
		exit.width = 500;
		exit.height = 100;
		exitOrigin = { 0, 0 };
		exitPos = { exit.x, exit.y };

		if (CheckCollisionPointRec(Mouse.Position, gameButtom))
		{
			selectMenu = 1;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = selectMenu;
			}
		}

		if (CheckCollisionCircleRec(Mouse.Position, static_cast <float>(Mouse.Radius), options))
		{
			selectMenu = 2;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = selectMenu;
			}
		}

		if (CheckCollisionCircleRec(Mouse.Position, static_cast <float>(Mouse.Radius), credits))
		{
			selectMenu = 3;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = selectMenu;
			}
		}

		if (CheckCollisionCircleRec(Mouse.Position, static_cast <float>(Mouse.Radius), exit))
		{
			selectMenu = 4;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = selectMenu;
			}
		}

	}

	void DrawMenu(int selectMenu, Texture2D BackgroundMenu, Vector2 BackgroudMenuPosition,Texture2D PlaySelect, Texture2D Play, Texture2D Options, Texture2D OptionsSelect, Texture2D Credits, Texture2D CreditsSelect, Texture2D Exit, Texture2D ExitSelect)
	{
		DrawTextureEx(BackgroundMenu, BackgroudMenuPosition, 0, 1, WHITE);

		if (selectMenu == 1)
		{			
			DrawTextureEx(PlaySelect, gamePos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(Play, gamePos, 0, 1, WHITE);
		}

		if (selectMenu == 2)
		{
			DrawTextureEx(OptionsSelect, optionsPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(Options, optionsPos, 0, 1, WHITE);
		}

		if(selectMenu == 3)
		{
			DrawTextureEx(CreditsSelect, creditsPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(Credits, creditsPos, 0, 1, WHITE);
		}

		if (selectMenu == 4)
		{
			DrawTextureEx(ExitSelect, exitPos, 0, 1, WHITE);
		}
		else
		{ 
			DrawTextureEx(Exit, exitPos, 0, 1, WHITE);
		}
		DrawTextureEx(Cursor, Mouse.Position, 0, 1, WHITE);
	}
	

}
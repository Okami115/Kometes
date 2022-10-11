#include "raylib.h"
#include "SpaceShip.h"

namespace OkamiIndustries
{

	Rectangle game;
	Vector2 gameOrigin;

	Rectangle options;
	Vector2 optionsOrigin;

	Rectangle credits;
	Vector2 creditsOrigin;

	Rectangle exit;
	Vector2 exitOrigin;

	Circle Mouse;

	void LoopMenu(int& selectMenu, int& setLoop)
	{
		Mouse.Position.x = GetMousePosition().x;
		Mouse.Position.y = GetMousePosition().y + 20;
		Mouse.Radius = 3;

		game.x = (static_cast <float>(GetScreenWidth()) / 2) - game.width / 2;
		game.y = static_cast <float>(GetScreenHeight()) / 3;
		game.width = 500;
		game.height = 100;
		gameOrigin = { 0, 0};

		options.x = (static_cast <float>(GetScreenWidth()) / 2) - options.width / 2;
		options.y = static_cast <float>(GetScreenHeight()) / 2.1f;
		options.width = 500;
		options.height = 100;
		optionsOrigin = { 0 , 0 };

		credits.x = (static_cast <float>(GetScreenWidth()) / 2) - credits.width / 2;
		credits.y = static_cast <float>(GetScreenHeight()) / 1.6f;
		credits.width = 500;
		credits.height = 100;
		creditsOrigin = { 0, 0 };

		exit.x = (static_cast <float>(GetScreenWidth()) / 2) - exit.width / 2;
		exit.y = static_cast <float>(GetScreenHeight()) / 1.3f;
		exit.width = 500;
		exit.height = 100;
		exitOrigin = { 0, 0 };

		if (CheckCollisionPointRec(Mouse.Position, game))
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

	void DrawMenu(int selectMenu)
	{
		if (selectMenu == 1)
		{
			DrawRectanglePro(game, gameOrigin, 0, WHITE);
		}
		else
		{
			DrawRectanglePro(game, gameOrigin, 0, RED);
		}

		if (selectMenu == 2)
		{
			DrawRectanglePro(options, optionsOrigin, 0, WHITE);
		}
		else
		{
			DrawRectanglePro(options, optionsOrigin, 0, RED);
		}

		if(selectMenu == 3)
		{
			DrawRectanglePro(credits, creditsOrigin, 0, WHITE);
		}
		else
		{
			DrawRectanglePro(credits, creditsOrigin, 0, RED);
		}

		if (selectMenu == 4)
		{
			DrawRectanglePro(exit, exitOrigin, 0, WHITE);
		}
		else
		{ 
			DrawRectanglePro(exit, exitOrigin, 0, RED);
		}

		DrawCircle(static_cast <int>(Mouse.Position.x), static_cast <int>(Mouse.Position.y), static_cast <float>(Mouse.Radius), YELLOW);
	}
	

}
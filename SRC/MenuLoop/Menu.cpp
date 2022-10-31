#include "raylib.h"
#include "../SpaceShip/SpaceShip.h"

namespace OkamiIndustries
{
	static Rectangle gameButtom;
	static Vector2 gameOrigin;
	static Vector2 gamePos;

	static Rectangle HowToPlayButtom;
	static Vector2 HowToPlayOrigin;
	static Vector2 HowToPlayPos;

	static Rectangle creditsButtom;
	static Vector2 creditsOrigin;
	static Vector2 creditsPos;

	static Rectangle exitButtom;
	static Vector2 exitOrigin;
	static Vector2 exitPos;

	extern int selectMenu;
	extern int setLoop;
	extern Texture2D BackgroundMenu;
	extern Vector2 BackgroudMenuPosition;	
	extern Texture2D PlaySelect;
	extern Texture2D Play;
	extern Texture2D HowToPlay;
	extern Texture2D HowToPlaySelect;
	extern Texture2D credits;
	extern Texture2D creditsSelect;
	extern Texture2D exit;
	extern Texture2D exitSelect;

	extern Texture2D Cursor;

	static Circle Mouse;

	void LoopMenu()
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

		HowToPlayButtom.x = (static_cast <float>(GetScreenWidth()) / 2) - HowToPlayButtom.width / 2;
		HowToPlayButtom.y = static_cast <float>(GetScreenHeight()) / 2.1f;
		HowToPlayButtom.width = 500;
		HowToPlayButtom.height = 100;
		HowToPlayOrigin = { 0 , 0 };
		HowToPlayPos = { HowToPlayButtom.x, HowToPlayButtom.y };

		creditsButtom.x = (static_cast <float>(GetScreenWidth()) / 2) - creditsButtom.width / 2;
		creditsButtom.y = static_cast <float>(GetScreenHeight()) / 1.6f;
		creditsButtom.width = 500;
		creditsButtom.height = 100;
		creditsOrigin = { 0, 0 };
		creditsPos = { creditsButtom.x, creditsButtom.y };

		exitButtom.x = (static_cast <float>(GetScreenWidth()) / 2) - exitButtom.width / 2;
		exitButtom.y = static_cast <float>(GetScreenHeight()) / 1.3f;
		exitButtom.width = 500;
		exitButtom.height = 100;
		exitOrigin = { 0, 0 };
		exitPos = { exitButtom.x, exitButtom.y };

		if (CheckCollisionPointRec(Mouse.Position, gameButtom))
		{
			selectMenu = 1;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = selectMenu;
			}
		}

		if (CheckCollisionCircleRec(Mouse.Position, static_cast <float>(Mouse.Radius), HowToPlayButtom))
		{
			selectMenu = 2;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = selectMenu;
			}
		}

		if (CheckCollisionCircleRec(Mouse.Position, static_cast <float>(Mouse.Radius), creditsButtom))
		{
			selectMenu = 3;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = selectMenu;
			}
		}

		if (CheckCollisionCircleRec(Mouse.Position, static_cast <float>(Mouse.Radius), exitButtom))
		{
			selectMenu = 4;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				setLoop = selectMenu;
			}
		}

	}

	void DrawMenu()
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
			DrawTextureEx(HowToPlaySelect, HowToPlayPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(HowToPlay, HowToPlayPos, 0, 1, WHITE);
		}

		if(selectMenu == 3)
		{
			DrawTextureEx(creditsSelect, creditsPos, 0, 1, WHITE);
		}
		else
		{
			DrawTextureEx(credits, creditsPos, 0, 1, WHITE);
		}

		if (selectMenu == 4)
		{
			DrawTextureEx(exitSelect, exitPos, 0, 1, WHITE);
		}
		else
		{ 
			DrawTextureEx(exit, exitPos, 0, 1, WHITE);
		}
		DrawTextureEx(Cursor, Mouse.Position, 0, 1, WHITE);
	}
	

}
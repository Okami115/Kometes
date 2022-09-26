#include "Comets.h"
#include "GameLoop.h"
#include "raymath.h"
#include "SpaceShip.h"
#include <iostream> 

namespace OkamiIndustries
{
	static int maxComets = 10;
	float cometsSpeed = 1.0f;
	float aceleration = 500;
	bool cometsIsLive[10];
	Vector2 cometsTrayectory[10];
	Circle comets[10];
	int random[10];

	Circle BigComets[10];
	Circle MidComets[20];
	Circle SmallComets[40];

	extern Circle bullet[100];

	void spawnComets()
	{
		for (int i = 0; i < 10; i++)
		{
			comets[i].Position.x = rand() % GetScreenWidth();
			comets[i].Position.y = rand() % GetScreenHeight();
			cometsIsLive[i] = true;
			random[i] = rand() % 3 + 1;
			if (random[i] == 1)
			{
				comets[i].Radius = 15;
			}
			else if (random[i] == 2)
			{
				comets[i].Radius = 30;
			}
			else
			{
				comets[i].Radius = 60;
			}
			cometsTrayectory[i] = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };
		}
	}

	void MoveComets()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				if (CheckCollision(comets[i], bullet[j]))
				{
					cometsIsLive[i] = false;
					comets[i].Position.x = -1000;
					comets[i].Position.y = -1000;
				}
			}

			if (cometsIsLive[i])
			{
				comets[i].Position.x += cometsTrayectory[i].x * aceleration * GetFrameTime();
				comets[i].Position.y += cometsTrayectory[i].y * aceleration * GetFrameTime();

				if (comets[i].Position.x > GetScreenWidth())
				{
					comets[i].Position.x = 0;
				}
				if (comets[i].Position.y > GetScreenHeight())
				{
					comets[i].Position.y = 0;
				}
				if (comets[i].Position.x < 0)
				{
					comets[i].Position.x = GetScreenWidth();
				}
				if (comets[i].Position.y < 0)
				{
					comets[i].Position.y = GetScreenHeight();
				}
			}
		}
	}

	void DrawComets(Texture2D SmallSprite, Texture2D MidSprite, Texture2D BigSprite)
	{
		for (int i = 0; i < 10; i++)
		{
			float rotation = 0;

			float arcTan = atan(cometsTrayectory[i].y / cometsTrayectory[i].x);

			float angle = arcTan * 180 / PI;

			if (cometsTrayectory[i].x < comets[i].Position.x && cometsTrayectory[i].y < comets[i].Position.y)
			{
				if (cometsTrayectory[i].x < 0)
				{

					angle += 180;
				}
				else
				{
					angle += 360;
				}
				
			}
			if (cometsTrayectory[i].x < comets[i].Position.x && cometsTrayectory[i].y > comets[i].Position.y)
			{
				angle += 180;
			}
			if (cometsTrayectory[i].x > comets[i].Position.x && cometsTrayectory[i].y > comets[i].Position.y)
			{
				angle -= 360;
			}
			if (cometsTrayectory[i].x > comets[i].Position.x && cometsTrayectory[i].y < comets[i].Position.y)
			{
				angle -= 0;
			}

			rotation = angle + 90;
			
			Vector2 cometsPos = { comets[i].Position.x, comets[i].Position.y };

			if (random[i] == 1)
			{
				Rectangle source = { 0, 0, SmallSprite.width, SmallSprite.height };
				Rectangle dest = { comets[i].Position.x, comets[i].Position.y, SmallSprite.width, SmallSprite.height};
				Vector2 origin = { SmallSprite.width / 2, SmallSprite.height / 2 };
				DrawRectanglePro(dest, origin, rotation, WHITE);
				DrawTexturePro(SmallSprite,source ,dest, origin, rotation, WHITE);
				DrawCircle(comets[i].Position.x, comets[i].Position.y, comets[i].Radius, RED);
			}
			else if (random[i] == 2)
			{
				Rectangle source = { 0, 0, MidSprite.width, MidSprite.height };
				Rectangle dest = { comets[i].Position.x, comets[i].Position.y, MidSprite.width, MidSprite.height };
				Vector2 origin = { MidSprite.width / 2, MidSprite.height / 2 };
				DrawRectanglePro(dest, origin, rotation, WHITE);
				DrawTexturePro(MidSprite, source, dest, origin, rotation, WHITE);
				DrawCircle(comets[i].Position.x, comets[i].Position.y, comets[i].Radius, RED);
			}
			else
			{
				Rectangle source = { 0, 0, BigSprite.width, BigSprite.height };
				Rectangle dest = { comets[i].Position.x, comets[i].Position.y, BigSprite.width, BigSprite.height };
				Vector2 origin = { BigSprite.width / 2, BigSprite.height / 2 };
				DrawRectanglePro(dest, origin, rotation, WHITE);
				DrawTexturePro(BigSprite, source, dest, origin, rotation, WHITE);
				DrawCircle(comets[i].Position.x, comets[i].Position.y, comets[i].Radius, RED);
			}
		}
	}
}
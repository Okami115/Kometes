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
	int asteroidsCounter = 0;

	enum typeComets
	{
		SmallComets = 1,
		MidComets,
		BigComets,
	};

	struct Comets
	{
		Circle cometsCollider;
		Vector2 cometsTrayectory;
		int typeComets;
		bool cometsIsLive;
	};

	Comets comets[100];
	extern Circle bullet[100];

	void spawnComets()
	{
		for (int i = 0; i < 10; i++)
		{
			asteroidsCounter++;
			comets[i].typeComets = rand() % 3 + 1;
			if (comets[i].typeComets == (int)SmallComets)
			{
				comets[i].cometsCollider.Position.x = rand() % GetScreenWidth();
				comets[i].cometsCollider.Position.y = rand() % GetScreenHeight();
				comets[i].cometsCollider.Radius = 15;
				comets[i].cometsIsLive = true;
				comets[i].cometsTrayectory = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };
			}
			else if (comets[i].typeComets == (int)MidComets)
			{
				comets[i].cometsCollider.Position.x = rand() % GetScreenWidth();
				comets[i].cometsCollider.Position.y = rand() % GetScreenHeight();
				comets[i].cometsCollider.Radius = 30;
				comets[i].cometsIsLive = true;
				comets[i].cometsTrayectory = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };
			}
			else if (comets[i].typeComets == (int)BigComets)
			{
				comets[i].cometsCollider.Position.x = rand() % GetScreenWidth();
				comets[i].cometsCollider.Position.y = rand() % GetScreenHeight();
				comets[i].cometsCollider.Radius = 60;
				comets[i].cometsIsLive = true;
				comets[i].cometsTrayectory = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };
			}
			
		}
	}

	void MoveComets()
	{
		for (int i = 0; i < asteroidsCounter + 1; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				if (CheckCollision(comets[i].cometsCollider, bullet[j]))
				{
					bullet[j].Position.x = -100;
					bullet[j].Position.y = -100;
					if (comets[i].typeComets == (int)SmallComets)
					{
						comets[i].cometsCollider.Position.x = -(rand() % GetScreenWidth());
						comets[i].cometsCollider.Position.y = -(rand() % GetScreenHeight());
						comets[i].typeComets = rand() % 3 + 1;
						comets[i].cometsTrayectory = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };
					}
					else if (comets[i].typeComets == (int)MidComets)
					{
						asteroidsCounter++;

						comets[i].cometsCollider.Radius = 15;
						comets[i].cometsTrayectory = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };
						comets[i].typeComets = (int)SmallComets;

						comets[asteroidsCounter].cometsCollider.Position.x = comets[i].cometsCollider.Position.x;
						comets[asteroidsCounter].cometsCollider.Position.y = comets[i].cometsCollider.Position.y;
						comets[asteroidsCounter].cometsCollider.Radius = 15;
						comets[asteroidsCounter].cometsIsLive = true;
						comets[asteroidsCounter].cometsTrayectory = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };
						comets[asteroidsCounter].typeComets = (int)SmallComets;
					}
					else if (comets[i].typeComets == (int)BigComets)
					{
						asteroidsCounter++;

						comets[i].cometsCollider.Radius = 30;
						comets[i].cometsTrayectory = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };
						comets[i].typeComets = (int)MidComets;

						comets[asteroidsCounter].cometsCollider.Position.x = comets[i].cometsCollider.Position.x;
						comets[asteroidsCounter].cometsCollider.Position.y = comets[i].cometsCollider.Position.y;
						comets[asteroidsCounter].cometsCollider.Radius = 30;
						comets[asteroidsCounter].cometsIsLive = true;
						comets[asteroidsCounter].cometsTrayectory = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };
						comets[asteroidsCounter].typeComets = (int)MidComets;
					}
				}
			}

			if (comets[i].cometsIsLive)
			{
				comets[i].cometsCollider.Position.x += comets[i].cometsTrayectory.x * aceleration * GetFrameTime();
				comets[i].cometsCollider.Position.y += comets[i].cometsTrayectory.y * aceleration * GetFrameTime();

				if (comets[i].cometsCollider.Position.x > GetScreenWidth())
				{
					comets[i].cometsCollider.Position.x = 0;
				}
				if (comets[i].cometsCollider.Position.y > GetScreenHeight())
				{
					comets[i].cometsCollider.Position.y = 0;
				}
				if (comets[i].cometsCollider.Position.x < 0)
				{
					comets[i].cometsCollider.Position.x = GetScreenWidth();
				}
				if (comets[i].cometsCollider.Position.y < 0)
				{
					comets[i].cometsCollider.Position.y = GetScreenHeight();
				}
			}
		}
	}

	void DrawComets(Texture2D SmallSprite, Texture2D MidSprite, Texture2D BigSprite)
	{
		for (int i = 0; i < asteroidsCounter + 1; i++)
		{
			float rotation = 0;

			float arcTan = atan(comets[i].cometsTrayectory.y / comets[i].cometsTrayectory.x);

			float angle = arcTan * 180 / PI;

			if (comets[i].cometsTrayectory.x < comets[i].cometsCollider.Position.x && comets[i].cometsTrayectory.y < comets[i].cometsCollider.Position.y)
			{
				if (comets[i].cometsTrayectory.x < 0)
				{

					angle += 180;
				}
				else
				{
					angle += 360;
				}
				
			}
			if (comets[i].cometsTrayectory.x < comets[i].cometsCollider.Position.x && comets[i].cometsTrayectory.y > comets[i].cometsCollider.Position.y)
			{
				angle += 180;
			}
			if (comets[i].cometsTrayectory.x > comets[i].cometsCollider.Position.x && comets[i].cometsTrayectory.y > comets[i].cometsCollider.Position.y)
			{
				angle -= 360;
			}
			if (comets[i].cometsTrayectory.x > comets[i].cometsCollider.Position.x && comets[i].cometsTrayectory.y < comets[i].cometsCollider.Position.y)
			{
				angle -= 0;
			}

			rotation = angle + 90;
			
			Vector2 cometsPos = { comets[i].cometsCollider.Position.x, comets[i].cometsCollider.Position.y };

			if (comets[i].typeComets == 1)
			{
				Rectangle source = { 0, 0, SmallSprite.width, SmallSprite.height };
				Rectangle dest = { comets[i].cometsCollider.Position.x, comets[i].cometsCollider.Position.y, SmallSprite.width, SmallSprite.height};
				Vector2 origin = { SmallSprite.width / 2, SmallSprite.height / 2 };
				//DrawRectanglePro(dest, origin, rotation, WHITE);
				DrawTexturePro(SmallSprite,source ,dest, origin, rotation, WHITE);
				//DrawCircle(comets[i].cometsCollider.Position.x, comets[i].cometsCollider.Position.y, comets[i].cometsCollider.Radius, SKYBLUE);
			}
			else if (comets[i].typeComets == 2)
			{
				Rectangle source = { 0, 0, MidSprite.width, MidSprite.height };
				Rectangle dest = { comets[i].cometsCollider.Position.x, comets[i].cometsCollider.Position.y, MidSprite.width, MidSprite.height };
				Vector2 origin = { MidSprite.width / 2, MidSprite.height / 2 };
				//DrawRectanglePro(dest, origin, rotation, WHITE);
				DrawTexturePro(MidSprite, source, dest, origin, rotation, WHITE);
				//DrawCircle(comets[i].cometsCollider.Position.x, comets[i].cometsCollider.Position.y, comets[i].cometsCollider.Radius, BLUE);
			}
			else
			{
				Rectangle source = { 0, 0, BigSprite.width, BigSprite.height };
				Rectangle dest = { comets[i].cometsCollider.Position.x, comets[i].cometsCollider.Position.y, BigSprite.width, BigSprite.height };
				Vector2 origin = { BigSprite.width / 2, BigSprite.height / 2 };
				//DrawRectanglePro(dest, origin, rotation, WHITE);
				DrawTexturePro(BigSprite, source, dest, origin, rotation, WHITE);
				//DrawCircle(comets[i].cometsCollider.Position.x, comets[i].cometsCollider.Position.y, comets[i].cometsCollider.Radius, VIOLET);
			}
		}
	}
}
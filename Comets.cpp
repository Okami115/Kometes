#include "Comets.h"
#include "GameLoop.h"
#include "raymath.h"
#include "SpaceShip.h"
#include <iostream> 

namespace OkamiIndustries
{
	extern Texture2D SmallCometsTexture;
	extern Texture2D MidCometsTexture;
	extern Texture2D BigCometsTexture;

	static int maxComets = 10;
	static float cometsSpeed = 1.0f;
	static float aceleration = 500;
	int asteroidsCounter = 0;

	int ShootInpact = 1;
	extern int score;

	Comets comets[100];
	extern Circle bullet[100];

	void spawnComets()
	{
		ShootInpact = 1;
		for (int i = 0; i < 2; i++)
		{
			asteroidsCounter++;
			comets[i].cometsCollider.Position.x = -(static_cast <float>(rand() % GetScreenWidth()));
			comets[i].cometsCollider.Position.y = -(static_cast <float>(rand() % GetScreenHeight()));
			comets[i].cometsIsLive = true;
			comets[i].cometsTrayectory = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };

			comets[i].typeComets = rand() % 3 + 1;

			if (comets[i].typeComets == (int)SmallComets)
			{
				comets[i].cometsCollider.Radius = 15;
			}
			else if (comets[i].typeComets == (int)MidComets)
			{
				comets[i].cometsCollider.Radius = 30;
			}
			else if (comets[i].typeComets == (int)BigComets)
			{
				comets[i].cometsCollider.Radius = 40;
			}
			
		}
	}

	void destroyComets()
	{
		for (int i = 0; i < asteroidsCounter; i++)
		{
			comets[i].cometsCollider.Position.x = -1000;
			comets[i].cometsCollider.Position.y = -1000;
			comets[i].cometsIsLive = false;
		}
		asteroidsCounter = 0;
		spawnComets();
	}

	void MoveComets(Sound boom)
	{
		for (int i = 0; i < asteroidsCounter + 1; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				if (CheckCollision(comets[i].cometsCollider, bullet[j]))
				{
					bullet[j].Position.x = -100;
					bullet[j].Position.y = -100;
					PlaySound(boom);
					ShootInpact++;
					score++;
					if (comets[i].typeComets == (int)SmallComets)
					{
						comets[i].cometsCollider.Position.x = -static_cast <float>(rand() % GetScreenWidth());
						comets[i].cometsCollider.Position.y = -static_cast <float>(rand() % GetScreenHeight());
						comets[i].cometsIsLive = true;
						comets[i].cometsTrayectory = { (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 , (cometsSpeed * (float(rand()) / float(RAND_MAX))) - cometsSpeed / 2 };

						comets[i].typeComets = rand() % 3 + 1;

						if (comets[i].typeComets == (int)SmallComets)
						{
							comets[i].cometsCollider.Radius = 15;
						}
						else if (comets[i].typeComets == (int)MidComets)
						{
							comets[i].cometsCollider.Radius = 30;
						}
						else if (comets[i].typeComets == (int)BigComets)
						{
							comets[i].cometsCollider.Radius = 40;
						}
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

				if (comets[i].cometsCollider.Position.x > static_cast <float>(GetScreenWidth()))
				{
					comets[i].cometsCollider.Position.x = 0;
				}
				if (comets[i].cometsCollider.Position.y > static_cast <float>(GetScreenHeight()))
				{
					comets[i].cometsCollider.Position.y = 0;
				}
				if (comets[i].cometsCollider.Position.x < 0)
				{
					comets[i].cometsCollider.Position.x = static_cast <float>(GetScreenWidth());
				}
				if (comets[i].cometsCollider.Position.y < 0)
				{
					comets[i].cometsCollider.Position.y = static_cast <float>(GetScreenHeight());
				}
			}
		}
	}

	void DrawComets()
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
				Rectangle source = { 0, 0, static_cast <float>(SmallCometsTexture.width), static_cast <float>(SmallCometsTexture.height) };
				Rectangle dest = { comets[i].cometsCollider.Position.x, comets[i].cometsCollider.Position.y, static_cast <float>(SmallCometsTexture.width), static_cast <float>(SmallCometsTexture.height)};
				Vector2 origin = { static_cast <float>(SmallCometsTexture.width) / 2, static_cast <float>(SmallCometsTexture.height) / 2 };
				DrawCircle(static_cast <int>(comets[i].cometsCollider.Position.x), static_cast <int>(comets[i].cometsCollider.Position.y), static_cast <float>(comets[i].cometsCollider.Radius), SKYBLUE);
				DrawTexturePro(SmallCometsTexture,source ,dest, origin, rotation, WHITE);
			}
			else if (comets[i].typeComets == 2)
			{
				Rectangle source = { 0, 0, static_cast <float>(MidCometsTexture.width), static_cast <float>(MidCometsTexture.height) };
				Rectangle dest = { comets[i].cometsCollider.Position.x, comets[i].cometsCollider.Position.y, static_cast <float>(MidCometsTexture.width), static_cast <float>(MidCometsTexture.height) };
				Vector2 origin = { static_cast <float>(MidCometsTexture.width) / 2, static_cast <float>(MidCometsTexture.height) / 2 };
				DrawCircle(static_cast <int>(comets[i].cometsCollider.Position.x), static_cast <int>(comets[i].cometsCollider.Position.y), static_cast <float>(comets[i].cometsCollider.Radius), BLUE);
				DrawTexturePro(MidCometsTexture, source, dest, origin, rotation, WHITE);
			}
			else
			{
				Rectangle source = { 0, 0, static_cast <float>(BigCometsTexture.width), static_cast <float>(BigCometsTexture.height) };
				Rectangle dest = { comets[i].cometsCollider.Position.x, comets[i].cometsCollider.Position.y, static_cast <float>(BigCometsTexture.width), static_cast <float>(BigCometsTexture.height) };
				Vector2 origin = { static_cast <float>(BigCometsTexture.width) / 2, static_cast <float>(BigCometsTexture.height) / 2 };
				DrawCircle(static_cast <int>(comets[i].cometsCollider.Position.x), static_cast <int>(comets[i].cometsCollider.Position.y), static_cast <float>(comets[i].cometsCollider.Radius), VIOLET);
				DrawTexturePro(BigCometsTexture, source, dest, origin, rotation, WHITE);
			}
		}
	}
}
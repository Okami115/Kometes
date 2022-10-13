#include "raylib.h"
#include "Hunter.h"
#include "raymath.h"
#include "SpaceShip.h"
#include <iostream>

namespace OkamiIndustries
{
	extern Circle SpaceShipColider;
	extern Circle bullet[100];

	extern Sound Boom;

	extern int ShootInpact;
	extern int score;

	extern Texture2D HunterTexture;
	Hunter hunter;

	static float rotated = 0;
	float hunterAceleration = 100.0f;
	float hunterTimer = 0;

	void SpawnHunter()
	{
		hunter.hunterCollider.Position.x = (static_cast <float>(rand() % GetScreenWidth())) * 2;
		hunter.hunterCollider.Position.y = (static_cast <float>(rand() % GetScreenHeight())) * 2;
	}

	void DestroyHunter()
	{
		hunter.hunterCollider.Position.x = -100;
		hunter.hunterCollider.Position.y = -100;
		hunterTimer = 0;
		SpawnHunter();
	}

	void HunterLoop()
	{
		hunterTimer += GetFrameTime();
		hunter.hunterCollider.Radius = 20;
		Vector2 normalDir = { 0,0 };
		Vector2 Dif = { 0,0 };

		Dif.x = hunter.hunterCollider.Position.x - SpaceShipColider.Position.x;
		Dif.y = hunter.hunterCollider.Position.y - SpaceShipColider.Position.y;

		float arcTan = static_cast <float>(atan(Dif.y / Dif.x));

		float angle = arcTan * 180 / PI;

		float Module = static_cast <float>(sqrt(pow(Dif.x, 2) + pow(Dif.y, 2)));

		normalDir = { Dif.x / Module, Dif.y / Module };

		if (SpaceShipColider.Position.x < hunter.hunterCollider.Position.x && SpaceShipColider.Position.y < hunter.hunterCollider.Position.y)
		{
			angle += 180;
		}
		if (SpaceShipColider.Position.x < hunter.hunterCollider.Position.x && SpaceShipColider.Position.y > hunter.hunterCollider.Position.y)
		{
			angle += 180;
		}
		if (SpaceShipColider.Position.x > hunter.hunterCollider.Position.x && SpaceShipColider.Position.y > hunter.hunterCollider.Position.y)
		{
			angle += 360;
		}

		rotated = angle + 90;
		hunter.hunterTrayectory = normalDir;

		if (hunterTimer > 15.0f)
		{
			hunter.hunterCollider.Position.x -= hunter.hunterTrayectory.x * hunterAceleration * GetFrameTime();
			hunter.hunterCollider.Position.y -= hunter.hunterTrayectory.y * hunterAceleration * GetFrameTime();

			for (int i = 0; i < 100; i++)
			{
				if (CheckCollision(hunter.hunterCollider, bullet[i]))
				{
					bullet[i].Position.x = -100;
					bullet[i].Position.y = -100;
					PlaySound(Boom);
					ShootInpact++;
					score++;
					DestroyHunter();
				}
			}

			if (hunter.hunterCollider.Position.x > static_cast <float>(GetScreenWidth()))
			{
				hunter.hunterCollider.Position.x = 0;
			}
			if (hunter.hunterCollider.Position.y > static_cast <float>(GetScreenHeight()))
			{
				hunter.hunterCollider.Position.y = 0;
			}
			if (hunter.hunterCollider.Position.x < 0)
			{
				hunter.hunterCollider.Position.x = static_cast <float>(GetScreenWidth());
			}
			if (hunter.hunterCollider.Position.y < 0)
			{
				hunter.hunterCollider.Position.y = static_cast <float>(GetScreenHeight());
			}
		}
	}

	void DrawHunter()
	{
		if (hunterTimer > 15.0f)
		{
			Rectangle source = { 0, 0, static_cast <float>(HunterTexture.width), static_cast <float>(HunterTexture.height) };
			Rectangle dest = { hunter.hunterCollider.Position.x, hunter.hunterCollider.Position.y, static_cast <float>(HunterTexture.width), static_cast <float>(HunterTexture.height) };
			Vector2 origin = { static_cast <float>(HunterTexture.width) / 2, static_cast <float>(HunterTexture.height) / 2 };
			DrawTexturePro(HunterTexture, source, dest, origin, rotated, WHITE);
		}
	}
}
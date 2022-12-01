#include "raylib.h"
#include <iostream> 
#include "../Comets/Comets.h"
#include "../SpaceShip/SpaceShip.h"

namespace OkamiIndustries
{
	struct PowerUp
	{
		Circle PowerUpCollider;
		Vector2 PowerUpTrayectory;
	};

	static float powerUpSpeed = 1.0f;
	static float aceleration = 500;

	bool isFullAutoActive = false;
	extern int AutoCounter;

	extern Texture2D KaboomTexture;
	extern Sound KaboomSound;

	extern Texture2D FullAutoTexture;
	extern Sound FullAutoSound;

	extern Circle SpaceShipColider;

	PowerUp Kaboom;
	PowerUp FullAuto;

	float timerKaboom = 0;
	float timerFullAuto = 0;

	void SpawnKaboom()
	{
		Kaboom.PowerUpCollider.Position.x = -(static_cast <float>(rand() % GetScreenWidth()));
		Kaboom.PowerUpCollider.Position.y = -(static_cast <float>(rand() % GetScreenHeight()));
		Kaboom.PowerUpCollider.Radius = 25;
		Kaboom.PowerUpTrayectory = { (powerUpSpeed * (float(rand()) / float(RAND_MAX))) - powerUpSpeed / 2 , (powerUpSpeed * (float(rand()) / float(RAND_MAX))) - powerUpSpeed / 2 };
	}	
	void SpawnFullAuto()
	{
		FullAuto.PowerUpCollider.Position.x = -(static_cast <float>(rand() % GetScreenWidth()));
		FullAuto.PowerUpCollider.Position.y = -(static_cast <float>(rand() % GetScreenHeight()));
		FullAuto.PowerUpCollider.Radius = 25;
		FullAuto.PowerUpTrayectory = { (powerUpSpeed * (float(rand()) / float(RAND_MAX))) - powerUpSpeed / 2 , (powerUpSpeed * (float(rand()) / float(RAND_MAX))) - powerUpSpeed / 2 };
	}

	void PowerUpsLoop()
	{
		timerKaboom += GetFrameTime();
		timerFullAuto += GetFrameTime();
		if (timerKaboom > 15.0f)
		{
			Kaboom.PowerUpCollider.Position.x += Kaboom.PowerUpTrayectory.x * aceleration * GetFrameTime();
			Kaboom.PowerUpCollider.Position.y += Kaboom.PowerUpTrayectory.y * aceleration * GetFrameTime();

			if (CheckCollision(Kaboom.PowerUpCollider, SpaceShipColider))
			{
				destroyComets();
				SpawnKaboom();
				PlaySound(KaboomSound);
				timerKaboom = 0;
			}

			if (Kaboom.PowerUpCollider.Position.x > static_cast <float>(GetScreenWidth()))
			{
				Kaboom.PowerUpCollider.Position.x = 0;
			}
			if (Kaboom.PowerUpCollider.Position.y > static_cast <float>(GetScreenHeight()))
			{
				Kaboom.PowerUpCollider.Position.y = 0;
			}
			if (Kaboom.PowerUpCollider.Position.x < 0)
			{
				Kaboom.PowerUpCollider.Position.x = static_cast <float>(GetScreenWidth());
			}
			if (Kaboom.PowerUpCollider.Position.y < 0)
			{
				Kaboom.PowerUpCollider.Position.y = static_cast <float>(GetScreenHeight());
			}
		}
		if (timerFullAuto > 5.0f)
		{
			FullAuto.PowerUpCollider.Position.x += FullAuto.PowerUpTrayectory.x * aceleration * GetFrameTime();
			FullAuto.PowerUpCollider.Position.y += FullAuto.PowerUpTrayectory.y * aceleration * GetFrameTime();

			if (CheckCollision(FullAuto.PowerUpCollider, SpaceShipColider))
			{
				isFullAutoActive = true;
				AutoCounter = 0;
				SpawnFullAuto();
				PlaySound(FullAutoSound);
				timerFullAuto = 0;
			}

			if (FullAuto.PowerUpCollider.Position.x > static_cast <float>(GetScreenWidth()))
			{
				FullAuto.PowerUpCollider.Position.x = 0;
			}
			if (FullAuto.PowerUpCollider.Position.y > static_cast <float>(GetScreenHeight()))
			{
				FullAuto.PowerUpCollider.Position.y = 0;
			}
			if (FullAuto.PowerUpCollider.Position.x < 0)
			{
				FullAuto.PowerUpCollider.Position.x = static_cast <float>(GetScreenWidth());
			}
			if (FullAuto.PowerUpCollider.Position.y < 0)
			{
				FullAuto.PowerUpCollider.Position.y = static_cast <float>(GetScreenHeight());
			}
		}
	}

	void DrawPowerUps()
	{
		if (timerKaboom > 15.0f)
		{
			Rectangle source = { 0, 0, static_cast <float>(KaboomTexture.width), static_cast <float>(KaboomTexture.height) };
			Rectangle dest = { Kaboom.PowerUpCollider.Position.x, Kaboom.PowerUpCollider.Position.y, static_cast <float>(KaboomTexture.width), static_cast <float>(KaboomTexture.height) };
			Vector2 origin = { static_cast <float>(KaboomTexture.width) / 2, static_cast <float>(KaboomTexture.height) / 2 };
			DrawTexturePro(KaboomTexture, source, dest, origin, 0, WHITE);
		}

		if (timerFullAuto > 5.0f)
		{
			Rectangle source = { 0, 0, static_cast <float>(FullAutoTexture.width), static_cast <float>(FullAutoTexture.height) };
			Rectangle dest = { FullAuto.PowerUpCollider.Position.x, FullAuto.PowerUpCollider.Position.y, static_cast <float>(FullAutoTexture.width), static_cast <float>(FullAutoTexture.height) };
			Vector2 origin = { static_cast <float>(FullAutoTexture.width) / 2, static_cast <float>(FullAutoTexture.height) / 2 };
			DrawTexturePro(FullAutoTexture, source, dest, origin, 0, WHITE);
		}
	}

}

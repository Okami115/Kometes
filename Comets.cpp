#include "Comets.h"
#include "GameLoop.h"
#include "SpaceShip.h"
#include <iostream> 

namespace OkamiIndustries
{
	void spawnComets(Circle& comets)
	{

		comets.Radius = rand() % 50 + 10;
		comets.Position.x = 0;
		comets.Position.y = rand() % GetScreenHeight();
	}

	void MoveComets(Circle& comets)
	{

		comets.Position.x++;
		comets.Position.y++;

		if (comets.Position.x > GetScreenWidth())
		{
			comets.Position.x = 0;
		}
		if (comets.Position.y > GetScreenHeight())
		{
			comets.Position.y = 0;
		}

	}

	void DrawComets(Circle& comets, Circle spaceShip, Circle bullets)
	{
		if (CheckCollisionSpaceShip(comets, spaceShip))
		{
			DrawCircle(comets.Position.x, comets.Position.y, comets.Radius, RED);
		}
		if (CheckCollisionSpaceShip(comets, bullets))
		{
			DrawCircle(comets.Position.x, comets.Position.y, comets.Radius, RED);
		}
		else
		{
			DrawCircle(comets.Position.x, comets.Position.y, comets.Radius, WHITE);
		}
		
	}
}
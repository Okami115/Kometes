#pragma once
#include "raylib.h"
#include "GameLoop.h"

namespace OkamiIndustries
{
	void spawnShip();
	void MoveSpaceShip();
	void DrawSpaceShip(Texture2D SpaceShip);
	bool CheckCollision(Circle SpaceShipColider, Circle Comets);
	void DrawBullets();
	void initBullets();
}
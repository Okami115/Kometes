#pragma once
#include "raylib.h"
#include "GameLoop.h"

namespace OkamiIndustries
{
	void MoveSpaceShip(Vector2& shipPosition);
	void DrawSpaceShip(Rectangle shipRectangle, Vector2 OriginSpaceShip, Vector2 shipPosition, Texture2D SpaceShip, Circle& SpaceShipColider, Circle Comets);
	bool CheckCollisionSpaceShip(Circle SpaceShipColider, Circle Comets);
}
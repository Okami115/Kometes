#pragma once
#include "raylib.h"

namespace OkamiIndustries
{

	struct Circle
	{
		Vector2 Position;
		int Radius;
	};

	void gameloop(Sound Hit, Sound Shoot, Sound boom);
	void DrawGame(Texture2D Background, Vector2 BackgroudPosition, Texture2D SpaceShip, Texture2D SmallComets, Texture2D MidComets, Texture2D BigComets, int asteroidsCounter);
}

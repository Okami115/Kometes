#pragma once
#include "../SpaceShip/SpaceShip.h"

namespace OkamiIndustries
{
	struct Hunter
	{
		Circle hunterCollider;
		Vector2 hunterTrayectory;
	};

	void SpawnHunter();
	void DestroyHunter();
	void HunterLoop();
	void DrawHunter();
}
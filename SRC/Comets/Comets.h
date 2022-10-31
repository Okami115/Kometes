#pragma once
#include "../GameLoop/GameLoop.h"

namespace OkamiIndustries
{
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

	void MoveComets(Sound boom);
	void spawnComets();
	void destroyComets();
	void DrawComets();

}


#pragma once
#include "GameLoop.h"

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
	void DrawComets(Texture2D SmallSprite, Texture2D MidSprite, Texture2D BigSprite);

}


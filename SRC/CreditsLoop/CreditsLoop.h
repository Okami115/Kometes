#pragma once
#include "raylib.h"

namespace OkamiIndustries
{
	void CreditsLoop(int& selectMenu, int& setLoop);
	void DrawCredits(Texture2D BackgroundCredits, Vector2 BackgroudCreditsPosition, Texture2D Back, Texture2D BackSelect, int selectMenu);
}
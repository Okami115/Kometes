#pragma once

namespace OkamiIndustries
{
	void LoopMenu(int& selectMenu, int& setLoop);
	void DrawMenu(int selectMenu, Texture2D BackgroundMenu, Vector2 BackgroudMenuPosition, Texture2D PlaySelect, Texture2D Play, Texture2D Options, Texture2D OptionsSelect, Texture2D Credits, Texture2D CreditsSelect, Texture2D Exit, Texture2D ExitSelect);
}
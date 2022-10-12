#include "CoreLoop.h"
#include "raylib.h"
#include "raymath.h"
#include "SpaceShip.h"
#include "Comets.h"
#include "GameLoop.h"
#include "CreditsLoop.h"
#include <iostream> 
#include <time.h> 
#include "menu.h"


namespace OkamiIndustries
{
	void initGame()
	{
		int selectMenu = 0;
		int setLoop = 0;

		const int screenWidth = 1920;
		const int screenHeight = 1080;

		SetRandomSeed(NULL);

		InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.22");

		InitAudioDevice();

		Sound Shoot = LoadSound("assets/Shoot.wav");
		Sound Boom = LoadSound("assets/boom.wav");
		Sound Hit = LoadSound("assets/Hit.wav");

		Texture2D SpaceShip = LoadTexture("assets/SpaceShip.png");
		SpaceShip.width = SpaceShip.width / 2;
		SpaceShip.height = SpaceShip.height / 2;

		Texture2D Background = LoadTexture("assets/Background.png");
		Vector2 BackgroudPosition = { 0, 0 };

		Texture2D BackgroundMenu = LoadTexture("assets/BackgroundMenu.png");
		Vector2 BackgroudMenuPosition = { 0, 0 };
		Texture2D Play = LoadTexture("assets/playNotSelect.png");
		Texture2D PlaySelect = LoadTexture("assets/PlaySelect.png");
		Texture2D options = LoadTexture("assets/OptionsNotSelect.png");;
		Texture2D optionsSelect = LoadTexture("assets/OptionsSelect.png");
		Texture2D credits = LoadTexture("assets/CreditsNotSelect.png");
		Texture2D creditsSelect = LoadTexture("assets/CreditsSelect.png");
		Texture2D exit = LoadTexture("assets/ExitNotSelect.png");
		Texture2D exitSelect = LoadTexture("assets/ExitSelect.png");

		Texture2D BackgroundCredits = LoadTexture("assets/BackgroundCredits.png");
		Vector2 BackgroudCreditsPosition = { 0, 0 };
		Texture2D Back = LoadTexture("assets/BackNotSelect.png");
		Texture2D BackSelect = LoadTexture("assets/BackSelect.png");

		spawnComets();
		spawnShip();
		Texture2D SmallComets = LoadTexture("assets/Comets Small.png");
		Texture2D MidComets = LoadTexture("assets/Mid Comets.png");
		Texture2D BigComets = LoadTexture("assets/Big Comets.png");

		extern int asteroidsCounter;

		initBullets();


		while (!WindowShouldClose())
		{
			std::cout << setLoop << std::endl;

			switch (setLoop)
			{
			case 0:
			{
				LoopMenu(selectMenu, setLoop);
				break;
			}
			case 1:
			{
				gameloop(Hit, Shoot, Boom);
				break;
			}
			case 2:
			{
				
			}
			case 3:
			{
				CreditsLoop(selectMenu, setLoop);
				break;
			}
			case 4:
			{

			}
			default:
				break;
			}

			BeginDrawing();

			ClearBackground(BLACK);
			switch (setLoop)
			{
			case 0:
			{
				DrawMenu(selectMenu,BackgroundMenu, BackgroudMenuPosition, PlaySelect, Play, options, optionsSelect,credits, creditsSelect, exit, exitSelect);
				break;
			}
			case 1:
			{
				DrawGame(Background, BackgroudPosition, SpaceShip, SmallComets, MidComets, BigComets, asteroidsCounter);
				break;
			}
			case 2:
			{

			}
			case 3:
			{
				DrawCredits(BackgroundCredits, BackgroudCreditsPosition, Back, BackSelect, selectMenu);
				break;
			}
			case 4:
			{

			}
			default:
				break;
			}
			EndDrawing();
		}



		UnloadTexture(SpaceShip);
		UnloadTexture(Background);
		UnloadTexture(SmallComets);
		UnloadTexture(MidComets);
		UnloadTexture(BigComets);
		UnloadSound(Boom);
		UnloadSound(Shoot);
		UnloadSound(Hit);

		CloseAudioDevice();
		CloseWindow();
	}

}
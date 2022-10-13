#include "CoreLoop.h"
#include "raylib.h"
#include "raymath.h"
#include "SpaceShip.h"
#include "Comets.h"
#include "GameLoop.h"
#include "ExitLoop.h"
#include "CreditsLoop.h"
#include <iostream> 
#include <time.h> 
#include "menu.h"


namespace OkamiIndustries
{
	int selectMenu = 0;
	int setLoop = 0;

	int score = 0;

	bool isGameActive = true;

	const int screenWidth = 1024;
	const int screenHeight = 768;

	Vector2 BackgroudPosition = { 0, 0 };
	Vector2 BackgroudMenuPosition = { -150, 0 };
	Vector2 BackgroudCreditsPosition = { -190, 0 };
	
#pragma region Texture&Sound
	Sound Shoot;
	Sound Boom;
	Sound Hit;

	Texture2D SpaceShip;

	Texture2D banner;
	Texture2D Background;
	Texture2D BackgroundMenu;
	Texture2D BackgroundCredits;
	
	Texture2D PauseMenu;

	Texture2D Play;
	Texture2D PlaySelect;
	Texture2D options;
	Texture2D optionsSelect;
	Texture2D credits;
	Texture2D creditsSelect;
	Texture2D exit;
	Texture2D exitSelect;
	Texture2D Back;
	Texture2D BackSelect;
	Texture2D Pause;
	Texture2D PauseSelect;
	Texture2D BackMenu;
	Texture2D BackMenuSelect;
	Texture2D Resume;
	Texture2D ResumeSelect;
	Texture2D Cancel;
	Texture2D CancelSelect;


	Texture2D SmallCometsTexture;
	Texture2D MidCometsTexture;
	Texture2D BigCometsTexture;
#pragma endregion

	static void initWin()
	{
		SetRandomSeed(NULL);

		InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.25");

		InitAudioDevice();

	}

	static void LoadGame()
	{
		Shoot = LoadSound("assets/Shoot.wav");
		Boom = LoadSound("assets/boom.wav");
		Hit = LoadSound("assets/Hit.wav");

		SpaceShip = LoadTexture("assets/SpaceShip.png");

		banner = LoadTexture("assets/Banner.png");
		Background = LoadTexture("assets/Background.png");
		BackgroundMenu = LoadTexture("assets/BackgroundMenu768.png");
		BackgroundCredits = LoadTexture("assets/BackgroundCredits768.png");

		Play = LoadTexture("assets/playNotSelect.png");
		PlaySelect = LoadTexture("assets/PlaySelect.png");
		options = LoadTexture("assets/OptionsNotSelect.png");
		optionsSelect = LoadTexture("assets/OptionsSelect.png");
		credits = LoadTexture("assets/CreditsNotSelect.png");
		creditsSelect = LoadTexture("assets/CreditsSelect.png");
		exit = LoadTexture("assets/ExitNotSelect.png");
		exitSelect = LoadTexture("assets/ExitSelect.png");
		Back = LoadTexture("assets/BackNotSelect.png");
		BackSelect = LoadTexture("assets/BackSelect.png");
		PauseMenu = LoadTexture("assets/PauseMenu.png");
		Pause = LoadTexture("assets/PauseNotSelect.png");
		PauseSelect = LoadTexture("assets/PauseSelect.png");
		BackMenu = LoadTexture("assets/BackMenuNotSelect.png");
		BackMenuSelect = LoadTexture("assets/BackMenuSelect.png");
		Resume = LoadTexture("assets/ResumeNotSelect.png");
		ResumeSelect = LoadTexture("assets/ResumeSelect.png");
		Cancel = LoadTexture("assets/CancelNotSelect.png");
		CancelSelect = LoadTexture("assets/CancelSelect.png");

		SmallCometsTexture = LoadTexture("assets/Comets Small.png");
		MidCometsTexture = LoadTexture("assets/Mid Comets.png");
		BigCometsTexture = LoadTexture("assets/Big Comets.png");

		SpaceShip.width = SpaceShip.width / 2;
		SpaceShip.height = SpaceShip.height / 2;
	}

	static void closeWindow()
	{
		UnloadTexture(SpaceShip);

		UnloadTexture(banner);
		UnloadTexture(Background);
		UnloadTexture(BackgroundMenu);
		UnloadTexture(BackgroundCredits);

		UnloadTexture(PauseMenu);
		UnloadTexture(Play);
		UnloadTexture(PlaySelect);
		UnloadTexture(options);
		UnloadTexture(optionsSelect);
		UnloadTexture(credits);
		UnloadTexture(creditsSelect);
		UnloadTexture(exit);
		UnloadTexture(exitSelect);
		UnloadTexture(Back);
		UnloadTexture(BackSelect);
		UnloadTexture(Pause);
		UnloadTexture(PauseSelect);
		UnloadTexture(BackMenu);
		UnloadTexture(BackMenuSelect);
		UnloadTexture(Resume);
		UnloadTexture(ResumeSelect);
		UnloadTexture(Cancel);
		UnloadTexture(CancelSelect);

		UnloadTexture(SmallCometsTexture);
		UnloadTexture(MidCometsTexture);
		UnloadTexture(BigCometsTexture);

		UnloadSound(Boom);
		UnloadSound(Shoot);
		UnloadSound(Hit);

		CloseAudioDevice();
		CloseWindow();
	}

	void initGame()
	{
		initWin();
		LoadGame();
		spawnComets();
		spawnShip();

		extern int asteroidsCounter;

		initBullets();


		while (!WindowShouldClose() && isGameActive)
		{

			switch (setLoop)
			{
			case 0:
			{
				LoopMenu(selectMenu, setLoop);
				break;
			}
			case 1:
			{
				gameloop();
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
				ExitLoop();
				break;
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
				DrawGame();
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
				DrawExit();
			}
			default:
				break;
			}
			EndDrawing();
		}


		closeWindow();

	}

}
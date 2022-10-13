#include "CoreLoop.h"
#include "raylib.h"
#include "raymath.h"
#include "SpaceShip.h"
#include "Hunter.h"
#include "Comets.h"
#include "GameLoop.h"
#include "HowToPlay.h"
#include "PowerUpsLoop.h"
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

	int screenWidth = 1024;
	int screenHeight = 768;

	Vector2 BackgroudPosition = { 0, 0 };
	Vector2 BackgroudHowToPlayPosition = { 0, 0 };
	Vector2 BackgroudMenuPosition = { -150, 0 };
	Vector2 BackgroudCreditsPosition = { -190, 0 };
	
#pragma region Texture&Sound
	Sound Shoot;
	Sound Boom;
	Sound Hit;
	Sound KaboomSound;
	Sound FullAutoSound;

	Texture2D SpaceShip;

	Texture2D boomAnimation;

	Texture2D banner;
	Texture2D Background;
	Texture2D BackgroundMenu;
	Texture2D BackgroundCredits;
	Texture2D BackgroundHowToPlay;
	
	Texture2D PauseMenu;

	Texture2D Play;
	Texture2D PlaySelect;
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
	Texture2D HowToPlay;
	Texture2D HowToPlaySelect;

	Texture2D KaboomTexture;
	Texture2D FullAutoTexture;

	Texture2D Sight;
	Texture2D Cursor;

	Texture2D SmallCometsTexture;
	Texture2D MidCometsTexture;
	Texture2D BigCometsTexture;
	Texture2D HunterTexture;
#pragma endregion

	void initWin()
	{
		SetRandomSeed(NULL);

		InitWindow(screenWidth, screenHeight, "OkamiIndustries T - 03 || Kometes || V0.30");

		InitAudioDevice();
	}

	void LoadGame()
	{
		Shoot = LoadSound("assets/Shoot.wav");
		Boom = LoadSound("assets/boom.wav");
		Hit = LoadSound("assets/Hit.wav");
		KaboomSound = LoadSound("assets/Kaboom.wav");
		FullAutoSound = LoadSound("assets/FullAuto.wav");

		SpaceShip = LoadTexture("assets/SpaceShip.png");

		boomAnimation = LoadTexture("assets/boomAnimation.png");

		banner = LoadTexture("assets/Banner.png");
		Background = LoadTexture("assets/Background.png");
		BackgroundHowToPlay = LoadTexture("assets/BackgroundHowToPlay768.png");
		BackgroundMenu = LoadTexture("assets/BackgroundMenu768.png");
		BackgroundCredits = LoadTexture("assets/BackgroundCredits768.png");

		Play = LoadTexture("assets/playNotSelect.png");
		PlaySelect = LoadTexture("assets/PlaySelect.png");
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
		HowToPlay = LoadTexture("assets/HowToPlayNotSelect.png");
		HowToPlaySelect = LoadTexture("assets/HowToPlaySelect.png");

		KaboomTexture = LoadTexture("assets/Kaboom.png");
		FullAutoTexture = LoadTexture("assets/FullAuto.png");

		Sight = LoadTexture("assets/Sight.png");
		Cursor = LoadTexture("assets/Cursor.png");

		SmallCometsTexture = LoadTexture("assets/Comets Small.png");
		MidCometsTexture = LoadTexture("assets/Mid Comets.png");
		BigCometsTexture = LoadTexture("assets/Big Comets.png");
		HunterTexture = LoadTexture("assets/Hunter.png");

		SpaceShip.width = SpaceShip.width / 2;
		SpaceShip.height = SpaceShip.height / 2;
	}

	void closeWindow()
	{
		UnloadTexture(SpaceShip);

		UnloadTexture(boomAnimation);

		UnloadTexture(banner);
		UnloadTexture(Background);
		UnloadTexture(BackgroundHowToPlay);
		UnloadTexture(BackgroundMenu);
		UnloadTexture(BackgroundCredits);

		UnloadTexture(PauseMenu);
		UnloadTexture(Play);
		UnloadTexture(PlaySelect);
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
		UnloadTexture(HowToPlay);
		UnloadTexture(HowToPlaySelect);

		UnloadTexture(KaboomTexture);
		UnloadTexture(FullAutoTexture);

		UnloadTexture(Sight);
		UnloadTexture(Cursor);

		UnloadTexture(SmallCometsTexture);
		UnloadTexture(MidCometsTexture);
		UnloadTexture(BigCometsTexture);
		UnloadTexture(HunterTexture);

		UnloadSound(Boom);
		UnloadSound(Shoot);
		UnloadSound(Hit);
		UnloadSound(KaboomSound);
		UnloadSound(FullAutoSound);

		CloseAudioDevice();
		CloseWindow();
	}

	void initGame()
	{
		initWin();
		LoadGame();
		spawnComets();
		spawnShip();
		SpawnKaboom();
		SpawnFullAuto();
		SpawnHunter();

		extern int asteroidsCounter;

		initBullets();


		while (!WindowShouldClose() && isGameActive)
		{
			switch (setLoop)
			{
			case 0:
			{
				LoopMenu();
				break;
			}
			case 1:
			{
				gameloop();
				break;
			}
			case 2:
			{
				HowToPlayLoop();
				break;
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
				DrawMenu();
				break;
			}
			case 1:
			{
				DrawGame();
				break;
			}
			case 2:
			{
				DrawHowToPlay();
				break;
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
#pragma once
#include "Include/GameWindows.h"

GameWindows::GameWindows()
{
	countedFrames = 0;
}

GameWindows::~GameWindows()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
}

bool GameWindows::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
			printf("Unable to init TTF: %s\n", SDL_GetError());
			success = false;
		}

		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Catgirl & Shotgun Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //SDL_WINDOW_RESIZABLE
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				//new code for the sound here==================
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
				Mix_AllocateChannels(48); //allocate audio channels

				SDL_Surface* sf = IMG_Load("assets-main/sprites/ui/boot_splash/icon-circle.png");
				SDL_SetWindowIcon(gWindow, sf);
			}
		}
	}

	//set base scaling
	SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	return success;
}

#pragma region Common_Function
void GameWindows::frameCap(
	player& myPlayer
)
{
	//Calculate and correct fps
	float avgFPS = countedFrames / (systemTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	++countedFrames;

	//If frame finished early
	int frameTicks = deltaTimer.getTicks();
	if (frameTicks < SCREEN_TICK_PER_FRAME)
	{
		//Wait remaining time
		SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
	}

	std::string title = "Catgirl & Shotgun Project [avg fps: " + std::to_string(int(avgFPS)) + "] " +
		" [X:" + std::to_string(int(myPlayer.px)) + ", Y:" + std::to_string(int(myPlayer.py)) + "]";
	SDL_SetWindowTitle(gWindow, title.c_str());
}

void GameWindows::clearScreen()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 0);
	SDL_RenderClear(gRenderer);
}
#pragma endregion











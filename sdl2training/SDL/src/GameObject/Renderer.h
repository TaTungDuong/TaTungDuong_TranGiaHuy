#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GameManager/Singleton.h"
//#include "Include/Player.h"
#include "Include/Global.h"

extern LTimer deltaTimer;
extern LTimer systemTimer;

class Renderer :public CSingleton<Renderer>{
public:
	Renderer();
	~Renderer();
	bool Init();
	SDL_Window* GetWindow();
	void SetWindow(SDL_Window* mWindow);
	SDL_Renderer* GetRenderer();
	void SetRenderer(SDL_Renderer* mRenderer);

	void frameCap();
private:
	int countedFrames;
};
#pragma once
#include "Include/Global.h"
#include "Include/Graphics.h"
#include "Include/Timer.h"
#include "Include/SpriteSheet.h"

extern LTimer deltaTimer;
extern LTimer systemTimer;
class GameWindows :public CSingleton<GameWindows>
{
public:
	GameWindows();
	~GameWindows();
	bool init(); //check and create a windows

#pragma region Common_Function
	void frameCap(
		player& myPlayer
	);
	void clearScreen();
#pragma endregion

	int countedFrames;
};

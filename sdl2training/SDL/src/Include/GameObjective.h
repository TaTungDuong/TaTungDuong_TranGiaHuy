#pragma once
#include "Include/Global.h"
#include "Include/Graphics.h"
#include "Sound.h"

#include "Include/Player.h"
#include "Include/Signal.h"

class GameObjective
{
public:
#pragma region Objectives
	int totalZombieKilled = 0;
	bool tutorial = true;
	int currentObjective = 4;// -1;
	bool objective[TOTAL_OBJECTIVE];
	std::string objectiveText;
	int timeLeft = TIME_LIMIT;
	//objective goals
	int obj_zombieKilled = 0;
	bool obj_keyPressed[4] = { false, false, false, false }; //whether w, a, s, d have been pressed
	int obj_zones;
#pragma endregion

//	GameObjective();
	void checkPreObjective();
	void checkObjective0(int key);
	void checkObjective1();
	void checkObjective2();
	void checkObjective3();
	void checkObjective4();
};
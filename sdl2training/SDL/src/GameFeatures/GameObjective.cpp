#include "Include/GameObjective.h"

GameObjective::GameObjective()
{
	boss = false;
	currentObjective = -1; 
	obj_zombieKilled = 0;
	totalZombieKilled = 0;
	for (int i = 0; i < 4; i++)
	{
		obj_keyPressed[i] = false;
	}
	tutorial = true;
}

void GameObjective::checkObjective0(int key)
{
	if (currentObjective == 0)
	{

		obj_keyPressed[key] = true;
		if (obj_keyPressed[0] && obj_keyPressed[1] && obj_keyPressed[2] && obj_keyPressed[3])
		{
			objective[0] = true;
		}
	}
}

void  GameObjective::checkObjective1()
{
	if (currentObjective == 1)
	{
		objective[1] = true;
	}
}
void GameObjective::checkObjective2()
{
	if (currentObjective == 2)
	{
		objective[2] = true;
		tutorial = false;
	}
}
void GameObjective::checkObjective3()
{
	if (currentObjective == 3)
	{

		obj_zombieKilled++;

		if (obj_zombieKilled >= ZOMBIE_NEEDED_TO_KILL) //killed required amount of zombies
		{
			objective[3] = true;
		}
	}
}
void GameObjective::checkObjective4()
{
	if (obj_zones <= 0)
	{
		objective[4] = true;
	}
}

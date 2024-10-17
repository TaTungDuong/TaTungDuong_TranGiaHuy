#include "Include/GameObjective.h"
/*
GameObjective::GameObjective()
{
	currentObjective = -1; 
	obj_zombieKilled = 0;
	totalZombieKilled = 0;
	for (int i = 0; i < 4; i++)
	{
		obj_keyPressed[i] = false;
	}
	tutorial = true;
}
*/
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
void GameObjective::checkObjective4(
	std	::vector<gameObject>& signalZones, 
	LTexture& gLightTexture, 
	player& myPlayer
)
{
	if (currentObjective == 4)
	{

		int i = 0;
		while (i < signalZones.size())
		{
			if (signalZones[i].checkCollision(myPlayer))
			{
				signalZones.erase(signalZones.begin() + i);
				Sound::GetInstance()->playCollectObject();
				obj_zones--;
			}
			else
			{
				int size1 = signalZones[i].size * 10;
				int size2 = signalZones[i].size * 5;
				int size3 = signalZones[i].size * 3;
				gLightTexture.setColor(0, 0, 255, 25);
				gLightTexture.render(camera, signalZones[i].px - size1 / 2, signalZones[i].py - size1 / 2, size1, size1);
				gLightTexture.setColor(0, 0, 255, 50);
				gLightTexture.render(camera, signalZones[i].px - size2 / 2, signalZones[i].py - size2 / 2, size2, size2);
				gLightTexture.setColor(0, 0, 255, 100);
				gLightTexture.render(camera, signalZones[i].px - size3 / 2, signalZones[i].py - size3 / 2, size3, size3);
				gLightTexture.setColor(0, 0, 255, 200);
				gLightTexture.render(camera, signalZones[i].rx, signalZones[i].ry, signalZones[i].size, signalZones[i].size);
			}
			i++;
		}
	}
	//renderGameObject(camera, gLightTexture, signalZones);

	if (obj_zones <= 0)
	{
		objective[4] = true;
	}
}

#include "Include/GameEnvironment.h"

bool GameEnvironment::loadMedia(SpriteSheet& m_SpriteSheet)
{
	//Loading success flag
	bool success = true;

#pragma region Load_static_textures
	//Load static texture
	if (!gGroundTexture.loadFromFile("assets-main/sprites/tilemap/ground.png"))
	{
		printf("Failed to load player texture!\n");
		success = false;
	}
	
	if (!gTreeTexture.loadFromFile("assets-main/sprites/objects/environment/trees/trees.png"))
	{
		printf("Failed to load tree texture!\n");
		success = false;
	}
	else
	{
		m_SpriteSheet.loadClips(gTreeTexture, gTreeClips, TREES_CLIP);
	}
	

//	if (!gBulletTexture.loadFromFile("assets-main/sprites/objects/bullets/player_bullets/bullet-16.png"))
	if (!gBulletTexture.loadFromFile("assets-main/sprites/objects/bullets/player_bullets/bullet.png"))
	{
		printf("Failed to load bullet texture!\n");
		success = false;
	}

	if (!gBloodPoolTexture.loadFromFile("assets-main/sprites/effects/blood_pool.png"))
	{
		printf("Failed to load white texture!\n");
		success = false;
	}

	if (!gHealthPickUpTexture.loadFromFile("assets-main/sprites/objects/items/milk_128.png"))
	{
		printf("Failed to load health pickup texture!\n");
		success = false;
	}
#pragma endregion

	return success;
}

//render and update environment
void GameEnvironment::renderBloodPool(SDL_Rect& camera)
{
	int i = 0;

	//delete old blood pool
	if (bloodpools.size() > MAX_BLOOD_POOL_NUM)
	{
		bloodpools.erase(bloodpools.begin());
	}

	//render blood pool
	while (i < bloodpools.size())
	{
		gBloodPoolTexture.render(camera, bloodpools[i].px, bloodpools[i].py, 
			bloodpools[i].size, bloodpools[i].size, NULL, bloodpools[i].rotation);
		i++;
	}
}
void GameEnvironment::renderGround(SDL_Rect& camera)
{
	for (int y = 0; y < LEVEL_SIZE; y++)
	{
		for (int x = 0; x < LEVEL_SIZE; x++)
		{
			gGroundTexture.render(camera, x * GROUND_TILE_SIZE, y * GROUND_TILE_SIZE, GROUND_TILE_SIZE, GROUND_TILE_SIZE);
		}
	}
}
void GameEnvironment::spawnZombie()
{
	if (canSpawnZombie)
	{
		int zombieAliveCnt = 0;
		for (auto z : zombies)
		{
			if (z.health > 0) zombieAliveCnt++;
		}
		while (zombies.size() - zombieAliveCnt > MAX_DEAD_ZOMBIE_NUM)
		{
			zombies.erase(zombies.begin());
			zombieWeapons.erase(zombieWeapons.begin());
		}
//		while (zombies.size() < MAX_ZOMBIE_NUM)
		while (zombieAliveCnt < MAX_ZOMBIE_NUM)
		{
			myZombie.init();
			zombies.push_back(myZombie);
			myZombieWeapon.init(myZombie);
			zombieWeapons.push_back(myZombieWeapon);
			zombieAliveCnt++;
		}
		printf("--- spawned zombies. total zombie = %i ---\n", zombies.size());
		canSpawnZombie = false;
	}
}
void GameEnvironment::updateZombie(SpriteSheet& m_SpriteSheet, player& myPlayer, SDL_Rect& camera)
{
	spawnZombie();
	int i = 0;

	while (i < zombies.size())
	{
		//attack player if close
		if (zombies[i].calDistance(myPlayer) <= zombies[i].attackRange + myPlayer.size)
		{
			if (zombies[i].attack(myPlayer))
			{
//				printf("HIT BY ZOMBIES\n");
				Sound::GetInstance()->playZombieAttack();
				Sound::GetInstance()->playPlayerHurt();
			}
		}
		//move
		zombies[i].move(myPlayer);
		zombieWeapons[i].move(zombies[i], myPlayer);
		//render zombie
		m_SpriteSheet.setZombieAnimation(zombies[i]);
		m_SpriteSheet.setZombieWeaponAnimation(zombieWeapons[i]);
		zombies[i].render(camera);
		zombieWeapons[i].render(camera, (zombies[i].health > 0));
		i++;
	}//
}
void GameEnvironment::updateBullet(
	player& myPlayer, GameObjective& m_GameObjective
)
{
	int i = 0;
	gBulletTexture.setColor(255, 200, 0);
	while (i < bullets.size())
	{
		bullets[i].px += bullets[i].vx;
		bullets[i].py += bullets[i].vy;

		//delete bullet if its out of view
		if (bullets[i].calDistance(myPlayer) > SCREEN_WIDTH)
		{
			bullets.erase(bullets.begin() + i);
		}
		else
		{
			bool collised = false;
			//check bullet collision
			//tree
			for (int j = 0; j < trees.size(); j++)
			{
				if (bullets[i].checkCollision(trees[j]))
				{
					collised = true;
					Sound::GetInstance()->playHitTree();
					break;
				}
			}
			//zombie
			for (int j = 0; j < zombies.size(); j++)
			{
				if (bullets[i].checkCollision(zombies[j]))
				{
					collised = (zombies[j].health > 0);
					zombies[j].hurt();
					Sound::GetInstance()->playHitZombie();

					//remove zombie if it's health is below 0
					if (zombies[j].health <= 0 && collised)
					{
						zombies[j].currentState = zombieState::DEAD;
						bloodpools.push_back(zombies[j]);
					//	zombies.erase(zombies.begin() + j);
					//	zombieWeapons.erase(zombieWeapons.begin() + j);
						canSpawnZombie = true;
						m_GameObjective.totalZombieKilled++;

						//for objective 4
						m_GameObjective.checkObjective3();
					}
					break;
				}
			}
			//delete current bullet if it's collided with something
			if (collised)
			{
				bullets.erase(bullets.begin() + i);
			}
			else
			{
				//update bullet position
				bullets[i].updateRenderPosition();
				//render bullet
				gBulletTexture.render(camera, bullets[i].rx, bullets[i].ry, bullets[i].size, bullets[i].size, 
					NULL, bullets[i].rotation);
				i++;
			}
		}
	}
}

void GameEnvironment::init()
{
	//clear level objects
	trees.clear();
	harmZones.clear();
	zombies.clear();
	zombieWeapons.clear();
	bloodpools.clear();
	bullets.clear();
	signalZones.clear();
	healthPickUps.clear();
}
void GameEnvironment::close()
{
	//Free static textures
	gGroundTexture.free();
	gTreeTexture.free();
	gBulletTexture.free();
	gBloodPoolTexture.free();
	gHealthPickUpTexture.free();
	//clear vectors
	trees.clear();
	harmZones.clear();
	zombies.clear();
	zombieWeapons.clear();
	bloodpools.clear();
	bullets.clear();
	signalZones.clear();
	healthPickUps.clear();
}
#pragma region create Objects
void createGameObjectRandom(
	gameObject sourceObject,
	std::vector<gameObject>& vectorList,
	int total, int minSize, int maxSize, int rotation,
	int maxType
)
{
	for (int i = 0; i < total; i++)
	{
		bool ok = false;
		int randomSize = 0;
		int randomX = 0;
		int randomY = 0;

		while (!ok)
		{
			randomSize = GetRandomInt(minSize, maxSize, 1);
			randomX = GetRandomInt(randomSize, LEVEL_WIDTH - randomSize, 1);
			randomY = GetRandomInt(randomSize, LEVEL_HEIGHT - randomSize, 1);
			if (calDistance(randomX, randomY, myPlayer.px, myPlayer.py) > randomSize + myPlayer.size)
			{
				ok = true;
			}
		}

		int randomRotation = 0;
		if (maxType != -1)
		{
			randomRotation = GetRandomInt(0, rotation, 1);
		}
		sourceObject.init(randomX, randomY, randomSize, randomRotation);
		if (maxType != -1)
		{
			sourceObject.type = GetRandomInt(0, maxType - 2, 1);
		}
		vectorList.push_back(sourceObject);
	}
}
#pragma endregion
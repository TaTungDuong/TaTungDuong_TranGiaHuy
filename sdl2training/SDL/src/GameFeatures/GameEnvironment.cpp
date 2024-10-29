#include "Include/GameEnvironment.h"

bool GameEnvironment::loadMedia(SpriteSheet& m_SpriteSheet)
{
	//Loading success flag
	bool success = true;

#pragma region Load_static_textures
	//Load static texture
	///Ground
	if (!gGroundTexture.loadFromFile("assets-main/sprites/tilemap/ground.png"))
	{
		printf("Failed to load player texture!\n");
		success = false;
	}
	
	///Trees
	if (!gTreeTexture.loadFromFile("assets-main/sprites/objects/environment/trees/trees_red.png"))
	{
		printf("Failed to load tree texture!\n");
		success = false;
	}
	else
	{
		m_SpriteSheet.loadClips(gTreeTexture, gTreeClips, TREES_CLIP);
	}
	
	///PLayer Bullet
	if (!gBulletTexture.loadFromFile("assets-main/sprites/objects/bullets/player_bullets/bullet.png"))
	{
		printf("Failed to load bullet texture!\n");
		success = false;
	}
	
	success = loadZombieBulletMedia(m_SpriteSheet);

	///Blood Pool
	if (!gBloodPoolTexture.loadFromFile("assets-main/sprites/effects/blood_pool.png"))
	{
		printf("Failed to load white texture!\n");
		success = false;
	}

	///Milk
	if (!gHealthPickUpTexture.loadFromFile("assets-main/sprites/objects/items/milk_128.png"))
	{
		printf("Failed to load health pickup texture!\n");
		success = false;
	}
#pragma endregion

	return success;
}

bool GameEnvironment::loadZombieBulletMedia(SpriteSheet& m_SpriteSheet)
{
	bool success = true;

	///Zombie Bullets
	int cnt;
	cnt = 0;
	if (!gZombieBulletTextures[cnt].loadFromFile("assets-main/sprites/objects/bullets/npc_bullets/ball_128.png"))
	{
		printf("Failed to load bullet texture!\n");
		success = false;
	}
	cnt = 1;
	if (!gZombieBulletTextures[cnt].loadFromFile("assets-main/sprites/objects/bullets/npc_bullets/homing_128.png"))
	{
		printf("Failed to load bullet texture!\n");
		success = false;
	}
	cnt = 2;
	if (!gZombieBulletTextures[cnt].loadFromFile("assets-main/sprites/objects/bullets/npc_bullets/square_128.png"))
	{
		printf("Failed to load bullet texture!\n");
		success = false;
	}
	cnt = 3;
	if (!gZombieBulletTextures[cnt].loadFromFile("assets-main/sprites/objects/bullets/npc_bullets/square_128.png"))
	{
		printf("Failed to load bullet texture!\n");
		success = false;
	}
	cnt = 4;
	if (!gZombieBulletTextures[cnt].loadFromFile("assets-main/sprites/objects/bullets/npc_bullets/ball_128.png"))
	{
		printf("Failed to load bullet texture!\n");
		success = false;
	}
	return success;
}

//render and update environment
void GameEnvironment::renderBloodPool(SpriteSheet& m_SpriteSheet, SDL_Rect& camera)
{
	//delete old blood pool
	if (bloodpools.size() > MAX_BLOOD_POOL_NUM)
	{
		bloodpools.erase(bloodpools.begin());
	}

	//render blood pool
	for (auto& bp : bloodpools)
	{
		gBloodPoolTexture.render(camera, bp.px, bp.py, 
			bp.size, bp.size, NULL, bp.rotation);
	}

	//render enemy bodies
	for (auto zb : zombies)
	{
		if (zb.health <= 0)
		{
			zb.currentState = zombieState::DEAD;
			m_SpriteSheet.setZombieAnimation(zb);
			zb.render(camera);
		}
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

void GameEnvironment::spawnSignal(GameObjective& m_GameObjective)
{
	if (signals.size() >= signalZones.size() || m_GameObjective.currentObjective != 4) return;
	for (auto sZ : signalZones)
	{
		signal mySignal;
		mySignal.initSignal(sZ);
		signals.push_back(mySignal);
	}
}
bool GameEnvironment::checkSignal()
{
	//check if there is alive signal
	bool hasSignal = false;
	for (auto s : signals)
	{
		if (s.currentState != signalState::DEAD || s.currentFrame < SIGNAL_DEAD_ANIMATION_FRAMES - 1)
		{
			hasSignal = true;
			break;
		}
	}
	return hasSignal;
}

void GameEnvironment::spawnZombie(GameObjective& m_GameObjective)
{
	//check if there is alive signal
	//if false, the zombie can not be spawned anymore
	if (canSpawnZombie && (checkSignal() || m_GameObjective.currentObjective < 4))
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
			zombieEffects.erase(zombieEffects.begin());
		}
//		while (zombies.size() < MAX_ZOMBIE_NUM)
		while (zombieAliveCnt < MAX_ZOMBIE_NUM)
		{
			myZombie.init();
			zombies.push_back(myZombie);
			myZombieWeapon.init(myZombie);
			zombieWeapons.push_back(myZombieWeapon);
			myZombieEffect.init(myZombie);
			zombieEffects.push_back(myZombieEffect);
			zombieAliveCnt++;
		}
		printf("--- spawned zombies. total zombie = %i ---\n", zombies.size());
		canSpawnZombie = false;
	}
}
void GameEnvironment::updateZombie(
	SpriteSheet& m_SpriteSheet, 
	player& myPlayer, 
	playerSkill& myPlayerSkill,
	GameObjective& m_GameObjective,
	SDL_Rect& camera
)
{
	spawnZombie(m_GameObjective);
	for (int i = 0; i < zombies.size(); i++)
	{
		if (zombies[i].health <= 0) continue;

		if (zombieWeapons[i].attack(myPlayer, zombies[i], zombieBullets, (zombies[i].health > 0)))
		{
//			Sound::GetInstance()->playZombieShoot();
		}
		
		//check collision with player skills
		/// Emperor Divide
		for (auto soldier : myPlayerSkill.myEmperorDivide)
		{
			if (zombies[i].checkCollision(soldier) && soldier.isActive && zombies[i].health > 0)
			{
				zombies[i].health -= soldier.damage;
				Sound::GetInstance()->playHitZombie();

				break;
			}
		}
		/// Call Of The Forge God
		if (zombies[i].checkCollision(myPlayerSkill.myCat) && zombies[i].health > 0)
		{
			zombies[i].health -= myPlayerSkill.myCat.damage;
			zombies[i].isActive = 0;
		}
		if (myPlayer.isActive == 1) zombies[i].isActive = 1;

		//remove zombie if it's health is below 0
		if (zombies[i].currentState != zombieState::DEAD)
		{
			if (zombies[i].health <= 0)
			{
				zombies[i].currentState = zombieState::DEAD;
				zombies[i].currentFrame = 0;
				bloodpools.push_back(zombies[i]);
				canSpawnZombie = true;
				m_GameObjective.totalZombieKilled++;
				Sound::GetInstance()->playZombieDie();

				//for objective 4
				m_GameObjective.checkObjective3();
			}
		}

		//move
		zombies[i].move(myPlayer);
		zombieWeapons[i].move(zombies[i], myPlayer);
		zombieEffects[i].move(zombies[i], myPlayer);
		//render zombie
		m_SpriteSheet.setZombieAnimation(zombies[i]);
		m_SpriteSheet.setZombieWeaponAnimation(zombieWeapons[i]);

		if (zombies[i].isActive == 0)
		{
			zombieEffects[i].currentState = zombieEffectState::STUNT;
			zombieEffects[i].gZombieEffectTimeCounter[zombieEffects[i].currentState] = 0.0f;
		}
		else
		{
			zombieEffects[i].currentState = zombieEffectState::IDLE;
		}
		m_SpriteSheet.setZombieEffectAnimation(zombieEffects[i]);

		zombies[i].render(camera);
		zombieWeapons[i].render(camera, (zombies[i].health > 0));
		zombieEffects[i].render(camera);
	}//
}

void GameEnvironment::spawnBoss(player& myPlayer, GameObjective& m_GameObjective)
{
	//check if there is alive signal and there is boss
	//if false, the boss can be spawned
	if (!checkSignal() && wardens.size() == 0 && m_GameObjective.currentObjective >= 4)
	{
		Sound::GetInstance()->playBossMusic();

		myWarden.initWarden(myPlayer);
		wardens.push_back(myWarden);
		printf("--- Boss: Warden---\n");

		//Set up Turrets
		for (int i = 0; i < myWarden.number_of_turrets; i++)
		{
			turret myTurret;
			myTurret.initTurret(myPlayer);
			turrets.push_back(myTurret);
		}

		//Set up Clones
		for (int i = 0; i < myWarden.number_of_clones; i++)
		{
			wardenClone myWardenClone;
			if (i)
			{
				myWardenClone.initWardenClone(myPlayer, wardenCloneState::FAKE);
			}
			else
			{
				myWardenClone.initWardenClone(myPlayer, wardenCloneState::REAL);
			}
			wardenClones.push_back(myWardenClone);
		}
	}
}
void GameEnvironment::updateBoss(
	SpriteSheet& m_SpriteSheet,
	player& myPlayer,
	playerSkill& myPlayerSkill,
	GameObjective& m_GameObjective,
	SDL_Rect& camera
)
{
	spawnBoss(myPlayer, m_GameObjective);
	if (wardens.size() == 0) return;
	if (myWarden.attack(myPlayer, wardenClones, turrets, zombieBullets))
	{

	}
	//check collision with player skills
	/// Emperor Divide
	for (auto soldier : myPlayerSkill.myEmperorDivide)
	{
		if (myWarden.checkCollision(soldier) && soldier.isActive)
		{
			myWarden.hurt(soldier.damage);
			Sound::GetInstance()->playHitZombie();

			break;
		}
	}
	/// Call Of The Forge God
	if (myWarden.checkCollision(myPlayerSkill.myCat))
	{
		myWarden.hurt(myPlayerSkill.myCat.damage);
	}

	///Change to DEAD if Warden health <= 0
	if (myWarden.health <= 0)
	{
		myWarden.currentState = WardenState::DEAD;
	}

	myWarden.move(myPlayer);
	m_SpriteSheet.setWardenAnimation(myWarden);
	myWarden.render(camera);

	for (int i = 0; i < wardenClones.size(); i++)
	{
		wardenClones[i].move(myPlayer);
		wardenClones[i].updateRenderPosition();
	}
}

void GameEnvironment::updateBullet(
	player& myPlayer, 
	GameObjective& m_GameObjective
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
					if (collised)
					{
						Sound::GetInstance()->playHitZombie();
					}
					zombies[j].hurt();

					//remove zombie if it's health is below 0
					if (zombies[j].health <= 0 && collised)
					{
						zombies[j].currentState = zombieState::DEAD;
						zombies[j].currentFrame = 0;
						bloodpools.push_back(zombies[j]);
						canSpawnZombie = true;
						m_GameObjective.totalZombieKilled++;
						Sound::GetInstance()->playZombieDie();
						//for objective 4
						m_GameObjective.checkObjective3();
					}

					if (collised) break;
				}
			}
			//signal
			for (int j = 0; j < signals.size(); j++)
			{
				if (bullets[i].checkCollision(signals[j]))
				{
					collised = (signals[j].health > 0);
					signals[j].hurt(myPlayer);

					//remove signal if it's health is below 0
					if (signals[j].health <= 0 && collised)
					{
						Sound::GetInstance()->playExplosion();
						m_GameObjective.obj_zones--;
					}
					if (collised) break;
				}
			}

			//boss
			//warden and clones
			if (bullets[i].checkCollision(myWarden) && myWarden.canCollide() == true)
			{
				collised = (myWarden.health > 0);
				myWarden.hurt(myPlayer.myWeapon[myPlayer.currentWeapon].getDamage());
				//printf("HIT WARDEN: %f\n", myWarden.health);

				//remove if Warden health is below 0
				if (myWarden.health <= 0 && collised)
				{
					myWarden.currentState = WardenState::DEAD;
				}
			}
			for (auto& wc : wardenClones)
			{
				if (bullets[i].checkCollision(wc))
				{
					collised = true;
					wc.hurt(myPlayer);
					Sound::GetInstance()->playGlassBreak();
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

void GameEnvironment::updateZombieBullet(
	player& myPlayer,
	playerSkill& myPlayerSkill,
	playerEffect& myPlayerEffect,
	GameObjective& m_GameObjective
)
{
	//check if there is alive signal and the bullet belongs to common enemies
	//if false, the bulltets of common enemies will be inactive
	int i = 0;
	while (i < zombieBullets.size())
	{
		gZombieBulletTextures[zombieBullets[i].type].setColor(255, 200, 0);
		zombieBullets[i].updateBullet();

		//delete bullet if its out of view or out of lifetime or is inactive
		if ((m_GameObjective.currentObjective >= 4 && !checkSignal() && zombieBullets[i].type < 3)
			|| zombieBullets[i].calDistance(myPlayer) > SCREEN_WIDTH
			|| zombieBullets[i].lifeTime >= zombieBullets[i].max_lifeTime)
		{
			zombieBullets.erase(zombieBullets.begin() + i);
		}
		else
		{
			bool collised = false;
			//check bullet collision
			//tree
			for (int j = 0; j < trees.size(); j++)
			{
				if (zombieBullets[i].checkCollision(trees[j]))
				{
					//collised = true;
					break;
				}
			}
			
			//player
			if (zombieBullets[i].checkCollision(myPlayer))
			{
				collised = true;
				myPlayer.health -= zombieBullets[i].damage * myPlayer.isActive;
				myPlayerEffect.currentState = playerEffectState::HURT;
				myPlayerEffect.gPlayerEffectTimeCounter[myPlayerEffect.currentState] = 0.0f;
				Sound::GetInstance()->playPlayerHurt();
			}

			//player skills
			//Dominus
			if (zombieBullets[i].checkCollision(myPlayerSkill.myDominus))
			{
				collised = true;
			}

			//delete current bullet if it's collided with something
			if (collised)
			{
				zombieBullets.erase(zombieBullets.begin() + i);
			}
			else
			{
				//update bullet position
				zombieBullets[i].updateRenderPosition();
				//render bullet
				gZombieBulletTextures[zombieBullets[i].type].render(camera, zombieBullets[i].rx, zombieBullets[i].ry,
					zombieBullets[i].size, zombieBullets[i].size,
					NULL, zombieBullets[i].rotation);
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
	zombieEffects.clear();
	zombieBullets.clear();
	wardens.clear();
	wardenClones.clear();
	turrets.clear();
	bloodpools.clear();
	bullets.clear();
	signals.clear();
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
	zombieEffects.clear();
	zombieBullets.clear();
	wardens.clear();
	wardenClones.clear();
	turrets.clear();
	bloodpools.clear();
	bullets.clear();
	signals.clear();
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
		if (vectorList.size() >= total) break; // if vector is full of sourceObject, break
		bool ok = false;
		int randomSize = 0;
		int randomX = 0;
		int randomY = 0;

		while (!ok)
		{
			randomSize = GetRandomInt(minSize, maxSize, 1);
			randomX = GetRandomInt(std::min(randomSize, LEVEL_WIDTH - randomSize), std::max(randomSize, LEVEL_WIDTH - randomSize), 1);
			randomY = GetRandomInt(std::min(randomSize, LEVEL_WIDTH - randomSize), std::max(randomSize, LEVEL_WIDTH - randomSize), 1);
			if (calDistance(randomX, randomY, myPlayer.px, myPlayer.py) >= std::max(randomSize - myPlayer.size, 0))
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



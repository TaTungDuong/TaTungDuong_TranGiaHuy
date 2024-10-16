#include "Include/SpriteSheet.h"

SpriteSheet::SpriteSheet()
{
	animationTimeCounter = 0.0;
}

//Load Sprite Sheet
void SpriteSheet::loadSpritesheet(
	enum playerAnimationState state, 
	std::map<playerAnimationState, LTexture>& spritesheet,
	std::map<playerAnimationState, 
	std::vector <SDL_Rect>>& spritesheetClip, 
	int totalFrame
)
{
	int w = spritesheet[state].getWidth() / totalFrame;
	int h = spritesheet[state].getHeight();
	for (int i = 0; i < totalFrame; i++)
	{
		spritesheetClip[state].push_back({ i * w, 0, w , h });
	}
}
void SpriteSheet::loadSpritesheet(
	enum playerEffectState state,
	std::map<playerEffectState, LTexture>& spritesheet,
	std::map<playerEffectState,
	std::vector <SDL_Rect>>&spritesheetClip,
	int totalFrame
)
{
	int w = spritesheet[state].getWidth() / totalFrame;
	int h = spritesheet[state].getHeight();
	for (int i = 0; i < totalFrame; i++)
	{
		spritesheetClip[state].push_back({ i * w, 0, w , h });
	}
}
void SpriteSheet::loadSpritesheet(
	enum playerState state, 
	std::map<playerState, LTexture>& spritesheet,
	std::map<playerState, 
	std::vector <SDL_Rect>>& spritesheetClip, 
	int totalFrame
)
{
	int w = spritesheet[state].getWidth() / totalFrame;
	int h = spritesheet[state].getHeight();
	for (int i = 0; i < totalFrame; i++)
	{
		spritesheetClip[state].push_back({ i * w, 0, w , h });
	}
}
void SpriteSheet::loadSpritesheet(
	enum zombieState state, 
	std::map<zombieState, LTexture>& spritesheet,
	std::map<zombieState, std::vector <SDL_Rect>>& spritesheetClip, 
	int totalFrame
)
{
	int w = spritesheet[state].getWidth() / totalFrame;
	int h = spritesheet[state].getHeight();
	for (int i = 0; i < totalFrame; i++)
	{
		spritesheetClip[state].push_back({ i * w, 0, w , h });
	}
}
void SpriteSheet::loadSpritesheet(
	enum zombieWeaponState state,
	std::map<zombieWeaponState, LTexture>& spritesheet,
	std::map<zombieWeaponState, std::vector <SDL_Rect>>& spritesheetClip,
	int totalFrame
)
{
	int w = spritesheet[state].getWidth() / totalFrame;
	int h = spritesheet[state].getHeight();
	for (int i = 0; i < totalFrame; i++)
	{
		spritesheetClip[state].push_back({ i * w, 0, w , h });
	}
}
void SpriteSheet::loadSpritesheet(
	LTexture& spritesheet, 
	std::vector <SDL_Rect>& spritesheetClip, 
	int totalFrame
)
{
	int w = spritesheet.getWidth() / totalFrame;
	int h = spritesheet.getHeight();
	for (int i = 0; i < totalFrame; i++)
	{
		spritesheetClip.push_back({ i * w, 0, w , h });
	}
}
//Load Clips
void SpriteSheet::loadClips(
	LTexture& spritesheet, 
	std::vector<SDL_Rect>& spritesheetClip, 
	int totalClip
)
{
	int w = spritesheet.getWidth() / totalClip;
	int h = spritesheet.getHeight();
	for (int i = 0; i < totalClip; i++)
	{
		spritesheetClip.push_back({ i * w, 0, w , h });
	}
}

bool SpriteSheet::loadPlayerAnimationMedia()
{
	bool success = true;
	// player animations
	//idle
//	if (!gPlayerAnimationTexture[playerAnimationState::IDLE].loadFromFile("assets-main/sprites/characters/player/player_idle_256.png"))
	if (!gPlayerAnimationTexture[playerAnimationState::IDLE].loadFromFile("assets-main/sprites/characters/player/player_idle_128.png"))
	{
		printf("Failed to load player idle texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerAnimationState::IDLE, gPlayerAnimationTexture, gPlayerAnimationClips, PLAYER_ANIMATION_IDLE_ANIMATION_FRAMES);
	}
	//walk
//	if (!gPlayerAnimationTexture[playerAnimationState::WALK].loadFromFile("assets-main/sprites/characters/player/player_walk_256.png"))
	if (!gPlayerAnimationTexture[playerAnimationState::WALK].loadFromFile("assets-main/sprites/characters/player/player_walk_128.png"))
	{
		printf("Failed to load player walk texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerAnimationState::WALK, gPlayerAnimationTexture, gPlayerAnimationClips, PLAYER_ANIMATION_WALK_ANIMATION_FRAMES);
	}
	//fire
	if (!gPlayerAnimationTexture[playerAnimationState::FIRE].loadFromFile("assets-main/sprites/characters/player/player_die(2).png"))
	{
		printf("Failed to load player fire texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerAnimationState::FIRE, gPlayerAnimationTexture, gPlayerAnimationClips, PLAYER_ANIMATION_FIRE_ANIMATION_FRAMES);
	}
	//reload
	if (!gPlayerAnimationTexture[playerAnimationState::RELOAD].loadFromFile("assets-main/sprites/characters/player/player_reload_128.png"))
	{
		printf("Failed to load player reload texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerAnimationState::RELOAD, gPlayerAnimationTexture, gPlayerAnimationClips, PLAYER_ANIMATION_RELOAD_ANIMATION_FRAMES);
	}

	return success;
}
bool SpriteSheet::loadPlayerEffectMedia()
{
	bool success = true;
	// player effects
	//drink
	if (!gPlayerEffectTexture[playerEffectState::DRINK].loadFromFile("assets-main/sprites/objects/items/milk_128_drink.png"))
	{
		printf("Failed to load player drink effect texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerEffectState::DRINK, gPlayerEffectTexture, gPlayerEffectClips, 13);
	}

	return success;
}

bool SpriteSheet::loadPlayerMedia()
{
	bool success = true;
	//pistol
	//idle
//	if (!gPlayerPistolTexture[playerState::IDLE].loadFromFile("assets-main/sprites/[spritesheets]/player/pistol/pistol-idle.png"))
//	if (!gPlayerPistolTexture[playerState::IDLE].loadFromFile("assets-main/sprites/weapons/shotgun/256_shotgun_idle.png"))
	if (!gPlayerPistolTexture[playerState::IDLE].loadFromFile("assets-main/sprites/weapons/shotgun/shotgun_idle_128.png"))
	{
		printf("Failed to load player pistol idle texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::IDLE, gPlayerPistolTexture, gPlayerPistolClips, PLAYER_PISTOL_IDLE_ANIMATION_FRAMES);
	}
	//walk
//	if (!gPlayerPistolTexture[playerState::WALK].loadFromFile("assets-main/sprites/[spritesheets]/player/pistol/pistol-walk.png"))
//	if (!gPlayerPistolTexture[playerState::WALK].loadFromFile("assets-main/sprites/weapons/shotgun/256_shotgun_walk.png"))
	if (!gPlayerPistolTexture[playerState::WALK].loadFromFile("assets-main/sprites/weapons/shotgun/shotgun_walk_128.png"))
	{
		printf("Failed to load player pistol walk texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::WALK, gPlayerPistolTexture, gPlayerPistolClips, PLAYER_PISTOL_WALK_ANIMATION_FRAMES);
	}
	//fire
//	if (!gPlayerPistolTexture[playerState::WALK].loadFromFile("assets-main/sprites/[spritesheets]/player/pistol/pistol-fire.png"))
//	if (!gPlayerPistolTexture[playerState::FIRE].loadFromFile("assets-main/sprites/weapons/shotgun/256_shotgun_fire.png"))
	if (!gPlayerPistolTexture[playerState::FIRE].loadFromFile("assets-main/sprites/weapons/shotgun/shotgun_fire_128.png"))
	{
		printf("Failed to load player pistol fire texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::FIRE, gPlayerPistolTexture, gPlayerPistolClips, PLAYER_PISTOL_FIRE_ANIMATION_FRAMES);
	}
	//reload
//	if (!gPlayerPistolTexture[playerState::WALK].loadFromFile("assets-main/sprites/[spritesheets]/player/pistol/pistol-reload.png"))
//	if (!gPlayerPistolTexture[playerState::RELOAD].loadFromFile("assets-main/sprites/weapons/shotgun/256_shotgun_reload.png"))
	if (!gPlayerPistolTexture[playerState::RELOAD].loadFromFile("assets-main/sprites/weapons/shotgun/shotgun_reload_128.png"))
	{
		printf("Failed to load player pistol reload texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::RELOAD, gPlayerPistolTexture, gPlayerPistolClips, PLAYER_PISTOL_RELOAD_ANIMATION_FRAMES);
	}

	//rifle
	//idle
	if (!gPlayerRifleTexture[playerState::IDLE].loadFromFile("assets-main/sprites/weapons/heavy_cannon/heavy_cannon_full_auto_idle_128.png"))
	{
		printf("Failed to load player rifle idle texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::IDLE, gPlayerRifleTexture, gPlayerRifleClips, PLAYER_RIFLE_IDLE_ANIMATION_FRAMES);
	}
	//walk
	if (!gPlayerRifleTexture[playerState::WALK].loadFromFile("assets-main/sprites/weapons/heavy_cannon/heavy_cannon_full_auto_walk_128.png"))
	{
		printf("Failed to load player rifle walk texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::WALK, gPlayerRifleTexture, gPlayerRifleClips, PLAYER_RIFLE_WALK_ANIMATION_FRAMES);
	}
	//fire
	if (!gPlayerRifleTexture[playerState::FIRE].loadFromFile("assets-main/sprites/weapons/heavy_cannon/heavy_cannon_full_auto_fire_128.png"))
	{
		printf("Failed to load player rifle fire texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::FIRE, gPlayerRifleTexture, gPlayerRifleClips, PLAYER_RIFLE_FIRE_ANIMATION_FRAMES);
	}
	//reload
	if (!gPlayerRifleTexture[playerState::RELOAD].loadFromFile("assets-main/sprites/weapons/heavy_cannon/heavy_cannon_full_auto_reload_128.png"))
	{
		printf("Failed to load player rifle reload texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::RELOAD, gPlayerRifleTexture, gPlayerRifleClips, PLAYER_RIFLE_RELOAD_ANIMATION_FRAMES);
	}

	return success;
}

bool SpriteSheet::loadZombieMedia()
{
	bool success = true;
	int cnt;

	//Zombie
	// #0. Cyborg
	cnt = 0;
	//walk
	if (!gZombieTexture[cnt][zombieState::WALK].loadFromFile("assets-main/sprites/characters/enemies/cyborg/cyborg_walk_128.png"))
	{
		printf("Failed to load zombie walk texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieState::WALK, gZombieTexture[cnt], gZombieClips[cnt], ZOMBIE_WALK_ANIMATION_FRAMES);
	}
	//attack
	if (!gZombieTexture[cnt][zombieState::ATTACK].loadFromFile("assets-main/sprites/characters/enemies/cyborg/cyborg_attack_128.png")) //TODO: change to zombie attack
	{
		printf("Failed to load zombie attack texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieState::ATTACK, gZombieTexture[cnt], gZombieClips[cnt], ZOMBIE_ATTACK_ANIMATION_FRAMES);
	}

	// #1. Drone
	cnt = 1;
	//walk
	if (!gZombieTexture[cnt][zombieState::WALK].loadFromFile("assets-main/sprites/characters/enemies/drone/drone_walk_128.png"))
	{
		printf("Failed to load zombie walk texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieState::WALK, gZombieTexture[cnt], gZombieClips[cnt], ZOMBIE_WALK_ANIMATION_FRAMES);
	}
	//attack
	if (!gZombieTexture[cnt][zombieState::ATTACK].loadFromFile("assets-main/sprites/characters/enemies/drone/drone_attack_128.png")) //TODO: change to zombie attack
	{
		printf("Failed to load zombie attack texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieState::ATTACK, gZombieTexture[cnt], gZombieClips[cnt], ZOMBIE_ATTACK_ANIMATION_FRAMES);
	}

	// #2. Uwu
	cnt = 2;
	//walk
	if (!gZombieTexture[cnt][zombieState::WALK].loadFromFile("assets-main/sprites/characters/enemies/uwu/uwu_walk_128.png"))
	{
		printf("Failed to load zombie walk texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieState::WALK, gZombieTexture[cnt], gZombieClips[cnt], ZOMBIE_WALK_ANIMATION_FRAMES);
	}
	//attack
	if (!gZombieTexture[cnt][zombieState::ATTACK].loadFromFile("assets-main/sprites/characters/enemies/uwu/uwu_attack_128.png")) //TODO: change to zombie attack
	{
		printf("Failed to load zombie attack texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieState::ATTACK, gZombieTexture[cnt], gZombieClips[cnt], ZOMBIE_ATTACK_ANIMATION_FRAMES);
	}

	// #3. Uwu
	cnt = 3;
	//walk
	if (!gZombieTexture[cnt][zombieState::WALK].loadFromFile("assets-main/sprites/characters/enemies/creeper/creeper_walk_128.png"))
	{
		printf("Failed to load zombie walk texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieState::WALK, gZombieTexture[cnt], gZombieClips[cnt], ZOMBIE_WALK_ANIMATION_FRAMES);
	}
	//attack
	if (!gZombieTexture[cnt][zombieState::ATTACK].loadFromFile("assets-main/sprites/characters/enemies/creeper/creeper_attack_128.png")) //TODO: change to zombie attack
	{
		printf("Failed to load zombie attack texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieState::ATTACK, gZombieTexture[cnt], gZombieClips[cnt], ZOMBIE_ATTACK_ANIMATION_FRAMES);
	}

	//load dead animation
	for (int i = 0; i < gZombieTexture->size(); i++)
	{
		if (!gZombieTexture[i][zombieState::DEAD].loadFromFile("assets-main/sprites/characters/enemies/enemy_die_128.png"))
		{
			printf("Failed to load zombie dead texture!\n");
			success = false;
		}
		else
		{
			loadSpritesheet(zombieState::DEAD, gZombieTexture[i], gZombieClips[i], ZOMBIE_WALK_ANIMATION_FRAMES);
		}
	}

	return success;
}
bool SpriteSheet::loadZombieWeaponMedia()
{
	bool success = true;
	int cnt;

	//Zombie Weapon
	// #0. Pistol
	cnt = 0;
	if (!gZombieWeaponTexture[cnt][zombieWeaponState::ATTACK].loadFromFile("assets-main/sprites/weapons/pistol/pistol_128.png")) //TODO: change to zombie weapon
	{
		printf("Failed to load zombie weapon texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieWeaponState::ATTACK, gZombieWeaponTexture[cnt], gZombieWeaponClips[cnt], 1);
	}

	return success;
}

void SpriteSheet::setPlayerAnimation(player& myPlayer)
{
	if (myPlayer.myWeapon[myPlayer.currentWeapon].checkReload())
	{
		myPlayer.currentState = playerState::RELOAD;
	}
	else if (myPlayer.previousState == playerState::RELOAD)
	{
		myPlayer.currentState = playerState::IDLE;
	}
	if (myPlayer.currentState == playerState::FIRE && myPlayer.currentFrame >= myPlayer.currentTotalFrame - 1)
	{
		myPlayer.currentState = playerState::IDLE;
		myPlayer.currentFrame = 0;
	}

	switch (myPlayer.currentState)
	{
	case playerState::IDLE:
		if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "pistol")
		{
			myPlayer.currentTotalFrame = PLAYER_PISTOL_IDLE_ANIMATION_FRAMES;
		}
		else if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "assault rifle")
		{
			myPlayer.currentTotalFrame = PLAYER_RIFLE_IDLE_ANIMATION_FRAMES;
		}
		break;
	case playerState::WALK:
		if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "pistol")
		{
			myPlayer.currentTotalFrame = PLAYER_PISTOL_WALK_ANIMATION_FRAMES;
		}
		else if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "assault rifle")
		{
			myPlayer.currentTotalFrame = PLAYER_RIFLE_WALK_ANIMATION_FRAMES;
		}
		break;
	case playerState::FIRE:
		if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "pistol")
		{
			myPlayer.currentTotalFrame = PLAYER_PISTOL_FIRE_ANIMATION_FRAMES;
		}
		else if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "assault rifle")
		{
			myPlayer.currentTotalFrame = PLAYER_RIFLE_FIRE_ANIMATION_FRAMES;
		}
		break;
	case playerState::RELOAD:
		if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "pistol")
		{
			myPlayer.currentTotalFrame = PLAYER_PISTOL_RELOAD_ANIMATION_FRAMES;
		}
		else if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "assault rifle")
		{
			myPlayer.currentTotalFrame = PLAYER_RIFLE_RELOAD_ANIMATION_FRAMES;
		}
		break;
	case playerState::DEAD:

		break;
	}

	if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "pistol")
	{
		myPlayer.setAnimation(gPlayerPistolTexture[myPlayer.currentState],
			gPlayerPistolClips[myPlayer.currentState][myPlayer.currentFrame]);
	}
	else if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "assault rifle")
	{
		myPlayer.setAnimation(gPlayerRifleTexture[myPlayer.currentState],
			gPlayerRifleClips[myPlayer.currentState][myPlayer.currentFrame]);
	}
}
void SpriteSheet::setPlayerAnimationAnimation(playerAnimation& myPlayerAnimation)
{
	switch (myPlayerAnimation.currentState)
	{
	case playerAnimationState::IDLE:
		myPlayerAnimation.currentTotalFrame = PLAYER_ANIMATION_IDLE_ANIMATION_FRAMES;
		break;
	case playerAnimationState::WALK:
		myPlayerAnimation.currentTotalFrame = PLAYER_ANIMATION_WALK_ANIMATION_FRAMES;
		break;
	case playerAnimationState::FIRE:
		myPlayerAnimation.currentTotalFrame = PLAYER_ANIMATION_FIRE_ANIMATION_FRAMES;
		break;
	case playerAnimationState::RELOAD:
		myPlayerAnimation.currentTotalFrame = PLAYER_ANIMATION_RELOAD_ANIMATION_FRAMES;
		break;
	case playerAnimationState::DEAD:

		break;
	}
	myPlayerAnimation.setAnimation(gPlayerAnimationTexture[myPlayerAnimation.currentState],
		gPlayerAnimationClips[myPlayerAnimation.currentState][myPlayerAnimation.currentFrame]);
}
void SpriteSheet::setPlayerEffectAnimation(playerEffect& myPlayerEffect)
{
	myPlayerEffect.currentState = playerEffectState::DRINK;
	switch (myPlayerEffect.currentState)
	{
	case playerEffectState::DRINK:
		myPlayerEffect.currentTotalFrame = 13;
		break;
	case playerEffectState::IDLE:

		break;
	}
	myPlayerEffect.setAnimation(gPlayerEffectTexture[myPlayerEffect.currentState],
		gPlayerEffectClips[myPlayerEffect.currentState][myPlayerEffect.currentFrame]);
}
void SpriteSheet::setZombieAnimation(zombie& source)
{
	if (source.currentTotalFrame == ZOMBIE_ATTACK_ANIMATION_FRAMES && source.currentFrame < ZOMBIE_ATTACK_ANIMATION_FRAMES)
	{
		source.currentState = zombieState::ATTACK;
	}

	if (source.health <= 0)
	{
		source.currentState = zombieState::DEAD;
	}

	switch (source.currentState)
	{
	case zombieState::WALK:
		if (source.currentFrame > ZOMBIE_WALK_ANIMATION_FRAMES - 1)
		{
			source.currentFrame = 0;
		}
		source.currentTotalFrame = ZOMBIE_WALK_ANIMATION_FRAMES;
		break;
	case zombieState::ATTACK:
		if (source.currentFrame > ZOMBIE_ATTACK_ANIMATION_FRAMES - 1)
		{
			source.currentFrame = 0;
		}
		source.currentTotalFrame = ZOMBIE_ATTACK_ANIMATION_FRAMES;
		break;
	case zombieState::DEAD:
		if (source.currentFrame > ZOMBIE_WALK_ANIMATION_FRAMES - 1)
		{
			source.currentFrame = ZOMBIE_WALK_ANIMATION_FRAMES - 1;
		}
		source.currentTotalFrame = ZOMBIE_WALK_ANIMATION_FRAMES;
		break;
	}

	source.setAnimation(gZombieTexture[source.type][source.currentState], 
		gZombieClips[source.type][source.currentState][source.currentFrame]);
}
void SpriteSheet::setZombieWeaponAnimation(zombieWeapon& source)
{
	source.currentState = zombieWeaponState::ATTACK;

	switch (source.currentState)
	{
	case zombieWeaponState::ATTACK:
		if (source.currentFrame > 1 - 1)
		{
			source.currentFrame = 0;
		}
		source.currentFrame = 0;
		source.currentTotalFrame = 1;
		break;
	}

	source.type = 0;
	source.currentState = zombieWeaponState::ATTACK;
	source.currentFrame = 0;

	source.setAnimation(gZombieWeaponTexture[source.type][source.currentState], 
		gZombieWeaponClips[source.type][source.currentState][source.currentFrame]);
}

void SpriteSheet::updateAnimation(
	player& myPlayer,
	playerAnimation& myPlayerAnimation,
	playerEffect& myPlayerEffect,
	std::vector<zombie>& zombies,
	LTimer deltaTimer
)
{
	animationTimeCounter += deltaTimer.getDeltaTime();

	if (animationTimeCounter > ANIMATION_INTERVAL)
	{
		animationTimeCounter = 0;
		myPlayer.currentFrame++;
		myPlayerAnimation.currentFrame++;
		myPlayerEffect.currentFrame++;

		for (int i = 0; i < zombies.size(); i++)
		{
			if (zombies[i].currentState != zombieState::DEAD)
			{
				zombies[i].currentFrame++;
				continue;
			}

			if (zombies[i].currentFrame <= ZOMBIE_WALK_ANIMATION_FRAMES - 1)
			{
				zombies[i].currentFrame++;
			}
		}
	}

	//Cycle player animation
	if (myPlayer.currentFrame > myPlayer.currentTotalFrame - 1)
	{
		myPlayer.currentFrame = 0;
	}
	if (myPlayerAnimation.currentFrame > myPlayerAnimation.currentTotalFrame - 1)
	{
		myPlayerAnimation.currentFrame = 0;
	}
	if (myPlayerEffect.currentFrame > myPlayerEffect.currentTotalFrame - 1)
	{
		myPlayerEffect.currentFrame = 0;
	}
}

void SpriteSheet::updatePlayer(
	player& myPlayer,
	playerAnimation& myPlayerAnimation,
	playerEffect& myPlayerEffect,
	int mouseX,
	int mouseY,
	std::vector<gameObject>& trees,
	std::vector<gameObject>& harmZones,
	std::vector<gameObject>& bloodpools,
	std::vector<zombie>& zombies,
	std::vector<bullet>& bullets,
	std::vector<gameObject>& signalZones,
	std::vector<gameObject>& healthPickUps,
	LTimer deltaTimer,
	audioManager& myAudio
)
{
	//set player's animation based on current state
	setPlayerAnimation(myPlayer);
	setPlayerAnimationAnimation(myPlayerAnimation);
	setPlayerEffectAnimation(myPlayerEffect);

	//calulate player rotation
	myPlayer.calRotation(camera, mouseX, mouseY);
	myPlayerAnimation.calRotation(camera, mouseX, mouseY);
	myPlayerEffect.calRotation(camera, mouseX, mouseY);

	myPlayer.speed = PLAYER_SPEED;
	//slow down player if player walk into trees
	for (int i = 0; i < trees.size(); i++)
	{
		if (myPlayer.checkCollision(trees[i]))
		{
			myPlayer.speed *= 0.75;
			myPlayer.speed *= 0.75;
			break;
		}
	}
	myPlayerAnimation.speed = myPlayer.speed;
	myPlayerEffect.speed = myPlayer.speed;

	//calulate player position
	float dirX = myPlayer.vx * myPlayer.speed * deltaTimer.getDeltaTime();
	float dirY = myPlayer.vy * myPlayer.speed * deltaTimer.getDeltaTime();
	myPlayer.px += dirX;
	myPlayer.py += dirY;
	myPlayerAnimation.px = myPlayer.px;
	myPlayerAnimation.py = myPlayer.py;
	myPlayerEffect.px = myPlayer.px;
	myPlayerEffect.py = myPlayer.py;

	//check collision with game objects
	//zombies
	for (int i = 0; i < zombies.size(); i++)
	{
		if (zombies[i].currentState != zombieState::DEAD
			&& myPlayer.checkCollision(zombies[i], zombies[i].attackRange))
		{
			myPlayer.px -= dirX;
			myPlayer.py -= dirY;
			break;
		}
	}

	//health pickups
	for (int i = 0; i < healthPickUps.size(); i++)
	{
		if (myPlayer.checkCollision(healthPickUps[i], HEALTH_PICKUP_SIZE / 2))
		{
			if (myPlayer.health < 100)
			{
				if (myPlayer.health + HEALTH_PICKUP_HEAL > 100)
				{
					myPlayer.health = 100;
				}
				else
				{
					myPlayer.health += HEALTH_PICKUP_HEAL;
				}
				myPlayerEffect.gPlayerEffectTimeCounter[myPlayerEffect.currentState] = 0.0f;
				healthPickUps.erase(healthPickUps.begin() + i);
				myAudio.playDrinkMilk();
			}
			break;
		}
	}

	//set player's render position
	myPlayer.updateRenderPosition();
	myPlayerAnimation.updateRenderPosition();
	myPlayerEffect.updateRenderPosition();

	//check if player is in harm zone
	for (int i = 0; i < harmZones.size(); i++)
	{
		float distance = myPlayer.calDistance(harmZones[i]);
		if (distance < harmZones[i].size / COLLIDER_TOLERANCE)
		{
			myPlayer.health -= ((MAX_HARM_ZONE_DAMAGE * DIFFICULTY) 
				- map(distance, 0, harmZones[i].size / COLLIDER_TOLERANCE, 
					0, (MAX_HARM_ZONE_DAMAGE * DIFFICULTY))) * deltaTimer.getDeltaTime();
			myAudio.playPlayerHurt(myPlayer);
			break;
		}
	}

	//render player++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	myPlayerAnimation.render(camera);
	myPlayer.render(camera);
	myPlayerEffect.render(camera);
}
#include "Include/SpriteSheet.h"

SpriteSheet::SpriteSheet()
{
	animationTimeCounter = 0.0;
}

//Load Sprite Sheet
//load Sprite Sheet for Player
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
	enum playerSkillState state,
	std::map<playerSkillState, LTexture>& spritesheet,
	std::map<playerSkillState,
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
//load Sprite Sheet for Enemy
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
	enum zombieEffectState state,
	std::map<zombieEffectState, LTexture>& spritesheet,
	std::map<zombieEffectState, std::vector <SDL_Rect>>& spritesheetClip,
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

//load Sprite Sheet for Signal
void SpriteSheet::loadSpritesheet(
	enum signalState state,
	std::map<signalState, LTexture>& spritesheet,
	std::map<signalState, std::vector <SDL_Rect>>& spritesheetClip,
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

#pragma region Load Player Stuff
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
	//idle
	if (!gPlayerEffectTexture[playerEffectState::IDLE].loadFromFile("assets-main/sprites/objects/items/milk_128_drink.png"))
	{
		printf("Failed to load player idle effect texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerEffectState::IDLE, gPlayerEffectTexture, gPlayerEffectClips, PLAYER_EFFECT_ANIMATION_FRAMES);
	}
	//drink
	if (!gPlayerEffectTexture[playerEffectState::DRINK].loadFromFile("assets-main/sprites/objects/items/milk_128_drink.png"))
	{
		printf("Failed to load player drink effect texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerEffectState::DRINK, gPlayerEffectTexture, gPlayerEffectClips, PLAYER_EFFECT_ANIMATION_FRAMES);
	}
	//hurt
	if (!gPlayerEffectTexture[playerEffectState::HURT].loadFromFile("assets-main/sprites/characters/player/player_bleed_128.png"))
	{
		printf("Failed to load player hurt effect texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerEffectState::HURT, gPlayerEffectTexture, gPlayerEffectClips, PLAYER_EFFECT_ANIMATION_FRAMES);
	}
	//stunt
	if (!gPlayerEffectTexture[playerEffectState::STUNT].loadFromFile("assets-main/sprites/effects/stunt_128.png"))
	{
		printf("Failed to load player stunt effect texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerEffectState::STUNT, gPlayerEffectTexture, gPlayerEffectClips, PLAYER_EFFECT_ANIMATION_FRAMES);
	}
	return success;
}

bool SpriteSheet::loadPlayerMedia()
{
	bool success = true;
	int cnt;
	//pistol
	cnt = 0;
	//idle
	if (!gPlayerTexture[cnt][playerState::IDLE].loadFromFile("assets-main/sprites/weapons/shotgun/shotgun_idle_128.png"))
	{
		printf("Failed to load player pistol idle texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::IDLE, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_PISTOL_IDLE_ANIMATION_FRAMES);
	}
	//walk
	if (!gPlayerTexture[cnt][playerState::WALK].loadFromFile("assets-main/sprites/weapons/shotgun/shotgun_walk_128.png"))
	{
		printf("Failed to load player pistol walk texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::WALK, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_PISTOL_WALK_ANIMATION_FRAMES);
	}
	//fire
	if (!gPlayerTexture[cnt][playerState::FIRE].loadFromFile("assets-main/sprites/weapons/shotgun/shotgun_fire_128.png"))
	{
		printf("Failed to load player pistol fire texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::FIRE, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_PISTOL_FIRE_ANIMATION_FRAMES);
	}
	//reload
	if (!gPlayerTexture[cnt][playerState::RELOAD].loadFromFile("assets-main/sprites/weapons/shotgun/shotgun_reload_128.png"))
	{
		printf("Failed to load player pistol reload texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::RELOAD, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_PISTOL_RELOAD_ANIMATION_FRAMES);
	}

	//rifle
	cnt = 1;
	//idle
	if (!gPlayerTexture[cnt][playerState::IDLE].loadFromFile("assets-main/sprites/weapons/heavy_cannon/heavy_cannon_full_auto_idle_128.png"))
	{
		printf("Failed to load player rifle idle texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::IDLE, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_RIFLE_IDLE_ANIMATION_FRAMES);
	}
	//walk
	if (!gPlayerTexture[cnt][playerState::WALK].loadFromFile("assets-main/sprites/weapons/heavy_cannon/heavy_cannon_full_auto_walk_128.png"))
	{
		printf("Failed to load player rifle walk texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::WALK, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_RIFLE_WALK_ANIMATION_FRAMES);
	}
	//fire
	if (!gPlayerTexture[cnt][playerState::FIRE].loadFromFile("assets-main/sprites/weapons/heavy_cannon/heavy_cannon_full_auto_fire_128.png"))
	{
		printf("Failed to load player rifle fire texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::FIRE, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_RIFLE_FIRE_ANIMATION_FRAMES);
	}
	//reload
	if (!gPlayerTexture[cnt][playerState::RELOAD].loadFromFile("assets-main/sprites/weapons/heavy_cannon/heavy_cannon_full_auto_reload_128.png"))
	{
		printf("Failed to load player rifle reload texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::RELOAD, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_RIFLE_RELOAD_ANIMATION_FRAMES);
	}

	//chaingun
	cnt = 2;
	//idle
	if (!gPlayerTexture[cnt][playerState::IDLE].loadFromFile("assets-main/sprites/weapons/chaingun/chaingun_128.png"))
	{
		printf("Failed to load player chaingun idle texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::IDLE, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_CHAINGUN_IDLE_ANIMATION_FRAMES);
	}
	//walk
	if (!gPlayerTexture[cnt][playerState::WALK].loadFromFile("assets-main/sprites/weapons/chaingun/chaingun_128.png"))
	{
		printf("Failed to load player chaingun walk texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::WALK, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_CHAINGUN_WALK_ANIMATION_FRAMES);
	}
	//fire
	if (!gPlayerTexture[cnt][playerState::FIRE].loadFromFile("assets-main/sprites/weapons/chaingun/chaingun_128.png"))
	{
		printf("Failed to load player chaingun fire texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::FIRE, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_CHAINGUN_FIRE_ANIMATION_FRAMES);
	}
	//reload
	if (!gPlayerTexture[cnt][playerState::RELOAD].loadFromFile("assets-main/sprites/weapons/chaingun/chaingun_128.png"))
	{
		printf("Failed to load player chaingun reload texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerState::RELOAD, gPlayerTexture[cnt], gPlayerClips[cnt], PLAYER_CHAINGUN_RELOAD_ANIMATION_FRAMES);
	}

	return success;
}
bool SpriteSheet::loadPlayerSkillMedia()
{
	bool success = true;
	//Dominus
	if (!gPlayerSkillTexture[playerSkillState::DOMINUS].loadFromFile(
		"assets-main/sprites/objects/bullets/skills/dominus/1.png"))
	{
		printf("Failed to load player skill: Dominus texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerSkillState::DOMINUS, gPlayerSkillTexture, gPlayerSkillClips, 1);
	}

	//Emperor's Divide
	if (!gPlayerSkillTexture[playerSkillState::EMPEROR_DIVIDE].loadFromFile(
		"assets-main/sprites/objects/bullets/skills/emperor_divide/emperor_divide_128.png"))
	{
		printf("Failed to load player skill: Emperor's Divide texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerSkillState::EMPEROR_DIVIDE, gPlayerSkillTexture, gPlayerSkillClips, PLAYER_EMPEROR_DIVIDE_ANIMATION_FRAMES);
	}
	//Call of the Forge God
	if (!gPlayerSkillTexture[playerSkillState::CALL_OF_THE_FORGE_GOD].loadFromFile(
		"assets-main/sprites/objects/bullets/skills/call_of_the_forge_god/nyan_cat_red_256.png"))
	{
		printf("Failed to load player skill: Call of the Forge God texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(playerSkillState::CALL_OF_THE_FORGE_GOD, gPlayerSkillTexture, gPlayerSkillClips, 
			PLAYER_CALL_OF_THE_FORGE_GOD_ANIMATION_FRAMES);
	}

	return success;
}
#pragma endregion

#pragma region Load Zombie Stuff
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

	// #3. Creeper
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
	if (!gZombieWeaponTexture[cnt][zombieWeaponState::ATTACK].loadFromFile("assets-main/sprites/weapons/[npc]/pistol_128.png")) //TODO: change to zombie weapon
	{
		printf("Failed to load zombie weapon texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieWeaponState::ATTACK, gZombieWeaponTexture[cnt], gZombieWeaponClips[cnt], 1);
	}
	// #1. Heavy Cannon
	cnt = 1;
	if (!gZombieWeaponTexture[cnt][zombieWeaponState::ATTACK].loadFromFile("assets-main/sprites/weapons/[npc]/heavy_cannon_128.png")) //TODO: change to zombie weapon
	{
		printf("Failed to load zombie weapon texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieWeaponState::ATTACK, gZombieWeaponTexture[cnt], gZombieWeaponClips[cnt], 1);
	}
	// #2. Shotgun
	cnt = 2;
	if (!gZombieWeaponTexture[cnt][zombieWeaponState::ATTACK].loadFromFile("assets-main/sprites/weapons/[npc]/shotgun_128.png")) //TODO: change to zombie weapon
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
bool SpriteSheet::loadZombieEffectMedia()
{
	bool success = true;
	//zombie's effect
	//idle
	if (!gZombieEffectTexture[zombieEffectState::IDLE].loadFromFile("assets-main/sprites/effects/stunt_128.png"))
	{
		printf("Failed to load player idle effect texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieEffectState::IDLE, gZombieEffectTexture, gZombieEffectClips, PLAYER_EFFECT_ANIMATION_FRAMES);
	}
	//stunt
	if (!gZombieEffectTexture[zombieEffectState::STUNT].loadFromFile("assets-main/sprites/effects/stunt_128.png"))
	{
		printf("Failed to load player stunt effect texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(zombieEffectState::STUNT, gZombieEffectTexture, gZombieEffectClips, PLAYER_EFFECT_ANIMATION_FRAMES);
	}
	return success;
}
#pragma endregion

#pragma region Load Signal Stuff
bool SpriteSheet::loadSignalMedia()
{
	bool success = true;
	//signal states
	//intro
	if (!gSignalTexture[signalState::INTRO].loadFromFile("assets-main/sprites/characters/enemies/spawner/tower_summon.png"))
	{
		printf("Failed to load signal summon texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(signalState::INTRO, gSignalTexture, gSignalClips, SIGNAL_INTRO_ANIMATION_FRAMES);
	}
	//idle
	if (!gSignalTexture[signalState::IDLE].loadFromFile("assets-main/sprites/characters/enemies/spawner/tower_idle.png"))
	{
		printf("Failed to load signal idle texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(signalState::IDLE, gSignalTexture, gSignalClips, SIGNAL_IDLE_ANIMATION_FRAMES);
	}
	//hurt
	if (!gSignalTexture[signalState::HURT].loadFromFile("assets-main/sprites/characters/enemies/spawner/tower_attacked.png"))
	{
		printf("Failed to load signal hurt texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(signalState::HURT, gSignalTexture, gSignalClips, SIGNAL_HURT_ANIMATION_FRAMES);
	}
	//dead
	if (!gSignalTexture[signalState::DEAD].loadFromFile("assets-main/sprites/characters/enemies/spawner/tower_dead.png"))
	{
		printf("Failed to load signal dead texture!\n");
		success = false;
	}
	else
	{
		loadSpritesheet(signalState::DEAD, gSignalTexture, gSignalClips, SIGNAL_DEAD_ANIMATION_FRAMES);
	}
	return success;
}
#pragma endregion

#pragma region Set Animations for Player
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
		else if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "chaingun")
		{
			myPlayer.currentTotalFrame = PLAYER_CHAINGUN_IDLE_ANIMATION_FRAMES;
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
		else if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "chaingun")
		{
			myPlayer.currentTotalFrame = PLAYER_CHAINGUN_WALK_ANIMATION_FRAMES;
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
		else if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "chaingun")
		{
			myPlayer.currentTotalFrame = PLAYER_CHAINGUN_FIRE_ANIMATION_FRAMES;
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
		else if (myPlayer.myWeapon[myPlayer.currentWeapon].getName() == "chaingun")
		{
			myPlayer.currentTotalFrame = PLAYER_CHAINGUN_RELOAD_ANIMATION_FRAMES;
		}
		break;
	case playerState::DEAD:

		break;
	}
	
	//printf("current weapon: %d, current frame: %d\n", myPlayer.currentWeapon, myPlayer.currentFrame);
	myPlayer.setAnimation(gPlayerTexture[myPlayer.currentWeapon][myPlayer.currentState],
			gPlayerClips[myPlayer.currentWeapon][myPlayer.currentState][myPlayer.currentFrame]);
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
	myPlayerEffect.currentTotalFrame = PLAYER_EFFECT_ANIMATION_FRAMES;
	myPlayerEffect.setAnimation(gPlayerEffectTexture[myPlayerEffect.currentState],
		gPlayerEffectClips[myPlayerEffect.currentState][myPlayerEffect.currentFrame]);
}
void SpriteSheet::setPlayerSkillAnimation(playerSkill& myPlayerSkill)
{
	myPlayerSkill.setAnimation(gPlayerSkillTexture, gPlayerSkillClips);
}
#pragma endregion

#pragma region Set Animation for Zombies
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

	source.currentState = zombieWeaponState::ATTACK;
	source.currentFrame = 0;

	source.setAnimation(gZombieWeaponTexture[source.type][source.currentState], 
		gZombieWeaponClips[source.type][source.currentState][source.currentFrame]);
}
void SpriteSheet::setZombieEffectAnimation(zombieEffect& source)
{
	switch (source.currentState)
	{
	case zombieEffectState::STUNT:
		if (source.currentFrame > PLAYER_EFFECT_ANIMATION_FRAMES - 1)
		{
			source.currentFrame = 0;
		}
		break;
	default:
		break;
	}

	source.setAnimation(gZombieEffectTexture[source.currentState],
		gZombieEffectClips[source.currentState][source.currentFrame]);
}
#pragma endregion

#pragma region Set Animation for Signal
void SpriteSheet::setSignalAnimation(signal& source)
{
	switch (source.currentState)
	{
	case signalState::INTRO:
		if (source.currentFrame > SIGNAL_INTRO_ANIMATION_FRAMES - 1)
		{
			source.currentState = source.health > 0 ? signalState::IDLE : signalState::DEAD;
			source.currentFrame = 0;
		}
		break;
	case signalState::IDLE:
		if (source.currentFrame > SIGNAL_IDLE_ANIMATION_FRAMES - 1)
		{
			source.currentFrame = 0;
		}
		break;
	case signalState::HURT:
		if (source.currentFrame > SIGNAL_HURT_ANIMATION_FRAMES - 1)
		{
			source.currentState = source.health > 0? signalState::IDLE : signalState::DEAD;
			source.currentFrame = 0;
		}
		break;
	case signalState::DEAD:
		source.currentFrame = 0;
		break;
	default:
		break;
	}

	source.setAnimation(gSignalTexture[source.currentState],
		gSignalClips[source.currentState][source.currentFrame]);
}
#pragma endregion

void SpriteSheet::updateAnimation(
	player& myPlayer,
	playerAnimation& myPlayerAnimation,
	playerEffect& myPlayerEffect,
	playerSkill& myPlayerSkill,
	std::vector<zombie>& zombies,
	std::vector<zombieEffect>& zombieEffects,
	std::vector<signal>& signals,
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

		myPlayerSkill.updateAnimation();

		for (auto& zZ : zombies)
		{
			// increase Animation Frame for Zombie
			if (zZ.currentState != zombieState::DEAD)
			{
				zZ.currentFrame++;
				continue;
			}

			if (zZ.currentFrame <= ZOMBIE_WALK_ANIMATION_FRAMES - 1)
			{
				zZ.currentFrame++;
			}
		}

		for (auto& zEffect : zombieEffects)
		{
			if (zEffect.currentState != zombieEffectState::IDLE)
			{
				zEffect.currentFrame++;
			}
		}
		for (auto& sS : signals)
		{
			if (sS.currentState != signalState::DEAD)
			{
				sS.currentFrame++;
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
	playerSkill& myPlayerSkill,
	int mouseX,
	int mouseY,
	std::vector<gameObject>& trees,
	std::vector<gameObject>& harmZones,
	std::vector<gameObject>& bloodpools,
	std::vector<zombie>& zombies,
	std::vector<bullet>& bullets,
	std::vector<signal>& signals,
	std::vector<gameObject>& healthPickUps,
	LTimer deltaTimer
)
{
	//set player's animation based on current state
	setPlayerAnimation(myPlayer);
	setPlayerAnimationAnimation(myPlayerAnimation);
	setPlayerSkillAnimation(myPlayerSkill);

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
	float dirX = myPlayer.vx * myPlayer.speed * deltaTimer.getDeltaTime() * myPlayer.isActive;
	float dirY = myPlayer.vy * myPlayer.speed * deltaTimer.getDeltaTime() * myPlayer.isActive;
	myPlayer.px += dirX;
	myPlayer.py += dirY;
	myPlayerAnimation.px = myPlayer.px;
	myPlayerAnimation.py = myPlayer.py;
	myPlayerEffect.px = myPlayer.px;
	myPlayerEffect.py = myPlayer.py;

	//check collision with game objects
	//zombies
	/*for (int i = 0; i < zombies.size(); i++)
	{
		if (zombies[i].currentState != zombieState::DEAD
			&& myPlayer.checkCollision(zombies[i], zombies[i].attackRange))
		{
			myPlayer.px -= dirX;
			myPlayer.py -= dirY;
			break;
		}
	}*/

	//signals
	for (int i = 0; i < signals.size(); i++)
	{
		if (signals[i].currentState != signalState::DEAD
			&& myPlayer.checkCollision(signals[i]))
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
				healthPickUps.erase(healthPickUps.begin() + i);
				Sound::GetInstance()->playDrinkMilk();
				myPlayerEffect.currentState = playerEffectState::DRINK;
				myPlayerEffect.gPlayerEffectTimeCounter[myPlayerEffect.currentState] = 0.0f;
			}
			break;
		}
	}
	if (myPlayer.isActive == 0)
	{
		myPlayerEffect.currentState = playerEffectState::STUNT;
		myPlayerEffect.gPlayerEffectTimeCounter[myPlayerEffect.currentState] = 0.0f;
	}
	else
	{
		myPlayerEffect.gPlayerEffectTimeCounter[playerEffectState::STUNT] = PLAYER_EFFECT_ANIMATION_TIME_INTERVAL;
	}
	setPlayerEffectAnimation(myPlayerEffect);

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
			Sound::GetInstance()->playPlayerHurt();
			break;
		}
	}

	//render player++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	myPlayerAnimation.render(camera);
	myPlayer.render(camera);
	myPlayerEffect.render(camera);
	

	myPlayerSkill.activateSkill(myPlayer);
}
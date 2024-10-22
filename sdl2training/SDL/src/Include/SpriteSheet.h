#pragma once
#include "Include/GameObject.h"
#include "Sound.h"

#include "Include/Player.h"
#include "Include/PlayerAnimation.h"
#include "Include/PlayerEffect.h"
#include "Include/PlayerSkill.h"
#include "Include/Weapon.h"

#include "Include/Zombie.h"
#include "Include/ZombieWeapon.h"
#include "Include/ZombieEffect.h"

#include "Include/Signal.h"

class SpriteSheet {
public:
#pragma region Animations
	double animationTimeCounter;
#pragma endregion
	SpriteSheet();

#pragma region Load SpriteSheet
	//load Sprite Sheet for Player
	void loadSpritesheet(
		enum playerAnimationState state, 
		std::map<playerAnimationState, LTexture>& spritesheet,
		std::map<playerAnimationState, std::vector <SDL_Rect>>& spritesheetClip, 
		int totalFrame
	);
	void loadSpritesheet(
		enum playerState state, 
		std::map<playerState, LTexture>& spritesheet,
		std::map<playerState, std::vector <SDL_Rect>>& spritesheetClip, 
		int totalFrame
	);
	void loadSpritesheet(
		enum playerEffectState state,
		std::map<playerEffectState, LTexture>& spritesheet,
		std::map<playerEffectState,
		std::vector <SDL_Rect>>&spritesheetClip,
		int totalFrame
	);
	void loadSpritesheet(
		enum playerSkillState state,
		std::map<playerSkillState, LTexture>& spritesheet,
		std::map<playerSkillState,
		std::vector <SDL_Rect>>&spritesheetClip,
		int totalFrame
	);
	//load Sprite Sheet for Enemy
	void loadSpritesheet(
		enum zombieState state, 
		std::map<zombieState, LTexture>& spritesheet,
		std::map<zombieState, std::vector <SDL_Rect>>& spritesheetClip, 
		int totalFrame
	);
	void loadSpritesheet(
		enum zombieWeaponState state,
		std::map<zombieWeaponState, LTexture>& spritesheet,
		std::map<zombieWeaponState, std::vector <SDL_Rect>>& spritesheetClip,
		int totalFrame
	);
	void SpriteSheet::loadSpritesheet(
		enum zombieEffectState state,
		std::map<zombieEffectState, LTexture>& spritesheet,
		std::map<zombieEffectState, std::vector <SDL_Rect>>& spritesheetClip,
		int totalFrame
	);
	//load Sprite Sheet for Signal
	void loadSpritesheet(
		enum signalState state,
		std::map<signalState, LTexture>& spritesheet,
		std::map<signalState, std::vector <SDL_Rect>>& spritesheetClip,
		int totalFrame
	);

	void loadSpritesheet(LTexture& spritesheet, std::vector <SDL_Rect>& spritesheetClip, int totalFrame);
	//Load Clips
	void loadClips(LTexture& spritesheet, std::vector<SDL_Rect>& spritesheetClip, int totalClip);
#pragma endregion

#pragma region Textures
	///player animations
	std::map<playerAnimationState, LTexture> gPlayerAnimationTexture;
	std::map<playerAnimationState, std::vector <SDL_Rect>> gPlayerAnimationClips;
	///player effects
	std::map<playerEffectState, LTexture> gPlayerEffectTexture;
	std::map<playerEffectState, std::vector <SDL_Rect>> gPlayerEffectClips;
	///weapons
	std::map<playerState, LTexture> gPlayerPistolTexture;
	std::map<playerState, std::vector <SDL_Rect>> gPlayerPistolClips;
	std::map<playerState, LTexture> gPlayerRifleTexture;
	std::map<playerState, std::vector <SDL_Rect>> gPlayerRifleClips;
	///player skills
	std::map<playerSkillState, LTexture> gPlayerSkillTexture;
	std::map<playerSkillState, std::vector <SDL_Rect>> gPlayerSkillClips;

	///enemies
	std::map<zombieState, LTexture> gZombieTexture[4];
	std::map<zombieState, std::vector <SDL_Rect>> gZombieClips[4];
	//enemy weapons
	std::map<zombieWeaponState, LTexture> gZombieWeaponTexture[4];
	std::map<zombieWeaponState, std::vector <SDL_Rect>> gZombieWeaponClips[4];
	//enemy effects
	std::map<zombieEffectState, LTexture> gZombieEffectTexture;
	std::map<zombieEffectState, std::vector <SDL_Rect>> gZombieEffectClips;
#pragma endregion

	//signal
	std::map<signalState, LTexture> gSignalTexture;
	std::map<signalState, std::vector <SDL_Rect>> gSignalClips;

	//Check load media
	///load player
	bool loadPlayerAnimationMedia();
	bool loadPlayerEffectMedia();
	bool loadPlayerMedia();
	bool loadPlayerSkillMedia();

	///load zombie
	bool loadZombieMedia();
	bool loadZombieWeaponMedia();
	bool loadZombieEffectMedia();

	///load signal
	bool loadSignalMedia();

	//set animations
	///set player's
	void setPlayerAnimation(player& myPlayer);
	void setPlayerAnimationAnimation(playerAnimation& myPlayerAnimation);
	void setPlayerEffectAnimation(playerEffect& myPlayerEffect);
	void setPlayerSkillAnimation(playerSkill& myPlayerSkill);

	/// set zombie's
	void setZombieAnimation(zombie& source);
	void setZombieWeaponAnimation(zombieWeapon& source);
	void setZombieEffectAnimation(zombieEffect& source);

	///set signal's
	void setSignalAnimation(signal& source);

	//update animation
	void updateAnimation(
		player& myPlayer, 
		playerAnimation& myPlayerAnimation,
		playerEffect& myPlayerEffect,
		playerSkill& myPlayerSkill,
		std::vector<zombie>& zombies,
		std::vector<zombieEffect>& zombieEffects,
		std::vector<signal>& signals,
		LTimer deltaTimer
	);
	void updatePlayer(
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
	);
};




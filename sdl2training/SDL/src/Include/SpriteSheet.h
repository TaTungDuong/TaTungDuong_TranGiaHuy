#pragma once
#include "Include/GameObject.h"
#include "Include/Weapon.h"
#include "Include/Player.h"
#include "Include/Zombie.h"
#include "Include/ZombieWeapon.h"
#include "Include/PlayerAnimation.h"
#include "Include/PlayerEffect.h"
#include "Include/Audio.h"

class SpriteSheet {
public:
#pragma region Animations
	double animationTimeCounter;
#pragma endregion
	SpriteSheet();

#pragma region Load SpriteSheet
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
	void loadSpritesheet(
		enum playerEffectState state,
		std::map<playerEffectState, LTexture>& spritesheet,
		std::map<playerEffectState,
		std::vector <SDL_Rect>>&spritesheetClip,
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
	///enemies
	std::map<zombieState, LTexture> gZombieTexture[4];
	std::map<zombieState, std::vector <SDL_Rect>> gZombieClips[4];
	//enemy weapons
	std::map<zombieWeaponState, LTexture> gZombieWeaponTexture[4];
	std::map<zombieWeaponState, std::vector <SDL_Rect>> gZombieWeaponClips[4];
#pragma endregion

	//Check load media
	bool loadPlayerAnimationMedia();
	bool loadPlayerEffectMedia();
	bool loadPlayerMedia();
	bool loadZombieMedia();
	bool loadZombieWeaponMedia();

	//set animations
	void setPlayerAnimation(player& myPlayer);
	void setPlayerAnimationAnimation(playerAnimation& myPlayerAnimation);
	void setPlayerEffectAnimation(playerEffect& myPlayerEffect);
	void setZombieAnimation(zombie& source);
	void setZombieWeaponAnimation(zombieWeapon& source);

	//update animation
	void updateAnimation(
		player& myPlayer, 
		playerAnimation& myPlayerAnimation,
		playerEffect& myPlayerEffect,
		std::vector<zombie>& zombies,
		LTimer deltaTimer
	);
	void updatePlayer(
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
	);
};




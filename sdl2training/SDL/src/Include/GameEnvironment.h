#pragma once
#include "Include/GameObject.h"
#include "Include/Weapon.h"
#include "Include/SpriteSheet.h"
#include "Include/GameObjective.h"

#include "Sound.h"

class GameEnvironment
{
public:
#pragma region Textures
	//static textures
	LTexture gGroundTexture;
	LTexture gTreeTexture;
	LTexture gBulletTexture;
	LTexture gZombieBulletTextures[4];
	LTexture gBloodPoolTexture;
	LTexture gHealthPickUpTexture;

#pragma region Trees
	std::vector <SDL_Rect> gTreeClips;
#pragma endregion

#pragma region Vectors
	std::vector<bullet> bullets;
	std::vector<gameObject> trees;
	std::vector<gameObject> harmZones;
	std::vector<gameObject> bloodpools;
	std::vector<zombie> zombies;
	std::vector<zombieWeapon> zombieWeapons;
	std::vector<zombieBullet> zombieBullets;
	std::vector<zombieEffect> zombieEffects;
	std::vector<signal> signals;
	std::vector<gameObject> signalZones;
	std::vector<gameObject> healthPickUps;
#pragma endregion
	
	bool loadMedia(SpriteSheet& m_SpriteSheet); //check load medias

	bool canSpawnZombie = true;
	zombie myZombie;
	zombieWeapon myZombieWeapon;
	zombieEffect myZombieEffect;

#pragma region Render and Update functions
	void renderGround(SDL_Rect& camera);
	void renderBloodPool(SDL_Rect& camera);
	void spawnSignal();
	void spawnZombie();
	void updateZombie(
		SpriteSheet& m_SpriteSheet, 
		player& myPlayer, 
		playerSkill& myPlayerSkill,
		GameObjective& m_GameObjective,
		SDL_Rect& camera
	);
	void updateBullet(
		player& myPlayer,
		GameObjective& m_GameObjective
	);
	void updateZombieBullet(player& myPlayer, playerEffect& myPlayerEffect);
#pragma endregion

	//free
	void init();
	void close();
};
#pragma region create Objects
void createGameObjectRandom(
	gameObject sourceObject,
	std::vector<gameObject>& vectorList,
	int total, int minSize, int maxSize, int rotation,
	int maxType
);
#pragma endregion
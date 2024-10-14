#pragma once
#include "Include/GameObject.h"
#include "Include/Weapon.h"
#include "Include/Audio.h"
#include "Include/SpriteSheet.h"
#include "Include/GameObjective.h"

class GameEnvironment
{
public:
#pragma region Textures
	//static textures
	LTexture gGroundTexture;
	LTexture gTreeTexture;
	LTexture gBulletTexture;
	LTexture gBloodPoolTexture;
	LTexture gHealthPickUpTexture;

#pragma region Trees
	std::vector <SDL_Rect> gTreeClips;
#pragma endregion

#pragma region Vectors
	std::vector<gameObject> trees;
	std::vector<gameObject> harmZones;
	std::vector<gameObject> bloodpools;
	std::vector<zombie> zombies;
	std::vector<bullet> bullets;
	std::vector<gameObject> signalZones;
	std::vector<gameObject> healthPickUps;
#pragma endregion
	
	bool loadMedia(SpriteSheet& m_SpriteSheet); //check load medias

	bool canSpawnZombie = true;
	zombie myZombie;

#pragma region Render and Update functions
	void renderGround(SDL_Rect& camera);
	void renderBloodPool(SDL_Rect& camera);
	void spawnZombie();
	void updateZombie(SpriteSheet& m_SpriteSheet, player& myPlayer, audioManager& myAudio, SDL_Rect& camera);
	void updateBullet(
		player& myPlayer, 
		GameObjective& m_GameObjective, 
		audioManager& myAudio
	);
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
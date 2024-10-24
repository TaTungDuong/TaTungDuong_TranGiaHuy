#pragma once
#include "Include/GameObject.h"
#include "Sound.h"

#include "Include/Weapon.h"

class SpriteSheet;
enum class playerState
{
	IDLE, WALK, FIRE, RELOAD, DEAD
};

class player : public  gameObject
{
public:
	//player stat
	float health;
	int skill; //value for skill cooldown timer bar
	int speed;
	int isActive; //if true (isActive == 1), player can move and attack; also applied for when player is stunt
	int vx;
	int vy;

	playerState currentState;
	playerState previousState;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	//weapon related
	int currentWeapon;
	weapon myWeapon[PLAYER_WEAPON_SLOT];

	player();
	void initPlayer();
	bullet attack(SDL_Rect& camera, player& myPlayer); //return true if player just attack
	void cycleWeapon();
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);
	void calRotation(SDL_Rect& camera, int x, int y);

	bool checkWeapon();// check if weapon can fire
	bool checkSpawnZone();//return true if the player is in spawn zone so the enemies can be spawned
private:
	const int PLAYER_START_X = 2750;
	const int PLAYER_START_Y = 13185;
};

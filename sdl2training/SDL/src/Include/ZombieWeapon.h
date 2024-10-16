#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Player.h"
#include "Include/Timer.h"

extern LTimer deltaTimer;
extern player myPlayer;

class SPriteSheet;
enum class zombieWeaponState
{
	IDLE, ATTACK, RELOAD
};

class zombieWeapon : public gameObject
{
public:
	zombieWeaponState currentState;

	float vx;
	float vy;

	float health;
	float speed;
	float damage;
	float attackRange;
	float attackSpeed; //attack speed in second

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	zombieWeapon();
	void init(gameObject source);
	void move(gameObject source, gameObject target);
	bool attack(player& target);
	void hurt();
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera, bool isAlive);

private:
	bool isFlipped;
	float attackTimer;
};

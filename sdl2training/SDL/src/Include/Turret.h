#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Timer.h"

#include "Include/Player.h"
#include "Include/ZombieWeapon.h"

class turret : public gameObject
{
public:
	float vx;
	float vy;

	int type;
	float health;
	float speed;

	const float lagTimeInterval = 1.5f; // the time between entrance and attack
	const float lifeTimeInterval = 5.0f + lagTimeInterval;
	float lifeTimeCounter;
	const float entranceTimeInterval = 0.432; // time value of turret sliding into action
	float entranceTimeCounter;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	turret();
	void initTurret(gameObject& source);
	void move();
	bool attack(); //return true if turret can shoot
	void hurt(player& myPlayer);
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);
	void calPosition(player& myPlayer, float distance);

private:
	bool isReady; // if true, turret can attack
	float attackSpeed;
	float attackTimer;
	const float ratio = 1.5f;
};

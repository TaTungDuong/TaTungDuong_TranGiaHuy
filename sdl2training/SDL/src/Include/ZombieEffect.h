#pragma once
#include "Include/GameObject.h"
#include "Include/ZombieWeapon.h"
#include "Include/Zombie.h"

enum class zombieEffectState
{
	STUNT, IDLE
};

class zombieEffect : public  gameObject
{
public:
	//zombie stat
	int speed;
	int vx;
	int vy;

	bool isFlipped;

	zombieEffectState currentState;
	zombieEffectState previousState;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	zombieEffect();
	void init(zombie& source);
	void move(gameObject source, gameObject target);
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);

	std::map<zombieEffectState, float> gZombieEffectInterval;
	std::map<zombieEffectState, float> gZombieEffectTimeCounter;
};
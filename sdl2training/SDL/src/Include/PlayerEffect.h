#pragma once
#include "Include/GameObject.h"
#include "Include/Weapon.h"
#include "Include/Player.h"

enum class playerEffectState
{
	DRINK, HURT, IDLE, STUNT
};

class playerEffect : public  gameObject
{
public:
	//player stat
	int speed;
	int vx;
	int vy;

	playerEffectState currentState;
	playerEffectState previousState;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	playerEffect();
	void initPlayer();
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);
	void calRotation(SDL_Rect& camera, int x, int y);

	std::map<playerEffectState, float> gPlayerEffectInterval;
	std::map<playerEffectState, float> gPlayerEffectTimeCounter;
};
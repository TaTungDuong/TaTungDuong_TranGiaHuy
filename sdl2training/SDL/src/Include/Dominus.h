#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Timer.h"
#include "Include/Player.h"
#include "Include/PlayerEffect.h"

class Dominus : public gameObject
{
public:
	float damage = 2.0f;
	const float lifeTimeInterval = 5.0f;
	float lifeTimeCounter;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	Dominus();
	void initPlayer();
	void move();
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);
};
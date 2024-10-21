#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Timer.h"
#include "Include/Player.h"
#include "Include/PlayerEffect.h"

//Emperor Divide
class emperorDivide : public gameObject
{
public:
	float vx;
	float vy;

	float speed;
	float damage = 10.0f;
	bool isActive; //if true, the soldier can move and damage the enemies

	const float lifeTimeInterval = 3.0f;
	float lifeTimeCounter;
	const float moveTimeInterval = 0.5f;
	float moveTimeCounter;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	emperorDivide();
	void initPlayer();
	void move();
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);
	void calRotation(SDL_Rect& camera, int x, int y);
	void calPosition(player& myPlayer, float distance);

	bool isFlipped;
private:
	const float ratio = 1.5f;
};
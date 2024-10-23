#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Timer.h"
#include "Include/Player.h"
#include "Include/PlayerEffect.h"

//Emperor Divide
class EmperorDivide : public gameObject
{
public:
	float vx;
	float vy;

	float speed;
	float damage = 2.0f;
	bool isReady; //if true, the soldier has finished the entrance and ready to attack
	bool isActive; //if true, the soldier can move and damage the enemies

	const float lifeTimeInterval = 5.0f;
	float lifeTimeCounter;
	const float entranceTimeInterval = 0.432;
	float entranceTimeCounter;
	const float moveTimeInterval = 0.5f;
	float moveTimeCounter;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	EmperorDivide();
	void initPlayer();
	void move();
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);
	void calPosition(player& myPlayer, float distance);

	bool isFlipped;
private:
	const float ratio = 1.5f;
};
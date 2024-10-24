#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Timer.h"
#include "Include/Player.h"
#include "Include/PlayerEffect.h"

//Call Of The Forge God
class CallOfTheForgeGod : public gameObject
{
public:
	float vx;
	float vy;

	float speed;
	float damage = 1.0f;
	bool isActive; //if true, the soldier can move and damage the enemies

	const float distance = SCREEN_WIDTH * 2 / 3; // spawn distance to player
	const float lifeTimeInterval = 7.5f;
	float lifeTimeCounter;
	const float moveTimeInterval = 0.5f;
	float moveTimeCounter;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	CallOfTheForgeGod();
	void initPlayer();
	void move(player& myPlayer);
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);
	void calRotation(SDL_Rect& camera, int x, int y);
	void calPosition(player& myPlayer);

	bool isRecasted; //if true, the skill is already recasted and will be gone
	bool isFlipped;
private:
	const float ratioSpeed = 2.5f;
	const float ratioScale = 1.0f;
};
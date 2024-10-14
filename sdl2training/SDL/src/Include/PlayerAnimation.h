#pragma once
#include "Include/GameObject.h"
#include "Include/Weapon.h"
#include "Include/Player.h"

enum class playerAnimationState
{
	IDLE, WALK, FIRE, RELOAD, DEAD
};

class playerAnimation : public  gameObject
{
public:
	//player stat
	int speed;
	int vx;
	int vy;

	playerAnimationState currentState;
	playerAnimationState previousState;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	playerAnimation();
	void initPlayer();
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);
	void calRotation(SDL_Rect& camera, int x, int y);
};

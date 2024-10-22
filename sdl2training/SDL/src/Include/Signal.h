#pragma once
#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Player.h"
#include "Include/Timer.h"

enum class signalState
{
	INTRO, IDLE, HURT, DEAD
};

class signal : public gameObject
{
public:
	float health;
	signalState currentState;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	signal();
	void initSignal(gameObject& source);
	void hurt(player& myPlayer);
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);

};
#pragma once
#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Timer.h"

#include "Include/Player.h"

enum class wardenCloneState
{
	FAKE, REAL
};

class wardenClone : public gameObject
{
public:
	float vx;
	float vy;

	int isActive;// if 1, clone can move

	int type;
	float health;
	float speed;
	wardenCloneState currentState;
	
	//entrance position
	float ex;
	float ey;
	const float entranceTimeInterval = 1;//value for when clone entrance into action
	float entranceTimeCounter;
	const float moveTimeInterval = 2.5f;//value for when clone change direction when moving
	float moveTimeCounter;
	const float lifeTimeInterval = 5.0f;//value for the lifetime of clone
	float lifeTimeCounter;

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	wardenClone();
	void initWardenClone(player& myPlayer, wardenCloneState state);
	void move(player& myPlayer);
	void hurt(player& myPlayer);
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);
	void calPosition(player& myPlayer, gameObject source);

private:
	const float ratio = 1.5f;
};

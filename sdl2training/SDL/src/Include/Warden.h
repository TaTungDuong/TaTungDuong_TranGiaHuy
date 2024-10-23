#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Player.h"
#include "Include/Timer.h"

enum class WardenState
{
	IDLE, 
	WALK, 
	IDLE_TO_STUNT, 
	STUNT,
	STUNT_TO_IDLE,
	DEAD
};

class Warden : public gameObject
{
public:
	WardenState currentState;

	float vx;
	float vy;

	float health;
	float speed;
	int isActive; //if true, Warden can move and attack; also applied for stunt
	float damage;
	float attackRange;
	float attackSpeed; //attack speed in second

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	Warden();
	void initWarden(player& myPlayer);
	void move(player& myPlayer);
	bool attack(player& target);
	void hurt(player& myPlayer);
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);

private:
	float attackTimer;
	bool isFlipped;
};



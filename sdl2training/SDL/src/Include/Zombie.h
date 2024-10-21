#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Player.h"
#include "Include/Timer.h"

extern LTimer deltaTimer;
extern player myPlayer;

class SpriteSheet;
enum class zombieState
{
	WALK, ATTACK, DEAD
};

class zombie : public gameObject
{
public:
	zombieState currentState;

	float vx;
	float vy;

	float health;
	float speed;
	int isActive; //if true, zombie can move and attack; also applied for stunt
	float damage;
	float attackRange;
	float attackSpeed; //attack speed in second

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	zombie();
	void init();
	void move(gameObject target);
	bool attack(player& target);
	void hurt();
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);

private:
	float attackTimer;
	bool isFlipped;
};
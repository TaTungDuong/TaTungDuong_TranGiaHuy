#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Player.h"
#include "Include/Timer.h"

enum class WardenState
{
	INTRO,
	IDLE, 
	WALK, 
	HURT,
	DIVE,
	HIDE,
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
	void hurt(float damage);
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);

	bool canCollide(); // return true if warden can collide with objects

private:
	float attackTimer;
	bool isFlipped;

	//warden's skill sets
	void cooldown();
	/// <summary>
	/// Skill: Dive
	/// Warden dive into ground to hide from player's attacks
	/// </summary>
	bool canDive;//return true if warden can dive
	float diveTimeCounter; 
	const float diveTimeInterval = 5.0f;
	float diveCooldownCounter;
	const float diveCooldownInterval = 5.0;// 10.0f;
	void initDive();
	void attackDive();
};



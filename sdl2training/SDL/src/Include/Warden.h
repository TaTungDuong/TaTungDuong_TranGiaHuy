#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Timer.h"

#include "Include/Player.h"
#include "Include/Turret.h"

class WardenBullet : public gameObject
{
public:
	int speed;
	int damage;
	float vx;
	float vy;
	float lifeTime;
	float max_lifeTime;

	WardenBullet(SDL_Rect& camera, gameObject source);

	//calculate warden bullet motions
	void updateBullet(player& myPlayer);
	void updateType0(player& myPlayer);
	void updateType1(player& myPlayer);
	void updateType2(player& myPlayer);
};

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
	void hurt(float damage);
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera);

	bool canCollide(); // return true if warden can collide with objects

	const int number_of_turrets = 5;

	bool attack(player& target, std::vector<turret>& turrets, std::vector<zombieBullet>& zombieBullets);
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

	/// <summary>
	/// Skill: Summon Turrets
	/// Warden summon some shooting turrets from sky
	/// </summary>
	bool canTurret;//return true if warden can summon turrets
	float turretTimeCounter;
	float turretTimeInterval;
	float turretCooldownCounter;
	const float turretCooldownInterval = 10.0f;
	void initTurret(std::vector<turret>& turrets);
	void attackTurret(std::vector<turret>& turrets, std::vector<zombieBullet>& zombieBullets);
};



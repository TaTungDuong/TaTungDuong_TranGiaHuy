#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Timer.h"

#include "Include/Player.h"
#include "Include/Turret.h"
#include "Include/WardenClone.h"

class WardenBullet : public gameObject
{
public:
	int type;
	WardenBullet(SDL_Rect& camera, gameObject source);
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
	bool isReady;
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

	const int number_of_fires = 3;
	const int number_of_turrets = 8;
	const int number_of_clones = 8;

	bool attack(
		player& target,
		std::vector<wardenClone>& wardenClones,
		std::vector<turret>& turrets, 
		std::vector<zombieBullet>& zombieBullets
	);
private:
	float attackTimer;
	bool isFlipped;

	//warden's skill sets
	///skill cooldown time will be random after each use
	void cooldown();

	/// <summary>
	/// Skill: Fire
	/// Warden fire multiple round bullets from its hands
	/// </summary>
	bool canFire;//return true if warden can fire
	int fireCounter; //calculate the turn of fire (<= number_of_fires)
	float fireTimeCounter;
	const float fireTimeInterval = 0.5f;
	float fireCooldownCounter;
	float fireCooldownInterval;
	const float minFireCooldownTimepoint = 5.0f;
	const float maxFireCooldownTimepoint = 7.5f;
	void initFire();
	void attackFire(std::vector<zombieBullet>& zombieBullets);

	/// <summary>
	/// Skill: Dive
	/// Warden dive into ground to hide from player's attacks
	/// </summary>
	bool canDive;//return true if warden can dive
	float diveTimeCounter; 
	const float diveTimeInterval = 5.0f;
	float diveCooldownCounter;
	float diveCooldownInterval;
	const float minDiveCooldownTimepoint = 12.5f;
	const float maxDiveCooldownTimepoint = 15.0f;
	void initDive(
		player& myPlayer,
		std::vector<wardenClone>& wardenClones
	);
	void attackDive(
		player& myPlayer,
		std::vector<wardenClone>& wardenClones
	);

	/// <summary>
	/// Skill: Summon Turrets
	/// Warden summon some shooting turrets from sky
	/// </summary>
	bool canTurret;//return true if warden can summon turrets
	float turretTimeCounter;
	float turretTimeInterval;
	float turretCooldownCounter;
	float turretCooldownInterval;
	const float minTurretCooldownTimepoint = 10.0f;
	const float maxTurretCooldownTimepoint = 15.0f;
	void initTurret(player& myPlayer, std::vector<turret>& turrets);
	void attackTurret(player& myPlayer, std::vector<turret>& turrets, std::vector<zombieBullet>& zombieBullets);
};



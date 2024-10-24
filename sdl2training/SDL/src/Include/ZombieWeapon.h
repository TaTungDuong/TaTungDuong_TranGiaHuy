#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Player.h"
#include "Include/Timer.h"

extern LTimer deltaTimer;
extern player myPlayer;

class zombieBullet : public gameObject
{
public:
	int speed;
	int damage;
	float vx;
	float vy;
	float lifeTime;
	float max_lifeTime;

	zombieBullet(SDL_Rect& camera, gameObject source);
	//~zombieBullet();
	/*void create(gameObject source, int targetX, int targetY);*/
	
	//calculate zombie bullet motions
	void updateBullet();
	void updateType0();
	void updateType1();
	void updateType2();
};

class SpriteSheet;
enum class zombieWeaponState
{
	IDLE, ATTACK, RELOAD
};

class zombieWeapon : public gameObject
{
public:
	zombieWeaponState currentState;

	float vx;
	float vy;

	float health;
	float speed;
	float damage;
	float attackRange;
	float attackSpeed; //attack speed in second
	int isActive;// if true, can attack player

	//animation related
	LTexture* currentTexture;
	SDL_Rect* currentClip;
	int currentFrame;
	int currentTotalFrame;

	zombieWeapon();
	void init(gameObject source);
	void move(gameObject source, gameObject target);
	
	//zombie attack types
	bool attack(
		player& target, 
		gameObject source,
		std::vector<zombieBullet>& zombieBullets, 
		bool isAlive
	);
	void attackType0(
		player& target,
		gameObject source,
		std::vector<zombieBullet>& zombieBullets
	);
	void attackType1(
		player& target,
		gameObject source,
		std::vector<zombieBullet>& zombieBullets
	);
	void attackType2(
		player& target,
		gameObject source,
		std::vector<zombieBullet>& zombieBullets
	);


	void hurt();
	void setAnimation(LTexture& targetTexture, SDL_Rect& targetClip);
	void render(SDL_Rect& camera, bool isAlive);

private:
	bool isFlipped;
	float attackTimer;
};



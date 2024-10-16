#include "Include/ZombieWeapon.h"

zombieWeapon::zombieWeapon()
{
	vx = 0;
	vy = 0;

	size = SCREEN_HEIGHT / 7;
	type = 0;
	attackTimer = 0;
}

void zombieWeapon::init(gameObject source)
{
	//set weapon position based on enemy's position
	setPosition(source.px, source.py);
	setRenderPosition(px, py);

	//set random type
	int randomType = GetRandomInt(0, 8, 1);
	//randomType = 0; //temp
	if (randomType <= NORMAL_ZOMBIE_CHANCE) //normal zombie
	{
		type = 0;
		health = NORMAL_ZOMBIE_HEALTH;
		speed = NORMAL_ZOMBIE_SPEED;
		damage = NORMAL_ZOMBIE_DAMAGE;
		attackRange = NORMAL_ZOMBIE_ATTACK_RANGE;
		attackSpeed = NORMAL_ZOMBIE_ATTACK_SPEED;
	}
	else if (randomType <= NORMAL_ZOMBIE_CHANCE + FAST_ZOMBIE_CHANCE) //fast zombie
	{
		type = 1;
		health = FAST_ZOMBIE_HEALTH;
		speed = FAST_ZOMBIE_SPEED;
		damage = FAST_ZOMBIE_DAMAGE;
		attackRange = FAST_ZOMBIE_ATTACK_RANGE;
		attackSpeed = FAST_ZOMBIE_ATTACK_SPEED;
	}
	else if (randomType <= NORMAL_ZOMBIE_CHANCE + FAST_ZOMBIE_CHANCE + TANK_ZOMBIE_CHANCE) //tank zombie
	{
		type = 2;
		health = TANK_ZOMBIE_HEALTH;
		speed = TANK_ZOMBIE_SPEED;
		damage = TANK_ZOMBIE_DAMAGE;
		attackRange = TANK_ZOMBIE_ATTACK_RANGE;
		attackSpeed = TANK_ZOMBIE_ATTACK_SPEED;
	}
	type = 0;
}

void zombieWeapon::move(gameObject source, gameObject target)
{
	calRotation(target.px, target.py);
	setPosition(source.px, source.py);
	setRenderPosition(px, py);
	isFlipped = px < target.px;
}

bool zombieWeapon::attack(player& target)
{
	currentState = zombieWeaponState::ATTACK;

	attackTimer += deltaTimer.getDeltaTime();
	if (attackTimer > attackSpeed)
	{
		attackTimer = 0;
		return true;
	}
	return false;
}

void zombieWeapon::hurt()
{
	health -= myPlayer.myWeapon[myPlayer.currentWeapon].getDamage();
}

void zombieWeapon::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void zombieWeapon::render(SDL_Rect& camera, bool isAlive)
{
	if (isAlive)
	{
	currentTexture->render(rx - camera.x, ry - camera.y, size, size, 
		currentClip, rotation, NULL, isFlipped == true ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
	}
}


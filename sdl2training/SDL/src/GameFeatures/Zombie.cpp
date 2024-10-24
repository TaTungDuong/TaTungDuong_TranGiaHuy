#include "Include/Zombie.h"

zombie::zombie()
{
	vx = 0;
	vy = 0;

	size = SCREEN_HEIGHT / 7;
	type = 0;
	attackTimer = 0;
}

void zombie::init()
{
	isActive = 1;
	//set random position
	bool ok = false;
	int randomX = 0;
	int randomY = 0;

	//set spawn zones
	int minX, maxX;
	int minY, maxY;

	((1950 <= px && px <= 3500) && (9700 <= py && py <= 10900)) ||
		((1350 <= px && px <= 4100) && (6900 <= py && py <= 8100));
	if ((1950 <= myPlayer.px && myPlayer.px <= 3500) && (9700 <= myPlayer.py && myPlayer.py <= 10900))
	{
		minX = 2040;
		maxX = 3400;
		minY = 9760;
		maxY = 10765;
	}
	if ((1350 <= myPlayer.px && myPlayer.px <= 4100) && (6900 <= myPlayer.py && myPlayer.py <= 8100))
	{
		minX = 1450;
		maxX = 4000;
		minY = 7025;
		maxY = 8000;
	}

	while (!ok)
	{
		//randomX = GetRandomInt(size, LEVEL_WIDTH - size, 1);
		//randomY = GetRandomInt(size, LEVEL_HEIGHT - size, 1);
		randomX = GetRandomInt(minX, maxX, 1);
		randomY = GetRandomInt(minY, maxY, 1);
		setPosition(randomX, randomY);
		if (calDistance(myPlayer) > SCREEN_WIDTH / 3) //to avoid zombie spawning within the camera view
		{
			ok = true;
		}
	}
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
}

void zombie::move(gameObject target)
{
	calRotation(target.px, target.py);

	if (calDistance(myPlayer) < attackRange + myPlayer.size || health <= 0)
	{
		return;
	}

	currentState = zombieState::WALK;
	float dirX = 0;
	float dirY = 0;

	int ratio = 2.0f;
	dirX = -cos(rotation * M_PI / 180.0);
	dirY = -sin(rotation * M_PI / 180.0);
	vx = dirX * speed * deltaTimer.getDeltaTime() / ratio * isActive;
	vy = dirY * speed * deltaTimer.getDeltaTime() / ratio * isActive;

	px += vx;
	py += vy;

	setRenderPosition(px, py);
	isFlipped = px < target.px;
}

bool zombie::attack(player& target)
{
	if (health <= 0) return false;

	currentState = zombieState::ATTACK;

	attackTimer += deltaTimer.getDeltaTime();
	if (attackTimer > attackSpeed)
	{
		attackTimer = 0;
		target.health -= damage;
		return true;
	}
	return false;
}

void zombie::hurt()
{
	health -= myPlayer.myWeapon[myPlayer.currentWeapon].getDamage();
	if (health <= 0 && currentState != zombieState::DEAD)
	{
		currentState = zombieState::DEAD;
		currentFrame = 0;
	}
}

void zombie::drop()
{

}

void zombie::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void zombie::render(SDL_Rect& camera)
{
	currentTexture->render(rx - camera.x, ry - camera.y, size, size,
		currentClip, 0, NULL, isFlipped == false ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
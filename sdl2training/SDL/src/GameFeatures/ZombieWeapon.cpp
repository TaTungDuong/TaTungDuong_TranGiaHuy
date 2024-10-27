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
	type = source.type;
	switch (type)
	{
	case 0:
		attackRange = NORMAL_ZOMBIE_ATTACK_RANGE;
		break;
	case 1:
		attackRange = TANK_ZOMBIE_ATTACK_RANGE;
		break;
	case 2:
		attackRange = FAST_ZOMBIE_ATTACK_RANGE;
		break;
	}
}

void zombieWeapon::move(gameObject source, gameObject target)
{
	calRotation(target.px, target.py);
	setPosition(source.px, source.py);
	setRenderPosition(px, py);
	isFlipped = px < target.px;
}

#pragma region Zombie Attack
bool zombieWeapon::attack(
	player& target, 
	gameObject source, 
	std::vector<zombieBullet>& zombieBullets,
	bool isAlive
)
{
	if (!isAlive) return false;
	if (source.calDistance(myPlayer) > attackRange * 15.0f + myPlayer.size) return false;

	currentState = zombieWeaponState::ATTACK;

	attackTimer += deltaTimer.getDeltaTime();
	if (attackTimer > attackSpeed)
	{
		switch (type)
		{
		case 0:
			attackType0(
				target,
				source,
				zombieBullets
			);
			break;
		case 1:
			attackType1(
				target,
				source,
				zombieBullets
			);
			break;
		case 2:
			attackType2(
				target,
				source,
				zombieBullets
			);
			break;
		default:
			break;
		}
		attackTimer = 0;
		return true;
	}
	return false;
}
void zombieWeapon::attackType0(//zombie bullet type 0
	player& target,
	gameObject source,
	std::vector<zombieBullet>& zombieBullets
)
{
	int threshold = 2;
	float fixed_angle = 15;
	for (int i = -threshold; i <= threshold; i++)
	{
		zombieBullet myZombieBullet(camera, source);
		myZombieBullet.rotation += fixed_angle * float(i); //fix bullet rotation
		float dirX = 0;
		float dirY = 0;

		dirX = cos(myZombieBullet.rotation * M_PI / 180.0);
		dirY = sin(myZombieBullet.rotation * M_PI / 180.0);

		myZombieBullet.vx = dirX * myZombieBullet.speed;
		myZombieBullet.vy = dirY * myZombieBullet.speed;

		zombieBullets.push_back(myZombieBullet);
	}
}
void zombieWeapon::attackType1(//zombie bullet type 1
	player& target,
	gameObject source,
	std::vector<zombieBullet>& zombieBullets
)
{
	zombieBullet myZombieBullet(camera, source);
	zombieBullets.push_back(myZombieBullet);
}
void zombieWeapon::attackType2(//zombie bullet type 2
	player& target,
	gameObject source,
	std::vector<zombieBullet>& zombieBullets
)
{
	float fixed_angle = 45;
	for (int i = 0; i <= 7; i++)
	{
		zombieBullet myZombieBullet(camera, source);
		myZombieBullet.rotation += fixed_angle * float(i); //fix bullet rotation
		float dirX = 0;
		float dirY = 0;

		dirX = cos(myZombieBullet.rotation * M_PI / 180.0);
		dirY = sin(myZombieBullet.rotation * M_PI / 180.0);

		myZombieBullet.vx = dirX * myZombieBullet.speed;
		myZombieBullet.vy = dirY * myZombieBullet.speed;

		zombieBullets.push_back(myZombieBullet);
	}
}
#pragma endregion

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

#pragma region zombieBullets
zombieBullet::zombieBullet(SDL_Rect& camera, gameObject source)
{
	type = source.type;
	lifeTime = 0.0f;
	switch (type)
	{
	case 0:
		size = 32;
		max_lifeTime = 10;
		damage = NORMAL_ZOMBIE_DAMAGE;
		break;
	case 1:
		size = 28;
		max_lifeTime = 5;
		damage = FAST_ZOMBIE_DAMAGE;
		break;
	case 2:
		size = 48;
		max_lifeTime = 10;
		damage = TANK_ZOMBIE_DAMAGE;
		break;
	case 3:
		size = 20;
		max_lifeTime = 10;
		damage = FAST_ZOMBIE_DAMAGE / 2.0f;
		break;
	case 4:
		size = 32;
		max_lifeTime = 10;
		damage = NORMAL_ZOMBIE_DAMAGE / 2.0f;
		break;
	default:
		size = 20;
		max_lifeTime = 10;
		damage = FAST_ZOMBIE_DAMAGE / 2.0f;
		break;
	}

	//	printf("Rotation: %f\n", source.rotation);

		//set fire rotation
	float offsetX = 20;
	float offsetY;
	if (0 < source.rotation && source.rotation <= 90)
	{
		offsetX *= -1;
		offsetY = 20;
		double theta = source.rotation * (M_PI / 180);
		px = int(source.px) - (offsetX * cos(theta) + offsetY * sin(theta));
		py = int(source.py) - (offsetX * sin(theta) + offsetY * cos(theta));

	}
	if (90 < source.rotation && source.rotation <= 180)
	{
		offsetX *= 1;
		offsetY = 20;
		double theta = source.rotation * (M_PI / 180);
		px = int(source.px) + (offsetX * cos(theta) - offsetY * sin(theta));
		py = int(source.py) + (offsetX * sin(theta) + offsetY * cos(theta));

	}
	if (180 < source.rotation && source.rotation <= 270)
	{
		offsetX *= -1;
		offsetY = -20;
		double theta = source.rotation * (M_PI / 180);
		px = int(source.px) - (offsetX * cos(theta) + offsetY * sin(theta));
		py = int(source.py) - (offsetX * sin(theta) + offsetY * cos(theta));

	}
	if (270 < source.rotation && source.rotation <= 360)
	{
		offsetX *= 1;
		offsetY = -20;
		double theta = source.rotation * (M_PI / 180);
		px = int(source.px) + (offsetX * cos(theta) - offsetY * sin(theta));
		py = int(source.py) + (offsetX * sin(theta) + offsetY * cos(theta));

	}
	setRenderPosition(px, py);
	speed = BULLET_SPEED * deltaTimer.getDeltaTime() / 7.5f;

	rotation = source.rotation + 180; //set bullet rotation
	float dirX = 0;
	float dirY = 0;

	dirX = cos(rotation * M_PI / 180.0);
	dirY = sin(rotation * M_PI / 180.0);

	vx = dirX * speed;
	vy = dirY * speed;
}

//calculate zombie bullet motions
void zombieBullet::updateBullet()
{
	lifeTime += deltaTimer.getDeltaTime();
	switch (type)
	{
	case 0:
		updateType0();
		break;
	case 1:
		updateType1();
		break;
	case 2:
		updateType2();
		break;
	case 3:
		updateType0();
		break;
	case 4:
		updateType0();
		break;
	default:
		break;
	}

}
void zombieBullet::updateType0()//zombie bullet  type 0
{
	px += vx;
	py += vy;
}
void zombieBullet::updateType1()//zombie bullet  type 1
{
	calRotation(myPlayer.px, myPlayer.py);
	float dirX = 0;
	float dirY = 0;

	float ratio = 0.8f;
	dirX = -cos(rotation * M_PI / 180.0);
	dirY = -sin(rotation * M_PI / 180.0);
	vx = dirX * speed * ratio;
	vy = dirY * speed * ratio;

	px += vx;
	py += vy;

	setRenderPosition(px, py);
}
void zombieBullet::updateType2()//zombie bullet  type 2
{
	px += vx;
	py += vy;
}
#pragma endregion




















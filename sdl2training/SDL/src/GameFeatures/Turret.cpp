#pragma once
#include "Include/Turret.h"

turret::turret()
{
	vx = 0.0f;
	vy = 0.0f;
	health = 100;
}
void turret::initTurret(gameObject& source)
{
	type = 3;
	health = 100;
	vx = 0.0f;
	vy = 0.0f;
	init(LEVEL_WIDTH * 2, LEVEL_HEIGHT * 2, source.size / 2, 0);
	speed = BULLET_SPEED / ratio;
	attackTimer = 0.0f;
	attackSpeed = 0.25f;
	currentFrame = 0;
	currentTotalFrame = 0;
	entranceTimeCounter = entranceTimeInterval;
	lifeTimeCounter = lifeTimeCounter;
}

void turret::move()
{
	lifeTimeCounter += deltaTimer.getDeltaTime();
	entranceTimeCounter += deltaTimer.getDeltaTime();

	isReady = (entranceTimeCounter >= entranceTimeInterval);

	if (lifeTimeCounter < lifeTimeInterval)
	{
		if (!isReady)
		{
			float dirX = 0;
			float dirY = 0;

			int ratio = 2.0f;
			dirX = -cos(90 * M_PI / 180.0 + M_PI);
			dirY = -sin(90 * M_PI / 180.0 + M_PI);
			vx = dirX * speed * deltaTimer.getDeltaTime() / ratio;
			vy = dirY * speed * deltaTimer.getDeltaTime() / ratio;

			px += vx;
			py += vy;
		}
	}
	else
	{
		float dirX = 0;
		float dirY = 0;

		int ratio = 2.0f;
		dirX = -cos(90 * M_PI / 180.0 + M_PI);
		dirY = -sin(90 * M_PI / 180.0 + M_PI);
		vx = dirX * speed * deltaTimer.getDeltaTime() / ratio;
		vy = dirY * speed * deltaTimer.getDeltaTime() / ratio;

		px -= vx;
		py -= vy;
	}

	setRenderPosition(px, py);
}

void turret::calPosition(player& myPlayer, float distance)
{
	px = myPlayer.px + distance;
	py = myPlayer.py + distance - SCREEN_HEIGHT / 2;
}

void turret::attack(//zombie bullet type 2
	player& target,
	gameObject source,
	std::vector<zombieBullet>& zombieBullets
)
{
	if (!isReady || lifeTimeCounter >= lifeTimeInterval) return;

	attackTimer += deltaTimer.getDeltaTime();
	if (attackTimer < attackSpeed) return;
	attackTimer = 0.0f;

	float fixed_angle = 90;
	for (int i = 0; i < 4; i++)
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

void turret::hurt(player& myPlayer)
{
	health -= myPlayer.myWeapon[myPlayer.currentWeapon].getDamage();
}

void turret::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void turret::render(SDL_Rect& camera)
{
	currentTexture->render(rx - camera.x, ry - camera.y, size, size,
		currentClip, 0, NULL, SDL_FLIP_NONE);
}



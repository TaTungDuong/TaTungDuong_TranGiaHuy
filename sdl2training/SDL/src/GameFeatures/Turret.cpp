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
	attackSpeed = 0.15f;
	currentFrame = 0;
	currentTotalFrame = 0;
	entranceTimeCounter = entranceTimeInterval;
	lifeTimeCounter = lifeTimeCounter;
}

void turret::move()
{
	lifeTimeCounter += deltaTimer.getDeltaTime();
	entranceTimeCounter += deltaTimer.getDeltaTime();

	isReady = (entranceTimeCounter >= entranceTimeInterval+ lagTimeInterval);

	if (lifeTimeCounter < lifeTimeInterval)
	{
		if (entranceTimeCounter < entranceTimeInterval)
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

bool turret::attack()
{
	if (!isReady || lifeTimeCounter >= lifeTimeInterval) return false;

	attackTimer += deltaTimer.getDeltaTime();
	if (attackTimer < attackSpeed) return false;
	attackTimer = 0.0f;
	return true;
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



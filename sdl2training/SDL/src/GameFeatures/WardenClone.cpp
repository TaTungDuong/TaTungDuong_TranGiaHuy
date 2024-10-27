#pragma once
#include "Include/WardenClone.h"

wardenClone::wardenClone()
{
	vx = 0.0f;
	vy = 0.0f;
	health = 100;
}
void wardenClone::initWardenClone(player& myPlayer, wardenCloneState state)
{
	currentState = state;
	health = 100;
	vx = 0.0f;
	vy = 0.0f;
	isActive = 0;
	init(LEVEL_WIDTH * 2, LEVEL_HEIGHT * 2, 192 / 2, 0);
	speed = PLAYER_SPEED * ratio;
	currentFrame = 0;
	currentTotalFrame = 0;
	entranceTimeCounter = entranceTimeInterval;
	lifeTimeCounter = lifeTimeCounter;
	moveTimeCounter = moveTimeInterval;
}

void wardenClone::move(player& myPlayer)
{
	if (lifeTimeCounter >= lifeTimeInterval)
	{
		px = LEVEL_WIDTH * 2;
		py = LEVEL_HEIGHT * 2;
	}
	else if (entranceTimeCounter < entranceTimeInterval)
	{
		entranceTimeCounter += deltaTimer.getDeltaTime();
		calRotation(ex, ey);

		float dirX = 0;
		float dirY = 0;

		int ratio = 1.0f;
		dirX = -cos(rotation * M_PI / 180.0);
		dirY = -sin(rotation * M_PI / 180.0);
		vx = dirX * speed * deltaTimer.getDeltaTime() / ratio * isActive;
		vy = dirY * speed * deltaTimer.getDeltaTime() / ratio * isActive;

		px += vx;
		py += vy;
	}
	else
	{
		moveTimeCounter += deltaTimer.getDeltaTime();
		if (moveTimeCounter >= moveTimeInterval)
		{
			if (currentState == wardenCloneState::REAL)
			{
				calRotation(int(myPlayer.px), int(myPlayer.py));
			}
			else
			{
				//store current position
				int nextX = px;
				int nextY = py;

				if (myPlayer.px > px)
				{
					nextX = GetRandomInt(int(myPlayer.px) + size, LEVEL_WIDTH + size, 1);
				}
				else
				{
					nextX = GetRandomInt(size, int(myPlayer.px) + size, 1);
				}

				if (myPlayer.py > py)
				{
					nextY = GetRandomInt(int(myPlayer.py + size), LEVEL_HEIGHT + size, 1);
				}
				else
				{
					nextY = GetRandomInt(size, int(myPlayer.py) + size, 1);
				}

				//calculate rotation to next position
				calRotation(nextX, nextY);
			}
			moveTimeCounter = 0.0f;
		}

		float dirX = 0;
		float dirY = 0;

		int ratio = 1.5f;
		dirX = -cos(rotation * M_PI / 180.0);
		dirY = -sin(rotation * M_PI / 180.0);

		float minRandomValue = 0.0f;
		float maxRandomValue = 5.0f;
		float RandomStep = 0.5f;
		vx = dirX * speed * deltaTimer.getDeltaTime() / ratio * isActive;
		vy = dirY * speed * deltaTimer.getDeltaTime() / ratio * isActive;

		px += vx;
		py += vy;
	}

	setPosition(px, py);
	setRenderPosition(px, py);
}

void wardenClone::calPosition(player& myPlayer, gameObject source)
{
	//set random position
	bool ok = false;
	int randomX = 0;
	int randomY = 0;

	while (!ok)
	{
		randomX = GetRandomInt(size, LEVEL_WIDTH - size, 1);
		randomY = GetRandomInt(size, LEVEL_HEIGHT - size, 1);
		setPosition(randomX, randomY);
		if (calDistance(myPlayer) > SCREEN_WIDTH) //to avoid clone spawning within the camera view
		{
			ok = true;
		}
	}
	ex = randomX;
	ey = randomY;
	px = source.px;
	py = source.py;
	setPosition(px, py);
	setRenderPosition(int(px), int(py));
}

void wardenClone::hurt(player& myPlayer)
{
	health -= myPlayer.myWeapon[myPlayer.currentWeapon].getDamage();
}

void wardenClone::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void wardenClone::render(SDL_Rect& camera)
{
	currentTexture->render(rx - camera.x, ry - camera.y, size, size,
		currentClip, 0, NULL, SDL_FLIP_NONE);
}



/// <summary>
/// Emperor's Divide (Heavy Cannon)
/// Player summons a wall of soldiers which charge forward, knocking back and damaging enemies.
/// </summary>
#pragma once
#include "Include/EmperorDivide.h"
#include "SDL.h"

#pragma region Emperor_Divide
EmperorDivide::EmperorDivide()
{
	init(LEVEL_WIDTH * 2, LEVEL_HEIGHT * 2, PLAYER_SIZE, -1);
	speed = BULLET_SPEED / ratio;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	moveTimeCounter = 0.0f;
	entranceTimeCounter = 0.0f;
	lifeTimeCounter = 0.0f;
}

void EmperorDivide::initPlayer()
{
	init(LEVEL_WIDTH * 2, LEVEL_HEIGHT * 2, SCREEN_HEIGHT / 7, -1);
	speed = BULLET_SPEED / ratio;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	moveTimeCounter = 0.0f;
	entranceTimeCounter = 0.0f;
	lifeTimeCounter = 0.0f;
}

void EmperorDivide::move()
{
	lifeTimeCounter += deltaTimer.getDeltaTime();
	entranceTimeCounter += deltaTimer.getDeltaTime();

	isReady = entranceTimeCounter >= entranceTimeInterval;

	if (isReady)
	{
		moveTimeCounter += deltaTimer.getDeltaTime();
		isActive = moveTimeCounter < moveTimeInterval;
		if (isActive)
		{
			float dirX = 0;
			float dirY = 0;

			int ratio = 2.0f;
			dirX = -cos(rotation * M_PI / 180.0 + M_PI);
			dirY = -sin(rotation * M_PI / 180.0 + M_PI);
			vx = dirX * speed * deltaTimer.getDeltaTime() / ratio;
			vy = dirY * speed * deltaTimer.getDeltaTime() / ratio;

			px += vx;
			py += vy;
		}
	}
	else
	{
		isActive = false;

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
	setRenderPosition(px, py);
}

void EmperorDivide::calPosition(player& myPlayer, float distance)
{
	float angleInRadians = (rotation + 90) * (M_PI / 180);

	px = myPlayer.px + distance * cos(angleInRadians);
	py = myPlayer.py + distance * sin(angleInRadians) - SCREEN_HEIGHT / 2;
}

void EmperorDivide::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void EmperorDivide::render(SDL_Rect& camera)
{
	currentTexture->render(rx - camera.x, ry - camera.y, size, size,
		currentClip, 0, NULL, isFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
#pragma endregion

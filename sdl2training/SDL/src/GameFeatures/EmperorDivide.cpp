/// <summary>
/// Emperor's Divide (Heavy Cannon)
/// Player summons a wall of soldiers which charge forward, knocking back and damaging enemies.
/// </summary>
#pragma once
#include "Include/EmperorDivide.h"
#include "SDL.h"

#pragma region Emperor_Divide
emperorDivide::emperorDivide()
{
	init(LEVEL_WIDTH * 2, LEVEL_HEIGHT * 2, PLAYER_SIZE, -1);
	speed = BULLET_SPEED / ratio;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	moveTimeCounter = 0.0f;
	lifeTimeCounter = 0.0f;
}

void emperorDivide::initPlayer()
{
	init(LEVEL_WIDTH * 2, LEVEL_HEIGHT * 2, SCREEN_HEIGHT / 7, -1);
	speed = BULLET_SPEED / ratio;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	moveTimeCounter = 0.0f;
	lifeTimeCounter = 0.0f;
}

void emperorDivide::move()
{
	lifeTimeCounter += deltaTimer.getDeltaTime();
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
	setRenderPosition(px, py);
}

void emperorDivide::calRotation(SDL_Rect& camera, int x, int y)
{
	int deltaX;
	int deltaY;
	//If player reached the edge of the level
	if (camera.x <= 0 || camera.y <= 0 || camera.x >= LEVEL_WIDTH - camera.w || camera.y >= LEVEL_HEIGHT - camera.h)
	{
		deltaX = px - camera.x - x;
		deltaY = py - camera.y - y;
	}
	else
	{
		deltaX = (SCREEN_WIDTH / 2 - size / 2) - x;
		deltaY = (SCREEN_HEIGHT / 2 - size / 2) - y;
	}

	rotation = 180 + (atan2(deltaY, deltaX) * 180.0000) / M_PI;
}

void emperorDivide::calPosition(player& myPlayer, float distance)
{
	float angleInRadians = (rotation + 90) * (M_PI / 180);

	px = myPlayer.px + distance * cos(angleInRadians);
	py = myPlayer.py + distance * sin(angleInRadians);
}

void emperorDivide::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void emperorDivide::render(SDL_Rect& camera)
{
	currentTexture->render(rx - camera.x, ry - camera.y, size, size,
		currentClip, 0, NULL, isFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
#pragma endregion

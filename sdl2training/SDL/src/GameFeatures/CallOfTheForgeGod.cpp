/// <summary>
/// Call Of The Forge God (Chaingun)
/// Player summons a massive elemental at a location which travels toward him with increasing speed. 
/// Enemies run over by the elemental take damage, are slowed and are made Brittle. 
/// Player can recast the ability to charge into the elemental, 
/// redirecting it in the direction he hits it, 
/// causing the elemental to affect any enemies it runs over to be knocked up, 
/// dealing the same damage and re-applying Brittle.
/// </summary>
#pragma once
#include "Include/CallOfTheForgeGod.h"
#include "SDL.h"

#pragma region Call_Of_The_Forge_God
callOfTheForgeGod::callOfTheForgeGod()
{
	init(LEVEL_WIDTH * 2, LEVEL_HEIGHT * 2, PLAYER_SIZE * ratioScale, -1);
	speed = PLAYER_SPEED * ratioSpeed;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	moveTimeCounter = 0.0f;
	lifeTimeCounter = 0.0f;
}
void callOfTheForgeGod::initPlayer()
{
	init(LEVEL_WIDTH * 2, LEVEL_HEIGHT * 2, PLAYER_SIZE * ratioScale, -1);
	speed == PLAYER_SPEED * ratioSpeed;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	moveTimeCounter = 0.0f;
	lifeTimeCounter = 0.0f;
}

void callOfTheForgeGod::move(player& myPlayer)
{
	if (isRecasted == false)
	{
		if (calDistance(myPlayer) <= PLAYER_SIZE && px <= myPlayer.px)
		{
			isRecasted = true;
			rotation = myPlayer.rotation;
			int mouseX, mouseY;
			// Get mouse position
			SDL_GetMouseState(&mouseX, &mouseY);
			if (isFlipped)
			{
				isFlipped = !(mouseX * 2 >= SCREEN_WIDTH);
			}
			else
			{
				isFlipped = !(mouseX * 2 <= SCREEN_WIDTH);
			}
		}
	}

	if (calDistance(myPlayer) <= SCREEN_WIDTH)
	{
		float dirX = 0;
		float dirY = 0;

		float direction = (isRecasted ? 1.0f : -1.0f);

		int ratio = 2.0f;
		dirX = cos(rotation * M_PI / 180.0) * direction;
		dirY = sin(rotation * M_PI / 180.0) * direction;
		vx = dirX * speed * deltaTimer.getDeltaTime() / ratio;
		vy = dirY * speed * deltaTimer.getDeltaTime() / ratio;

		px += vx;
		py += vy;
	}
	else
	{
		myPlayer.isActive = 1;
		px = LEVEL_SIZE * 2;
		py = LEVEL_SIZE * 2;
	}
	setRenderPosition(px, py);
}

void callOfTheForgeGod::calRotation(SDL_Rect& camera, int x, int y)
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

void callOfTheForgeGod::calPosition(player& myPlayer)
{
	float angleInRadians = (rotation) * (M_PI / 180);

	px = myPlayer.px + distance * cos(angleInRadians);
	py = myPlayer.py + distance * sin(angleInRadians);
}

void callOfTheForgeGod::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void callOfTheForgeGod::render(SDL_Rect& camera)
{
	currentTexture->render(rx - camera.x, ry - camera.y, 404, 160,
		currentClip, 0, NULL, isFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
#pragma endregion
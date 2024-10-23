#pragma once
/// <summary>
/// Dominus (Pistol)
/// Player transforms into the Tyrant form, gaining bonus Health and dealing damage to enemies around him. 
/// While in this form, Player gains Fury periodically.
/// </summary>
#pragma once
#include "Include/Dominus.h"
#include "SDL.h"

#pragma region Dominus
Dominus::Dominus()
{
	init(LEVEL_WIDTH * 2, LEVEL_HEIGHT * 2, 256, -1);
	currentFrame = 0;
	currentTotalFrame = 0;
	lifeTimeCounter = 0.0f;
}
void Dominus::initPlayer()
{
	init(LEVEL_WIDTH * 2, LEVEL_HEIGHT * 2, 256, -1);
	currentFrame = 0;
	currentTotalFrame = 0;
	lifeTimeCounter = 0.0f;
}

void Dominus::move()
{
	lifeTimeCounter += deltaTimer.getDeltaTime();
	if (lifeTimeCounter >= lifeTimeInterval)
	{
		px = LEVEL_WIDTH * 2;
		py = LEVEL_WIDTH * 2;
	}
	setRenderPosition(px, py);
}

void Dominus::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void Dominus::render(SDL_Rect& camera)
{
	currentTexture->render(rx - camera.x, ry - camera.y, 512, 512,
		currentClip, 0, NULL, SDL_FLIP_NONE);
}
#pragma endregion
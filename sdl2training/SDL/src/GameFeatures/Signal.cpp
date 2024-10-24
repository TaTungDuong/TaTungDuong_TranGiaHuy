#pragma once
#include "Include/Signal.h"

signal::signal()
{
	currentState = signalState::INTRO;
	health = SIGNAL_HEALTH;
}
void signal::initSignal(gameObject& source)
{
	currentState = signalState::INTRO;
	health = SIGNAL_HEALTH;
	init(source.px, source.py, source.size / 2, 0);
}

void signal::hurt(player& myPlayer)
{
	if (currentState == signalState::DEAD || currentState == signalState::INTRO) return;
	health -= myPlayer.myWeapon[myPlayer.currentWeapon].getDamage();
	if (health <= 0)
	{
		currentState = signalState::DEAD;
		currentFrame = 0;
	}
	else
	{
		currentState = signalState::HURT;
		currentFrame = 0;
	}
}

void signal::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void signal::render(SDL_Rect& camera)
{
	currentTexture->render(rx - camera.x, ry - camera.y, size, size,
		currentClip, 0, NULL, SDL_FLIP_NONE);
}

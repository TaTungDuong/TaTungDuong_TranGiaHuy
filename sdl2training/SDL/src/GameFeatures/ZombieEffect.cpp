#pragma once
#include "Include/ZombieEffect.h"
#include "SDL.h"

zombieEffect::zombieEffect()
{
	vx = 0;
	vy = 0;

	size = SCREEN_HEIGHT / 7;
}

void zombieEffect::init(zombie& source)
{
	setPosition(source.px, source.py);
	setRenderPosition(px, py);
	speed = source.speed;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	currentState = zombieEffectState::IDLE;
	previousState = zombieEffectState::IDLE;

	gZombieEffectInterval[zombieEffectState::IDLE] = PLAYER_EFFECT_ANIMATION_TIME_INTERVAL;
	gZombieEffectTimeCounter[zombieEffectState::IDLE] = PLAYER_EFFECT_ANIMATION_TIME_INTERVAL;
	gZombieEffectInterval[zombieEffectState::STUNT] = PLAYER_EFFECT_ANIMATION_TIME_INTERVAL;
	gZombieEffectTimeCounter[zombieEffectState::STUNT] = PLAYER_EFFECT_ANIMATION_TIME_INTERVAL;
}
void zombieEffect::move(gameObject source, gameObject target)
{
	calRotation(target.px, target.py);
	setPosition(source.px, source.py);
	setRenderPosition(px, py);
	isFlipped = px < target.px;
}

void zombieEffect::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void zombieEffect::render(SDL_Rect& camera)
{
	bool isFlipped;
	int mouseX, mouseY;
	// Get mouse position
	SDL_GetMouseState(&mouseX, &mouseY);

	// If the mouse is to the left of the zombie, flip horizontally
	if (mouseX < SCREEN_WIDTH / 2) {
		isFlipped = true;
	}
	else {
		isFlipped = false;
	}

	if (currentState == zombieEffectState::IDLE) return;
	gZombieEffectTimeCounter[currentState] += deltaTimer.getDeltaTime();
	if (gZombieEffectTimeCounter[currentState] < gZombieEffectInterval[currentState])
	{
		currentTexture->render(rx - camera.x, ry - camera.y - 16, size, size,
			currentClip, 0, NULL, isFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	}
}

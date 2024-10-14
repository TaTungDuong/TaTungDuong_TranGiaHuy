#include "Include/PlayerAnimation.h"
#include "SDL.h"

playerAnimation::playerAnimation()
{
	init(LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2, PLAYER_SIZE, -1);
	speed = PLAYER_SPEED;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	currentState = playerAnimationState::IDLE;
	previousState = playerAnimationState::IDLE;
}

void playerAnimation::initPlayer()
{
	init(LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2, SCREEN_HEIGHT / 7, -1);
	speed = PLAYER_SPEED;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	currentState = playerAnimationState::IDLE;
	previousState = playerAnimationState::IDLE;
}

void playerAnimation::calRotation(SDL_Rect& camera, int x, int y)
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


void playerAnimation::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void playerAnimation::render(SDL_Rect& camera)
{
	bool isFlipped;
	int mouseX, mouseY;
	// Get mouse position
	SDL_GetMouseState(&mouseX, &mouseY);

	// If the mouse is to the left of the player, flip horizontally
	if (mouseX < SCREEN_WIDTH / 2) {
		isFlipped = true;
	}
	else {
		isFlipped = false;
	}
	currentTexture->render(rx - camera.x, ry - camera.y - 16, size, size, currentClip, 0, NULL, isFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

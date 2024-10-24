#include "Include/Player.h"
#include "SDL.h"
player::player()
{
	init(PLAYER_START_X, PLAYER_START_Y, PLAYER_SIZE, -1);
	speed = PLAYER_SPEED;
	health = 100;
	skill = SCREEN_WIDTH / 5.0f;
	isActive = 1;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	currentWeapon = 0;
	currentState = playerState::IDLE;
	previousState = playerState::IDLE;
	for (int i = 0; i < PLAYER_WEAPON_SLOT; i++)
	{
		myWeapon[i].init("temp", 0, 0, 0, 0, 0);
	}
}

void player::initPlayer()
{
	init(PLAYER_START_X, PLAYER_START_Y, SCREEN_HEIGHT / 7, -1);
	speed = PLAYER_SPEED;
	isActive = 1;
	health = 100;
	vx = 0;
	vy = 0;
	currentFrame = 0;
	currentTotalFrame = 0;
	currentWeapon = 0;
	currentState = playerState::IDLE;
	previousState = playerState::IDLE;
}

void player::calRotation(SDL_Rect& camera, int x, int y)
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

void player::cycleWeapon()
{
	myWeapon[currentWeapon].stopReload();
	currentWeapon++;
	if (currentWeapon >= PLAYER_WEAPON_SLOT)
	{
		currentWeapon = 0;
	}
}

void player::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void player::render(SDL_Rect& camera)
{
	bool isFlipped;
	int mouseX, mouseY;
	// Get mouse position
	SDL_GetMouseState(&mouseX, &mouseY);

	// If the mouse is to the left of the player, flip horizontally
	if ((0 < rotation && rotation < 90)||(270 < rotation && rotation < 360)) {
		isFlipped = false;
	}
	else {
		isFlipped = true;
	}
	currentTexture->render(rx - camera.x, ry - camera.y, size, size, currentClip, rotation, NULL, isFlipped? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
}

bool player::checkWeapon()
{
	return myWeapon[currentWeapon].checkRateOfFire() &&
		myWeapon[currentWeapon].checkAmmo() &&
		!myWeapon[currentWeapon].checkReload() &&
		isActive;
}
bullet player::attack(SDL_Rect& camera, player& myPlayer)
{
	Sound::GetInstance()->playGunshot();
	currentState = playerState::FIRE;
	currentFrame = 0;
	//	myWeapon[currentWeapon].ammo--;

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	bullet myBullet;
	//set rotatio for bullet based on weapon
	myBullet.rotation = rotation;
	switch (currentWeapon)
	{
	case 2:
		myBullet.rotation += GetRandomFloat(0.0f, 10.0f, 0.1f);
	default:
		break;
	}
	myBullet.initBullet(camera, myPlayer, mouseX, mouseY);

	return myBullet;
}

bool player::checkSpawnZone()
{
	return ((1950 <= px && px <= 3500) && (9700 <= py && py <= 10900)) ||
		((1350 <= px && px <= 4100) && (6900 <= py && py <= 8100));
}
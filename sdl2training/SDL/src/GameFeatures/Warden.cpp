#pragma once
#include "Include/Warden.h"

Warden::Warden()
{
	vx = 0;
	vy = 0;

	size = 256;
	type = 0;
	attackTimer = 0;
	speed = BOSS_WARDEN_SPEED;
	health = 100.0f;
}

void Warden::initWarden(player& myPlayer)
{
	health = 100.0f;
	isActive = 1;
	//set random position
	bool ok = false;
	int randomX = 0;
	int randomY = 0;

	while (!ok)
	{
		randomX = GetRandomInt(size, LEVEL_WIDTH - size, 1);
		randomY = GetRandomInt(size, LEVEL_HEIGHT - size, 1);
		setPosition(randomX, randomY);
		if (calDistance(myPlayer) > SCREEN_WIDTH) //to avoid Warden spawning within the camera view
		{
			ok = true;
		}
	}
	px = myPlayer.px + 512; py = myPlayer.py + 512;
	init(px, py, size, 0);
	setRenderPosition(px, py);
}

void Warden::move(player& myPlayer)
{
	if (health <= 0)
	{
		currentState = WardenState::DEAD;
		return;
	}

	calRotation(myPlayer.px, myPlayer.py);

	if (calDistance(myPlayer) < size / 4 + myPlayer.size)
	{
		currentState = WardenState::IDLE;
		return;
	}

	currentState = WardenState::WALK;
	float dirX = 0;
	float dirY = 0;

	int ratio = 2.0f;
	dirX = -cos(rotation * M_PI / 180.0);
	dirY = -sin(rotation * M_PI / 180.0);
	vx = dirX * speed * deltaTimer.getDeltaTime() / ratio * isActive;
	vy = dirY * speed * deltaTimer.getDeltaTime() / ratio * isActive;

	px += vx;
	py += vy;

	setRenderPosition(px, py);
	isFlipped = px < myPlayer.px;
}

bool Warden::attack(player& target)
{
	if (health <= 0) return false;

	attackTimer += deltaTimer.getDeltaTime();
	if (attackTimer > attackSpeed)
	{
		attackTimer = 0;
		target.health -= damage;
		return true;
	}
	return false;
}

void Warden::hurt(player& myPlayer)
{
	if (health > 0)
	{
		health -= myPlayer.myWeapon[myPlayer.currentWeapon].getDamage() * 100.0f / BOSS_WARDEN_HEALTH;
	}
	else
	{
		currentState = WardenState::DEAD;
	}
}

void Warden::setAnimation(LTexture& targetTexture, SDL_Rect& targetClip)
{
	currentTexture = &targetTexture;
	currentClip = &targetClip;
}

void Warden::render(SDL_Rect& camera)
{
	currentTexture->render(rx - camera.x - 32, ry - camera.y - 72, size, size,
		currentClip, 0, NULL, isFlipped == false ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
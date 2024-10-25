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
	currentState = WardenState::INTRO;
	currentFrame = 0;
	currentTotalFrame = BOSS_WARDEN_INTRO_ANIMATION_FRAMES;
	vx = 0;
	vy = 0;

	size = 256;
	type = 0;
	attackTimer = 0;
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

	//set stats
	attackSpeed = 5.0f;
	attackTimer = 0.0f;
	speed = BOSS_WARDEN_SPEED;
	health = 100.0f;
	isActive = 1;

	//set skill
	///dive
	diveCooldownCounter = 0.0f;
	canDive = false;
	//summon turret
	turretCooldownCounter = 0.0f;
	canTurret = false;
}

void Warden::move(player& myPlayer)
{
	if (currentState == WardenState::INTRO) return;
	if (health <= 0)
	{
		currentState = WardenState::DEAD;
		return;
	}

	calRotation(myPlayer.px, myPlayer.py);

	if (calDistance(myPlayer) < size / 4 + myPlayer.size)
	{
		if (currentState != WardenState::HURT && currentState != WardenState::DIVE && currentState != WardenState::HIDE)
		{
			currentState = WardenState::IDLE;
		}
		return;
	}

	if (currentState != WardenState::HURT && currentState != WardenState::DIVE && currentState != WardenState::HIDE)
	{
		currentState = WardenState::WALK;
	}
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

void Warden::hurt(float damage)
{
	if (canCollide() == false) return;
	if (health > 0)
	{
		currentState = WardenState::HURT;
		health -= damage * 100.0f / BOSS_WARDEN_HEALTH;
	}
	else
	{
		currentState = WardenState::DEAD;
	}
}

bool Warden::canCollide()
{
	return !(currentState == WardenState::INTRO || currentState == WardenState::DIVE
		|| currentState == WardenState::HIDE || currentState == WardenState::DEAD);
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

#pragma region Warden Attacks
bool Warden::attack(player& target, std::vector<turret>& turrets, std::vector<zombieBullet>& zombieBullets)
{
	if (currentState == WardenState::INTRO || currentState == WardenState::DEAD) return false;

	if (attackTimer >= attackSpeed)
	{
		attackTimer = 0;
		//return true;
	}
	if (diveCooldownCounter >= diveCooldownInterval)
	{
		initDive();
	}
	attackDive();

	if (turretCooldownCounter >= turretCooldownInterval)
	{
		initTurret(turrets);
	}
	attackTurret(turrets, zombieBullets);

	cooldown();
	return false;
}
void Warden::cooldown()
{
	attackTimer += deltaTimer.getDeltaTime();
	diveCooldownCounter += deltaTimer.getDeltaTime();
	turretCooldownCounter += deltaTimer.getDeltaTime();
}


//Dive
void Warden::initDive()
{
	if (canDive == false)
	{
		diveTimeCounter = 0;
		canDive = true;
	}
}
void Warden::attackDive()
{
	if (diveCooldownCounter < diveCooldownInterval || canDive == false) return;
	diveTimeCounter += deltaTimer.getDeltaTime();
	if (diveTimeCounter < diveTimeInterval)
	{
		if (currentState != WardenState::DIVE && currentState != WardenState::HIDE)
		{
			currentState = WardenState::DIVE;
			currentFrame = 0;
		}
	}
	else
	{
		currentState = WardenState::INTRO;
		currentFrame = 0;
		currentTotalFrame = BOSS_WARDEN_INTRO_ANIMATION_FRAMES;
		diveCooldownCounter = 0.0f;
		canDive = false;
	}
}

//Summon Turrets
void Warden::initTurret(std::vector<turret>& turrets)
{
	if (turrets.size() == 0) return;
	if (canTurret == false)
	{
		turretTimeCounter = 0;
		canTurret = true;

		int i = -number_of_turrets / 2;
		for (auto& tr : turrets)
		{
			tr.calPosition(myPlayer, 128 * i);
			i++;
			tr.lifeTimeCounter = 0.0f;
			tr.entranceTimeCounter = 0.0f;
			turretTimeInterval = tr.lifeTimeInterval;
		}
	}
}
void Warden::attackTurret(std::vector<turret>& turrets, std::vector<zombieBullet>& zombieBullets)
{
	if (turrets.size() == 0) return;
	if (turretCooldownCounter < turretCooldownInterval || canTurret == false) return;
	turretTimeCounter += deltaTimer.getDeltaTime();
	if (turretTimeCounter >= turretTimeInterval)
	{
		turretCooldownCounter = 0.0f;
		canTurret = false;
	}
	else
	{
		for (auto& tr : turrets)
		{
			tr.move();
			tr.attack(myPlayer, tr, zombieBullets);
			tr.updateRenderPosition();
			tr.render(camera);
		}
	}
}
#pragma endregion


#pragma region WardenBullets
WardenBullet::WardenBullet(SDL_Rect& camera, gameObject source)
{
	type = source.type;
	lifeTime = 0.0f;
	switch (type)
	{
	case 0:
		size = 32;
		max_lifeTime = 10;
		damage = NORMAL_ZOMBIE_DAMAGE;
		break;
	case 1:
		size = 28;
		max_lifeTime = 10;
		damage = FAST_ZOMBIE_DAMAGE;
		break;
	case 2:
		size = 48;
		max_lifeTime = 10;
		damage = TANK_ZOMBIE_DAMAGE;
		break;
	default:
		break;
	}

	//	printf("Rotation: %f\n", source.rotation);

		//set fire rotation
	float offsetX = 20;
	float offsetY;
	if (0 < source.rotation && source.rotation <= 90)
	{
		offsetX *= -1;
		offsetY = 20;
		double theta = source.rotation * (M_PI / 180);
		px = source.px - (offsetX * cos(theta) + offsetY * sin(theta));
		py = source.py - (offsetX * sin(theta) + offsetY * cos(theta));

	}
	if (90 < source.rotation && source.rotation <= 180)
	{
		offsetX *= 1;
		offsetY = 20;
		double theta = source.rotation * (M_PI / 180);
		px = source.px + (offsetX * cos(theta) - offsetY * sin(theta));
		py = source.py + (offsetX * sin(theta) + offsetY * cos(theta));

	}
	if (180 < source.rotation && source.rotation <= 270)
	{
		offsetX *= -1;
		offsetY = -20;
		double theta = source.rotation * (M_PI / 180);
		px = source.px - (offsetX * cos(theta) + offsetY * sin(theta));
		py = source.py - (offsetX * sin(theta) + offsetY * cos(theta));

	}
	if (270 < source.rotation && source.rotation <= 360)
	{
		offsetX *= 1;
		offsetY = -20;
		double theta = source.rotation * (M_PI / 180);
		px = source.px + (offsetX * cos(theta) - offsetY * sin(theta));
		py = source.py + (offsetX * sin(theta) + offsetY * cos(theta));

	}
	setRenderPosition(px, py);
	speed = BULLET_SPEED * deltaTimer.getDeltaTime() / 7.5f;

	rotation = source.rotation + 180; //set bullet rotation
	float dirX = 0;
	float dirY = 0;

	dirX = cos(rotation * M_PI / 180.0);
	dirY = sin(rotation * M_PI / 180.0);

	vx = dirX * speed;
	vy = dirY * speed;
}

//calculate Warden bullet motions
void WardenBullet::updateBullet(player& myPlayer)
{
	lifeTime += deltaTimer.getDeltaTime();
	switch (type)
	{
	case 0:
		updateType0(myPlayer);
		break;
	case 1:
		updateType1(myPlayer);
		break;
	case 2:
		updateType2(myPlayer);
		break;
	default:
		break;
	}

}
void WardenBullet::updateType0(player& myPlayer)//Warden bullet  type 0
{
	px += vx;
	py += vy;
}
void WardenBullet::updateType1(player& myPlayer)//Warden bullet  type 1
{
	calRotation(myPlayer.px, myPlayer.py);
	float dirX = 0;
	float dirY = 0;

	float ratio = 0.8f;
	dirX = -cos(rotation * M_PI / 180.0);
	dirY = -sin(rotation * M_PI / 180.0);
	vx = dirX * speed * ratio;
	vy = dirY * speed * ratio;

	px += vx;
	py += vy;

	setRenderPosition(px, py);
}
void WardenBullet::updateType2(player& myPlayer)//Warden bullet  type 2
{
	px += vx;
	py += vy;
}
#pragma endregion
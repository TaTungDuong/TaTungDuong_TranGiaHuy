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
	isReady = false;
	currentState = WardenState::INTRO;
	currentFrame = 0;
	currentTotalFrame = BOSS_WARDEN_INTRO_ANIMATION_FRAMES;
	vx = 0;
	vy = 0;

	size = 256;
	type = 0;
	attackTimer = 0;

	px = myPlayer.px + 512; py = myPlayer.py + 512;
	px = LEVEL_WIDTH / 2; py = LEVEL_HEIGHT / 2;
	init(px, py, size, 0);
	setRenderPosition(px, py);

	//set stats
	attackSpeed = 5.0f;
	attackTimer = 0.0f;
	speed = BOSS_WARDEN_SPEED;
	health = 100.0f;
	isActive = 1;

	//set skill
	///fire
	fireCooldownCounter = 0.0f;
	fireCooldownInterval = GetRandomFloat(minFireCooldownTimepoint, maxFireCooldownTimepoint, 0.5f);
	canFire = false;
	///dive
	diveCooldownCounter = 0.0f;
	diveCooldownInterval = GetRandomFloat(minDiveCooldownTimepoint, maxDiveCooldownTimepoint, 0.5f);
	canDive = false;
	///summon turret
	turretCooldownCounter = 0.0f;
	turretCooldownInterval = GetRandomFloat(minTurretCooldownTimepoint, maxTurretCooldownTimepoint, 0.5f);
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
	if (isReady == false)
	{
		isReady = true;
		myPlayer.isActive = true;
	}
	isReady = true;

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
bool Warden::attack(
	player& target,
	std::vector<wardenClone>& wardenClones,
	std::vector<turret>& turrets, 
	std::vector<zombieBullet>& zombieBullets
)
{
	if (currentState == WardenState::INTRO || currentState == WardenState::DEAD) return false;

	if (attackTimer >= attackSpeed)
	{
		attackTimer = 0;
		//return true;
	}
	
	//Fire
	if (fireCooldownCounter >= fireCooldownInterval)
	{
		initFire();
	}
	attackFire(zombieBullets);

	//Dive
	if (diveCooldownCounter >= diveCooldownInterval)
	{
		initDive(myPlayer, wardenClones);
	}
	attackDive(myPlayer, wardenClones);

	//Summon Turrets
	if (turretCooldownCounter >= turretCooldownInterval)
	{
		initTurret(target, turrets);
	}
	attackTurret(target, turrets, zombieBullets);

	cooldown();
	return false;
}
void Warden::cooldown()
{
	attackTimer += deltaTimer.getDeltaTime();
	fireCooldownCounter += deltaTimer.getDeltaTime();
	diveCooldownCounter += deltaTimer.getDeltaTime();
	turretCooldownCounter += deltaTimer.getDeltaTime();
}


//Fire
void Warden::initFire()
{
	//Warden only can fire when the current state is IDLE or WALK or HURT
	if (canFire == false 
		&& (currentState == WardenState::IDLE 
			|| currentState == WardenState::WALK 
			|| currentState == WardenState::HURT))
	{
		canFire = true;
		fireCounter = 0;
		fireTimeCounter = fireTimeInterval;
	}
}
void Warden::attackFire(std::vector<zombieBullet>& zombieBullets)
{
	if (fireCooldownCounter < fireCooldownInterval || canFire == false) return;
	//Warden only can fire when the current state is IDLE or WALK or HURT
	if (currentState != WardenState::IDLE 
		&& currentState != WardenState::WALK
		&& currentState != WardenState::HURT) return;
	//Warden can not fire anymore if it fire enough times
	if (fireCounter >= number_of_fires)
	{
		fireCooldownCounter = 0.0f;
		fireCooldownInterval = GetRandomFloat(minFireCooldownTimepoint, maxFireCooldownTimepoint, 0.5f);
		canFire = false;
		return;
	}

	fireTimeCounter += deltaTimer.getDeltaTime();
	if (fireTimeCounter >= fireTimeInterval)
	{
		fireTimeCounter = 0.0f;
		fireCounter++;
		//printf("Fire Counter: %d\n", fireCounter);
		gameObject temp;
		float fixed_angle = 30.0f;
		//left hand
		temp.init(px - 128, py - 8, 128, 0, -1);
		WardenBullet myWardenBulletLeft(camera, temp);
		for (int j = 0; j < 12; j++)
		{
			zombieBullet myZombieBullet(camera, myWardenBulletLeft);
			//set bullet position
			myZombieBullet.setPosition(int(myWardenBulletLeft.px), int(myWardenBulletLeft.py));
			myZombieBullet.setRenderPosition(myZombieBullet.px, myZombieBullet.py);

			//set bullet type
			myZombieBullet.type = int(myWardenBulletLeft.type);
			myZombieBullet.size = 32;

			//set bullet rotation
			myZombieBullet.rotation = fixed_angle * float(j); //fix bullet rotation

			float dirX = 0;
			float dirY = 0;

			dirX = cos(myZombieBullet.rotation * M_PI / 180.0);
			dirY = sin(myZombieBullet.rotation * M_PI / 180.0);

			myZombieBullet.vx = dirX * myZombieBullet.speed;
			myZombieBullet.vy = dirY * myZombieBullet.speed;

			zombieBullets.push_back(myZombieBullet);
		}
		//right hand
		temp.init(px + 128, py - 8, 128, 0, -1);
		WardenBullet myWardenBulletRight(camera, temp);
		for (int j = 0; j < 12; j++)
		{
			zombieBullet myZombieBullet(camera, myWardenBulletRight);
			//set bullet position
			myZombieBullet.setPosition(int(myWardenBulletRight.px), int(myWardenBulletRight.py));
			myZombieBullet.setRenderPosition(myZombieBullet.px, myZombieBullet.py);

			//set bullet type
			myZombieBullet.type = int(myWardenBulletRight.type);
			myZombieBullet.size = 32;

			//set bullet rotation
			myZombieBullet.rotation = fixed_angle * float(j); //fix bullet rotation

			float dirX = 0;
			float dirY = 0;

			dirX = cos(myZombieBullet.rotation * M_PI / 180.0);
			dirY = sin(myZombieBullet.rotation * M_PI / 180.0);

			myZombieBullet.vx = dirX * myZombieBullet.speed;
			myZombieBullet.vy = dirY * myZombieBullet.speed;

			zombieBullets.push_back(myZombieBullet);
		}
	}
}

//Dive
void Warden::initDive(player& myPlayer, std::vector<wardenClone>& wardenClones)
{
	if (canDive == false)
	{
		diveTimeCounter = 0;
		canDive = true;
	}
}
void Warden::attackDive(player& myPlayer, std::vector<wardenClone>& wardenClones)
{
	if (diveCooldownCounter < diveCooldownInterval || canDive == false) return;
//	diveTimeCounter += deltaTimer.getDeltaTime();
	if (diveTimeCounter < diveTimeInterval)
	{
		if (currentState != WardenState::DIVE && currentState != WardenState::HIDE)
		{
			currentState = WardenState::DIVE;
			currentFrame = 0;
			Sound::GetInstance()->playWardenDive(1);
		}
		else if (currentState == WardenState::DIVE && currentFrame == BOSS_WARDEN_DIVE_ANIMATION_FRAMES - 3)
		{
			for (auto& wc : wardenClones)
			{
				wc.lifeTimeCounter = 0.0f;
				wc.entranceTimeCounter = 0.0f;
				wc.health = 100.0f;
				gameObject temp;
				temp.init(px, py, 512, 0, -1);
				wc.calPosition(myPlayer, temp);
				wc.isActive = 1;
			}
		}
		else if (currentState == WardenState::HIDE)
		{
			for (auto wc : wardenClones)
			{
				if (wc.currentState == wardenCloneState::REAL && wc.health <= 0)
				{
					diveTimeCounter = diveTimeInterval;
					for (auto& wc2 : wardenClones)
					{
						wc2.lifeTimeCounter = wc2.lifeTimeInterval;
						wc2.isActive = 0;
					}
					return;
				}
			}
		}
	}
	else
	{
		currentState = WardenState::INTRO;
		currentFrame = 0;
		Sound::GetInstance()->playWardenDive(-1);
		currentTotalFrame = BOSS_WARDEN_INTRO_ANIMATION_FRAMES;
		diveCooldownCounter = 0.0f;
		diveCooldownInterval = GetRandomFloat(minDiveCooldownTimepoint, maxDiveCooldownTimepoint, 0.5f);
		canDive = false;
	}
}

//Summon Turrets
void Warden::initTurret(player& myPlayer, std::vector<turret>& turrets)
{
	if (turrets.size() == 0) return;
	if (canTurret == false)
	{
		turretTimeCounter = 0;
		canTurret = true;

		int i = -number_of_turrets / 2;
		for (int j = 0; j < turrets.size(); j++)
		{
			turrets[j].calPosition(myPlayer, 208 * i);
			i++;
			turrets[j].lifeTimeCounter = 0.0f;
			turrets[j].entranceTimeCounter = 0.0f;
			turretTimeInterval = turrets[j].lifeTimeInterval;
		}
	}
}
void Warden::attackTurret(player& myPlayer, std::vector<turret>& turrets, std::vector<zombieBullet>& zombieBullets)
{
	if (turrets.size() == 0) return;
	if (turretCooldownCounter < turretCooldownInterval || canTurret == false) return;
	turretTimeCounter += deltaTimer.getDeltaTime();
	if (turretTimeCounter >= turretTimeInterval)
	{
		turretCooldownCounter = 0.0f;
		turretCooldownInterval = GetRandomFloat(minTurretCooldownTimepoint, maxTurretCooldownTimepoint, 0.5f);
		canTurret = false;
	}
	else
	{
		for (int i = 0; i < turrets.size(); i++)
		{
			turrets[i].move();
			if (turrets[i].attack())
			{
				/*printf("Turret %d [type: %d, px: %d, py: %d] || player [px: %d, py: %d]\n", 
					i + 1, turrets[i].type, int(turrets[i].px), int(turrets[i].py), int(myPlayer.px), int(myPlayer.py));*/
				float fixed_angle = 90.0f;
				for (int j = 0; j < 4; j++)
				{
					zombieBullet myZombieBullet(camera, turrets[i]);
					//set bullet position
					myZombieBullet.setPosition(int(turrets[i].px), int(turrets[i].py));
					myZombieBullet.setRenderPosition(myZombieBullet.px, myZombieBullet.py);

					//set bullet type
					myZombieBullet.type = int(turrets[j].type);

					//set bullet rotation
					myZombieBullet.rotation = fixed_angle * float(j); //fix bullet rotation

					float dirX = 0;
					float dirY = 0;

					dirX = cos(myZombieBullet.rotation * M_PI / 180.0);
					dirY = sin(myZombieBullet.rotation * M_PI / 180.0);

					myZombieBullet.vx = dirX * myZombieBullet.speed;
					myZombieBullet.vy = dirY * myZombieBullet.speed;

					/*printf("Bullet Type: %d, [X: %d, Y: %d, Rotation: %f, vx: %f, vy: %f]\n",
						int(myZombieBullet.type), int(myZombieBullet.px), int(myZombieBullet.py), 
						myZombieBullet.rotation,
						myZombieBullet.vx, myZombieBullet.vy);*/

					zombieBullets.push_back(myZombieBullet);
				}
			}
			turrets[i].updateRenderPosition();
			turrets[i].render(camera);
		}
	}
}
#pragma endregion


#pragma region WardenBullets
WardenBullet::WardenBullet(SDL_Rect& camera, gameObject source)
{
	type = 4;
	setPosition(source.px, source.py);
	setRenderPosition(px, py);
}
#pragma endregion
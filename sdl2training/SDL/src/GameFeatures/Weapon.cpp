#include "Include/Weapon.h"

#pragma region bullets
void bullet::initBullet(SDL_Rect& camera, gameObject source, int targetX, int targetY)
{
	size = BULLET_SIZE;

	//set fire rotation
	float offsetX = -20;
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
	speed = BULLET_SPEED * deltaTimer.getDeltaTime();
/*	
	float screenX = calOnScreenXPosition(camera, px);
	float screenY = calOnScreenYPosition(camera, py);

	float tempX = targetX - screenX;
	float tempY = targetY - screenY;
*/
	float dirX = 0;
	float dirY = 0;

	dirX = cos(rotation * M_PI / 180.0);
	dirY = sin(rotation * M_PI / 180.0);

	vx = dirX * speed;
	vy = dirY * speed;
}



#pragma region weapons
weapon::weapon()
{
	name = "";
	damage = 0;
	rateOfFire = 0;
	ammo = 0;
	clipSize = 0;
	rateOfFireTimer = 0;
}

void weapon::init(std::string n, float d, float r, int a, int c, float t)
{
	name = n;
	damage = d;
	rateOfFire = r;
	ammo = a;
	clipSize = c;
	reloadTime = t;
	reloadFlag = false;
	rateOfFireTimer = 0;
	reloadTimer = 0;
}

std::string weapon::getName()
{
	return name;
}

int weapon::getDamage()
{
	return damage;
}

float weapon::getRateOfFire()
{
	return rateOfFire;
}

int weapon::getClipSize()
{
	return clipSize;
}

bool weapon::checkRateOfFire()
{
	rateOfFireTimer += deltaTimer.getDeltaTime();
	if (rateOfFireTimer > rateOfFire)
	{
		rateOfFireTimer = 0;
		return true;
	}
	else
	{
		return false;
	}
}

bool weapon::checkAmmo()
{
	if (ammo <= 0)
	{
		ammo = 0;
	}
	else
	{
		if (!reloadFlag)
		{
			return true;
		}
	}
	return false;
}

bool weapon::checkReload()
{
	if (reloadFlag)
	{
		if (reloadTimer <= 0)
		{
			reloadTimer = 0;
			reloadFlag = false;
			ammo = clipSize;
		}
		else
		{
			reloadTimer -= deltaTimer.getDeltaTime();
			//printf("reload timer = %f\n", reloadTimer);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool weapon::getReloadFlag()
{
	return reloadFlag;
}

void weapon::reload()
{
	if (!reloadFlag)
	{
		reloadFlag = true;
		reloadTimer = reloadTime;
	}

}

void weapon::stopReload()
{
	reloadFlag = false;
	reloadTimer = 0;
}

void weapon::resetTimer()
{
	rateOfFireTimer = rateOfFire;
}


void weapon::fire()
{

}

#include "BaseObject.h"

void BaseObject::init(float x, float y, int s, double r, int t) {
	size = s;
	setPosition(x, y);
	setRenderPosition(x, y);
	rotation = r;
	type = t;
}

void BaseObject::setPosition(float x, float y) {
	px = x;
	py = y;
}

void BaseObject::setRenderPosition(float x, float y) {
	rx = int(x - size / 2);
	ry = int(y - size / 2);
}

void BaseObject::updateRenderPosition() {
	rx = int(px - size / 2);
	ry = int(py - size / 2);
}

void BaseObject::calRotation(int x, int y) {
	int deltaX = px - x;
	int deltaY = py - y;

	rotation = (atan2(deltaY, deltaX) * 180.0000) / M_PI;
}

float BaseObject::calDistance(BaseObject target) {
	return sqrt(pow(target.px - px, 2) + pow(target.py - py, 2));
}

bool BaseObject::checkCollision(BaseObject target, float padding) {
	if (calDistance(target) < float(target.size / COLLIDER_TOLERANCE) + padding) {
		return true;
	}
	return false;
}

void BaseObject::resize(int s) {
	size = s;
}

void BaseObject::render(LTexture target)
{
	target.render(rx, ry, size, size, NULL, rotation);
}

void BaseObject::render(LTexture target, SDL_Rect& camera)
{
	target.render(rx - camera.x, ry - camera.y, size, size, NULL, rotation);
}

void renderBaseObject(SDL_Rect camera, LTexture& sourceTexture, std::vector<BaseObject>& vectorList)
{
	if (vectorList.size() > 0)
	{
		for (int i = 0; i < vectorList.size(); i++)
		{
			sourceTexture.render(camera, vectorList[i].rx, vectorList[i].ry, vectorList[i].size, vectorList[i].size, NULL, vectorList[i].rotation);
		}
	}
}

void renderBaseObject(SDL_Rect camera, LTexture& sourceTexture, std::vector<BaseObject>& vectorList, std::vector<SDL_Rect> clips)
{
	if (vectorList.size() > 0 && clips.size() > 0)
	{
		for (int i = 0; i < vectorList.size(); i++)
		{
			sourceTexture.render(camera, vectorList[i].rx, vectorList[i].ry, vectorList[i].size, vectorList[i].size, &clips[vectorList[i].type], vectorList[i].rotation);
		}
	}
}
#pragma once
#include "CMath.h"
#include <memory>
#include "SDL.h"

#include "TextureManager.h"
#include "Include/Graphics.h"

class BaseObject
{
protected:
	Vector3 m_position;
	Vector3 m_scale;
	double m_angle = 0.0; // default angle
	SDL_RendererFlip m_flip = SDL_FLIP_NONE;
	std::shared_ptr<TextureManager> m_pTexture;
public:
	BaseObject() : m_pTexture(nullptr), m_position(Vector3(0.0f, 0.0f, 0.0f)), m_scale(Vector3(1.0f, 1.0f, 1.0f)) {}
	BaseObject(std::shared_ptr<TextureManager> texture)
		:m_pTexture(texture), m_position(Vector3(0.0f, 0.0f, 0.0f)) , m_scale(Vector3(1.0f, 1.0f, 1.0f) ){}
//	virtual void Init() = 0;
//	virtual void Draw(SDL_Renderer* renderer, SDL_Rect *clip = NULL) = 0;
//	virtual void Update(float deltatime) = 0;
	void SetPosition(Vector3 position) { m_position = position; }
	Vector3 GetPosition() { return m_position; }
	void SetTexture(std::shared_ptr<TextureManager> texture) { m_pTexture = texture; }

	//size and angle
	int size;
	double rotation;

	//game object's center position
	float px;
	float py;

	//game object render offset (top left corner)
	int rx;
	int ry;

	int type;

	void init(float x, float y, int s, double r, int t = -1);
	void setPosition(float x, float y);
	void setRenderPosition(float x, float y);
	void updateRenderPosition();
	void calRotation(int x, int y);
	float calDistance(BaseObject target);
	bool checkCollision(BaseObject target, float padding = 0);
	void resize(int s);
	void render(LTexture target);
	void render(LTexture target, SDL_Rect& camera);

};

void renderGameObject(SDL_Rect camera, LTexture& sourceTexture, std::vector<BaseObject>& vectorList);
void renderGameObject(SDL_Rect camera, LTexture& sourceTexture, std::vector<BaseObject>& vectorList, std::vector<SDL_Rect> clips);
#pragma once
#include "SDL.h"
#include <string>
#include <memory>
#include "Sprite2D.h"
class TextureManager;

class Text : public Sprite2D
{
public:
	Text( std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	void		Init();
	void		Draw(SDL_Renderer* renderer, SDL_Rect *clip = NULL) ;
	void		Update(float deltatime) ;



};

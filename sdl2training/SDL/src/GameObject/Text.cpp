#include"Text.h"

#include "TextureManager.h"
Text::Text(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip) : Sprite2D(texture, flip)

	 
{
	
	m_position = Vector3(-1.0f, 1.0f, 1.0f);
	
	
}

void Text::Init()
{
}

void Text::Draw(SDL_Renderer* renderer, SDL_Rect* clip)
{
	if (m_pTexture != nullptr)
	{
		SDL_Rect dstRect = { m_position.x  ,m_position.y , m_iWidth, m_iHeight };
		if (clip != NULL)
		{
			dstRect.w = clip->w;
			dstRect.h = clip->h;
		}
		SDL_RenderCopy(Renderer::GetInstance()->GetRenderer(), m_pTexture->GetTextureObj(), clip, &dstRect);//, m_angle, nullptr, m_flip);
	}
}

void Text::Update(float deltatime)
{
}



#pragma once
#include "Include/Global.h"
#include "Include/Graphics.h"

class GameResource
{
public:
#pragma region Colors
	SDL_Color whiteColor = { 255, 255, 255 };
	SDL_Color blackColor = { 0, 0, 0 };
	SDL_Color UIColor = whiteColor;
#pragma endregion

#pragma region Fonts
	const int fontSize = SCREEN_HEIGHT / 30;
	const int fontSizeSmall = SCREEN_HEIGHT / 40;
	const int fontSizeLarge = SCREEN_HEIGHT / 20;
	const int fontSizeTitle = SCREEN_HEIGHT / 7.5;
	TTF_Font* boldFont;
	TTF_Font* regularFont;
	TTF_Font* boldFontSmall;
	TTF_Font* boldFontLarge;
	TTF_Font* boldFontTitle;
	TTF_Font* regularFontSmall;
#pragma endregion
	
	bool loadMedia(); //check load medias

	void close();  //free
};
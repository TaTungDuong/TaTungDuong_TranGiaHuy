#pragma once
#include "Include/GameResource.h"

bool GameResource::loadMedia()
{
	bool success = true;
#pragma region Load_text_font
	//Load text font
	boldFont = TTF_OpenFont("assets-main/resources/fonts/open-sans_bold.ttf", fontSize);
	if (boldFont == NULL) {
		printf("Failed to load bold font! TTF Error: %s\n", TTF_GetError());
		success = false;
	}

	boldFontSmall = TTF_OpenFont("assets-main/resources/fonts/open-sans_bold.ttf", fontSizeSmall);
	if (boldFontSmall == NULL) {
		printf("Failed to load bold font small! TTF Error: %s\n", TTF_GetError());
		success = false;
	}

	boldFontLarge = TTF_OpenFont("assets-main/resources/fonts/open-sans_bold.ttf", fontSizeLarge);
	if (boldFontLarge == NULL) {
		printf("Failed to load bold font large! TTF Error: %s\n", TTF_GetError());
		success = false;
	}

	boldFontTitle = TTF_OpenFont("assets-main/resources/fonts/open-sans_bold.ttf", fontSizeTitle);
	if (boldFontTitle == NULL) {
		printf("Failed to load bold font title! TTF Error: %s\n", TTF_GetError());
		success = false;
	}

	regularFont = TTF_OpenFont("assets-main/resources/fonts/open-sans_regular.ttf", fontSize);
	if (regularFont == NULL) {
		printf("Failed to load regular font! TTF Error: %s\n", TTF_GetError());
		success = false;
	}

	regularFontSmall = TTF_OpenFont("assets-main/resources/fonts/open-sans_regular.ttf", fontSizeSmall);
	if (regularFontSmall == NULL) {
		printf("Failed to load regular font small! TTF Error: %s\n", TTF_GetError());
		success = false;
	}
#pragma endregion
	return success;
}

void GameResource::close()
{
	//Free fonts
	TTF_CloseFont(boldFont);
	boldFont = NULL;
	TTF_CloseFont(boldFontSmall);
	boldFontSmall = NULL;
	TTF_CloseFont(boldFontLarge);
	boldFontLarge = NULL;
	TTF_CloseFont(boldFontTitle);
	boldFontTitle = NULL;
	TTF_CloseFont(regularFont);
	regularFont = NULL;
	TTF_CloseFont(regularFontSmall);
	regularFontSmall = NULL;
}
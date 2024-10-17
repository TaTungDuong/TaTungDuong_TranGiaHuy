#pragma once
#include "Include/Global.h"
#include "Include/Graphics.h"
#include "Include/SpriteSheet.h"
#include "Include/GameResource.h"
#include "Include/GameObjective.h"
#include "Include/GameDialogue.h"
#include "Include/GameEnvironment.h"

class GameUI
{
public:
#pragma region Textures
	//static textures
	LTexture gWhiteTexture;
	//corsshair
	LTexture gCrosshairTexture;
	//UI textures
	LTexture gHealthIconTexture;
	LTexture gPistolIconTexture;
	LTexture gRifleIconTexture;
	//background texture for menu
	LTexture gMenuTexture;
	//backdrop texture used for pause screen
	SDL_Texture* backdrop;
#pragma endregion

#pragma region Screen effect textures
	LTexture gVignetteTexture;
	LTexture gLightTexture;
	LTexture gLensDirtTexture;
	LTexture gBloodOverlayTexture;
#pragma endregion

	bool loadMedia(); //check load medias

#pragma region Render, Draw and Update Objects
	void setCamera(SDL_Rect& camera, gameObject target);
	void renderCrosshair(player& myPlayer, int mouseX, int mouseY);
	void renderLighting(GameEnvironment& m_GameEnvironment);
	void drawWeapon(player& myPlayer, GameResource m_GameResource);
	void updateObjective(
		GameObjective& m_GameObjective,
		GameEnvironment& m_GameEnvironment,
		GameDialogue& m_GameDialogue
	);
	void drawObjective(
		GameResource& m_GameResource,
		GameObjective& m_GameObjective,
		GameEnvironment& m_GameEnvironment,
		GameDialogue& m_GameDialogue
	);
	void drawTimer(GameResource& m_GameResource, GameObjective& m_GameObjective);
	void drawHealth(player& myPlayer, GameResource& m_GameResource);
	void drawDialogue(
		GameResource& m_GameResource,
		GameObjective& m_GameObjective,
		GameDialogue& m_GameDialogue
	);
	void drawUI(
		player& myPlayer,
		GameResource& m_GameResource,
		GameObjective& m_GameObjective,
		GameEnvironment& m_GameEnvironment,
		GameDialogue& m_GameDialogue
	);

#pragma endregion
	void close(); //free
};


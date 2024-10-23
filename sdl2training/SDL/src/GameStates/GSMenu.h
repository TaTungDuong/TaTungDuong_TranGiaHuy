#pragma once
#include "GameStateBase.h"

#include"GameObject/Text.h"
#include "GameObject/Sound.h"

#include "Include/Button.h"

#include "Include/GameResource.h"
#include "Include/GameDialogue.h"
#include "Include/GameUI.h"

class MouseButton;
class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;

	bool	loadMedia(); //check load medias
	void	handleMenuEvent(int& choice);

private:
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<Text>					m_textGameName;
	SDL_Color m_textColor;
	std::shared_ptr<MouseButton> btnCredit;
	int score = 0;

#pragma region Menu_Screen
#pragma region Create_Variables
#pragma region Features
	GameResource m_GameResource;
	GameDialogue m_GameDialogue;
	GameUI m_GameUI;
#pragma endregion
#pragma region Button
	button myButton;
	std::vector<button> buttons;
#pragma endregion
#pragma region Input
	int mouseX;
	int mouseY;
	const Uint8* keys;
	Uint32 mouses;
#pragma endregion
#pragma region Event_Handler
	SDL_Event event;
#pragma endregion

#pragma region Camera
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
#pragma endregion
#pragma endregion
};
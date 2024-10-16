#pragma once
#include "GameStateBase.h"

#include "Include/Global.h"
#include "Include/Graphics.h"
#include "Include/Player.h"
#include "Include/PlayerAnimation.h"
#include "Include/PlayerEffect.h"
#include "Include/Zombie.h"
#include "Include/Weapon.h"
#include "Include/Timer.h"
#include "Include/Audio.h"
#include "Include/PopUpText.h"
#include "Include/Button.h"

#include "Include/SpriteSheet.h"
#include "Include/GameEnvironment.h"
#include "Include/GameResource.h"
#include "Include/GameDialogue.h"
#include "Include/GameUI.h"
#include "Include/GameWindows.h"
#include "GameStates/GSMenu.h"

class Sprite2D;
class SpriteAnimation;
class MouseButton;
class Sound;
class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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
	int m_KeyPress;

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> button;
	
	float time = 0.0f;
	float m_Velocity = 10.0f;

};


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
#include "Include/PopUpText.h"
#include "Include/Button.h"

#include "Include/SpriteSheet.h"
#include "Include/GameEnvironment.h"
#include "Include/GameResource.h"
#include "Include/GameDialogue.h"
#include "Include/GameUI.h"
#include "GameStates/GSMenu.h"

enum class confirmState { FALSE, RETRY, QUIT, QUIT_TO_MENU };
enum class endState { FALSE, WIN, LOSE, TIME_OVER };

struct StateStruct
{
	std::function<void()> StatePointer; //void (*StatePointer)();
};

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

	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int m_KeyPress;


	bool init();
	bool loadMedia();
	void initLevel();
	//menu screen
	void Menu();
	void handleMenuEvent(int& choice);

	//game screen
	void Game();
	void handleGameEvent();
	void handleGameInput();
	void setDifficulty();

	//pause screen
	void Pause() override;
	bool paused = false; //flag
	void handlePauseEvent();

	//confirm screen
	void Confirm();
	confirmState confirmMode;
	void showConfirmScreen(confirmState m);
	void hideConfirmScreen();
	bool confirmScreen = false; //flag
	void handleConfirmEvent(int& choice);

	//end game screen
	void EndGame();
	endState endGameMode = endState::FALSE;
	void showEndGamecreen(endState m);
	void hideEndGameScreen();
	bool endGameScreen = false; //flag
	void handleEndGameEvent(int& choice);
	void checkEndGame();

#pragma endregion
#pragma region Game_Objects
	zombie myZombie;
	gameObject myTree;
	gameObject myHarmZone;
	gameObject mySignalZone;
	gameObject myHealthPickup;
#pragma endregion


private:
	std::shared_ptr<Sprite2D>	m_background;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<MouseButton> button;
	
	float time = 0.0f;
	float m_Velocity = 10.0f;

#pragma region Flags
	bool initedLevel = false;
	bool quit = false;
	bool cheat = false;
#pragma endregion

};


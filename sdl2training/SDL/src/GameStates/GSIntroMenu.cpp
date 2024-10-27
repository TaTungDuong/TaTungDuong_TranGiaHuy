#include "GSIntroMenu.h"
#include "ResourceManagers.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include "Sound.h"

GSIntroMenu::GSIntroMenu()
{
	m_time = 0;
}


GSIntroMenu::~GSIntroMenu()
{
}

void GSIntroMenu::Init()
{
	//// background
	//m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	//m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	//m_background->Set2DPosition(0, 0);

	//// button close
	//texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	//button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//button->SetSize(50, 50);
	//button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	//button->SetOnClick([this]() {
	//	GameStateMachine::GetInstance()->PopState();
	//	});
	//m_listButton.push_back(button);

	// Animation 
	m_listAnimation.clear();
	auto texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/[cutscenes]/menu_1.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 10, 1, 0.075f);
	obj->SetFlip(SDL_FLIP_NONE);
	obj->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	obj->Set2DPosition(0, 0);
	obj->m_currentFrame = 0;
	m_listAnimation.push_back(obj);

	isReady = true;
	m_time = 0.0f;
	currentAnimation = 0;
	m_KeyPress = 0;

	//play background music
	Sound::GetInstance()->playMenuMusic();
	Sound::GetInstance()->stopBackgroundLoop();
}

void GSIntroMenu::Exit()
{
}


void GSIntroMenu::Pause()
{

}
void GSIntroMenu::Resume()
{
}


void GSIntroMenu::HandleEvents()
{
}

void GSIntroMenu::HandleKeyEvents(SDL_Event& e)
{

}

void GSIntroMenu::HandleTouchEvents(SDL_Event& e)
{

}

void GSIntroMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSIntroMenu::Update(float deltaTime)
{
	if (!isReady || m_listAnimation.size() == 0) return;

	for (auto& it : m_listAnimation)
	{
		if (it->m_currentFrame >= it->m_frameCount - 1)
		{
			if (currentAnimation)
			{
				printf("INTRO_MENU_TIME\n");
				GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
			}
			else
			{
				currentAnimation++;
				printf("INTRO_MENU: %d\n", currentAnimation);

				auto texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/[cutscenes]/menu_2.png");
				it = std::make_shared<SpriteAnimation>(texture, 1, 10, 1, 0.075f);
				it->SetFlip(SDL_FLIP_NONE);
				it->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
				it->Set2DPosition(0, 0);
				it->m_currentFrame = 0;
			}
			return;
		}
	}

	for (auto it : m_listAnimation)
	{
		if (it->m_currentFrame < it->m_frameCount - 1)
		{
			it->Update(deltaTime);
		}
	}
}

void GSIntroMenu::Draw(SDL_Renderer* renderer)
{
	//	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
}

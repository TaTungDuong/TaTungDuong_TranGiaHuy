#include "GSIntroCutscene.h"
#include "ResourceManagers.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include "Sound.h"

GSIntroCutscene::GSIntroCutscene()
{
	srand(static_cast<unsigned int>(time(0)));
	m_time = 0.0f;
	voiceline = rand() % 2;
}


GSIntroCutscene::~GSIntroCutscene()
{
}

void GSIntroCutscene::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/ui/others/black.png");

	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	//// button close
	//texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	//button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//button->SetSize(50, 50);
	//button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	//button->SetOnClick([this]() {
	//	GameStateMachine::GetInstance()->PopState();
	//	});
	//m_listButton.push_back(button);
	
	// button next
	texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/ui/others/empty.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	button->Set2DPosition(0, 0);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_INTRO_STORY);
		});
	m_listButton.push_back(button);
	
	// Animation 
	m_listAnimation.clear();
	texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/[cutscenes]/intro/intro.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 32, 1, 0.5f);
	obj->SetFlip(SDL_FLIP_NONE);
	obj->SetSize(512, 300);
	obj->Set2DPosition((float)(SCREEN_WIDTH - obj->GetWidth()) / 2, (float)(SCREEN_HEIDHT - obj->GetHeight()) / 2);
	obj->m_currentFrame = 0;
	m_listAnimation.push_back(obj);
	Sound::GetInstance()->playVoiceIntro(voiceline);

	m_time = 0;
	m_KeyPress = 0;
}

void GSIntroCutscene::Exit()
{
}


void GSIntroCutscene::Pause()
{

}
void GSIntroCutscene::Resume()
{
}


void GSIntroCutscene::HandleEvents()
{
}

void GSIntroCutscene::HandleKeyEvents(SDL_Event& e)
{

}

void GSIntroCutscene::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSIntroCutscene::HandleMouseMoveEvents(int x, int y)
{
}

void GSIntroCutscene::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		if (it->m_currentFrame < it->m_frameCount - 1)
		{
			it->Update(deltaTime);
		}
	}
}

void GSIntroCutscene::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
}

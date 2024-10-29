#include "GSIntroStory.h"
#include "ResourceManagers.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include "Sound.h"

GSIntroStory::GSIntroStory()
{
	m_time = 0.0f;
	currentAnimation = 0;
}


GSIntroStory::~GSIntroStory()
{
}

void GSIntroStory::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/ui/others/empty.png");
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

	// button next
	texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/ui/others/empty.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	button->Set2DPosition(0, 0);
	button->SetOnClick([this]() {
		currentAnimation++;
		if (currentAnimation <= 7)
		{
			SetAnimation();
		}
		else
		{
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_LOADING);
		}
		});
	m_listButton.push_back(button);

	// Animation 
	currentAnimation = 1;
	SetAnimation();

	isReady = true;
	m_time = 0.0f;
	m_KeyPress = 0;

	//play background music
	Sound::GetInstance()->playStoryMusic();
}

void GSIntroStory::SetAnimation()
{
	m_listAnimation.clear();
	std::string linePath = "assets-main/sprites/[cutscenes]/story/l" + std::to_string(currentAnimation) + ".png";
	auto texture = ResourceManagers::GetInstance()->GetTexture(linePath);
	obj = std::make_shared<SpriteAnimation>(texture, 1, 9, 1, 0.075f);
	obj->SetFlip(SDL_FLIP_NONE);
	obj->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	obj->Set2DPosition(0, 0);
	obj->m_currentFrame = 0;
	m_listAnimation.push_back(obj);
}

void GSIntroStory::Exit()
{
}


void GSIntroStory::Pause()
{

}
void GSIntroStory::Resume()
{
}


void GSIntroStory::HandleEvents()
{
}

void GSIntroStory::HandleKeyEvents(SDL_Event& e)
{

}

void GSIntroStory::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSIntroStory::HandleMouseMoveEvents(int x, int y)
{
}

void GSIntroStory::Update(float deltaTime)
{
	if (!isReady || m_listAnimation.size() == 0) return;

	for (auto it : m_listAnimation)
	{
		if (it->m_currentFrame < it->m_frameCount - 1)
		{
			it->Update(deltaTime);
		}
	}
}

void GSIntroStory::Draw(SDL_Renderer* renderer)
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

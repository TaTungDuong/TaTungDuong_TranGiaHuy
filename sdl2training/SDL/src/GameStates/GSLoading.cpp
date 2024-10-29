#include "GSLoading.h"
#include "ResourceManagers.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include "Sound.h"

GSLoading::GSLoading()
{
	srand(static_cast<unsigned int>(time(0)));
	m_timeInterval = GetRandomFloat(3.0f, 9.0f, 0.5f);
	m_timeCounter = 0.0f;
}


GSLoading::~GSLoading()
{
}

void GSLoading::Init()
{
	std::string m_loadingScreenPath = "assets-main/sprites/ui/loading_screens/" + std::to_string(rand() % 5) + ".png";
	auto texture = ResourceManagers::GetInstance()->GetTexture(m_loadingScreenPath);

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
		if (m_timeCounter >= m_timeInterval)
		{
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		}
	});
	m_listButton.push_back(button);

	// loading bar
	texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/ui/others/loading_bg.png");
	m_loadingBg = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_loadingBg->SetSize(728, 16);
	m_loadingBg->Set2DPosition(
		(float)(SCREEN_WIDTH - m_loadingBg->GetWidth()) / 2,
		(float)(SCREEN_HEIDHT - m_loadingBg->GetHeight()) / 2 + 256
	);

	texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/ui/others/white.png");
	m_loadingBar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_loadingBar->SetSize(0, 8);
	m_loadingBar->Set2DPosition(
		(float)(SCREEN_WIDTH - m_loadingBar->GetWidth()) / 2, 
		(float)(SCREEN_HEIDHT - m_loadingBar->GetHeight()) / 2 + 256
	);

	// loading text
	texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/ui/others/loading.png");
	m_text = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_text->SetSize(195 * 3 / 4, 30);
	m_text->Set2DPosition(
		(float)(SCREEN_WIDTH - m_text->GetWidth()) / 2,
		(float)(SCREEN_HEIDHT + m_text->GetHeight() * 3 / 2) / 2 + 256
	);

	//// Animation 
	//m_listAnimation.clear();
	//texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/[cutscenes]/intro.png");
	//obj = std::make_shared<SpriteAnimation>(texture, 1, 32, 1, 0.5f);
	//obj->SetFlip(SDL_FLIP_NONE);
	//obj->SetSize(512, 300);
	//obj->Set2DPosition((float)(SCREEN_WIDTH - obj->GetWidth()) / 2, (float)(SCREEN_HEIDHT - obj->GetHeight()) / 2);
	//obj->m_currentFrame = 0;
	//m_listAnimation.push_back(obj);
	//Sound::GetInstance()->playVoiceIntro(voiceline);
	///Set Font
	m_timeCounter = 0.0f;
	m_KeyPress = 0;
}

void GSLoading::Exit()
{
}


void GSLoading::Pause()
{

}
void GSLoading::Resume()
{
}


void GSLoading::HandleEvents()
{
}

void GSLoading::HandleKeyEvents(SDL_Event& e)
{

}

void GSLoading::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSLoading::HandleMouseMoveEvents(int x, int y)
{
}

void GSLoading::Update(float deltaTime)
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

	//Update loading bar
	if (m_timeCounter < m_timeInterval)
	{
		m_timeCounter += deltaTimer.getDeltaTime();
	}
	else
	{
		m_timeCounter = m_timeInterval;
		
		auto texture = ResourceManagers::GetInstance()->GetTexture("assets-main/sprites/ui/others/left-click.png");
		m_text = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
		m_text->SetSize(336 * 3 / 4, 30);
		m_text->Set2DPosition(
			(float)(SCREEN_WIDTH - m_text->GetWidth()) / 2,
			(float)(SCREEN_HEIDHT + m_text->GetHeight() * 3 / 2) / 2 + 256
		);
	}
	float LOADING_BAR_WIDTH = (m_timeCounter / m_timeInterval) * 720.0f;
	m_loadingBar->SetSize(int(LOADING_BAR_WIDTH), 8);
	m_loadingBar->Set2DPosition(
		(float)(SCREEN_WIDTH - m_loadingBar->GetWidth()) / 2,
		(float)(SCREEN_HEIDHT - m_loadingBar->GetHeight()) / 2 + 256
	);
}

void GSLoading::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	m_loadingBg->Draw(renderer);
	m_loadingBar->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
	m_text->Draw(renderer);
}

#include "GSMenu.h"
#include "ResourceManagers.h"
#include "MouseButton.h"
GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}


#pragma region Load_Media
bool GSMenu::loadMedia()
{
	//Loading success flag
	bool success = true;
	success = m_GameUI.loadMedia();

#pragma region Load_audio
	//Load audio
#pragma endregion
	success = m_GameResource.loadMedia();
	success = m_GameDialogue.loadMedia();

	return success;
}
#pragma endregion

void GSMenu::Init()
{
/**/
	//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//play background music
			Sound::GetInstance()->playMenuMusic();
			Sound::GetInstance()->stopBackgroundLoop();

			//show back the cursor
			SDL_ShowCursor(SDL_ENABLE);
			//SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); //set the cursor to center of the window

			//set text positions
			int textOffset = SCREEN_HEIGHT / 4;
			int textX = SCREEN_WIDTH / 2;
			int textY = SCREEN_HEIGHT / 2 - textOffset;

			//add buttons
			//start button
			int buttonpy = textY + SCREEN_HEIGHT / 7.5 + 75;
			myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Start", m_GameResource.regularFont);
			buttons.push_back(myButton);
			//toggle music button
			buttonpy += 75;
			myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Toggle music", m_GameResource.regularFont);
			buttons.push_back(myButton);
			//quit button
			buttonpy += 75;
			myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Quit", m_GameResource.regularFont);
			buttons.push_back(myButton);
		}
/**/

/*
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	
	btnPlay->SetSize(150, 150);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth())/2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		Renderer::GetInstance()->~Renderer();
		});
	m_listButton.push_back(btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);

	//Setting game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_settings.tga");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(100, 100);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnOption->GetWidth()) / 2, (SCREEN_HEIDHT / 3) *2 );
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(btnOption);

	//CREDIT game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_help.tga");
	btnCredit = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnCredit->Set2DPosition((SCREEN_WIDTH - btnCredit->GetWidth()) / 2, SCREEN_HEIDHT / 6 *5);
	btnCredit->SetSize(100, 100);
	btnCredit->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(btnCredit);

	// game title
	///Set Font

	m_textColor = { 255,0,0 };
	auto font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf", 28);
	m_textGameName = std::make_shared<Text>("Your Game",font,  m_textColor);
	m_textGameName->SetSize(300, 150);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth())/2, SCREEN_HEIDHT / 2 - 300);
	
	/// sound
	
	Sound::GetInstance()->LoadSound("Alarm01.wav");
	Sound::GetInstance()->PlaySound("Alarm01.wav");
*/
}

void GSMenu::Exit()
{
	
}


void GSMenu::Pause()
{
	
	// button close
	Sound::GetInstance()->PauseSound();
	
}

void GSMenu::Resume()
{
	
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
/*
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
*/
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
/*
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	
	m_textGameName->Draw(renderer);
*/
	int choice = -1; //0 for yes, 1 for no

	while (choice == -1)
	{
		deltaTimer.tick();
		mouses = SDL_GetMouseState(&mouseX, &mouseY);
		handleMenuEvent(choice);

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		//Render black overlay 
		m_GameUI.gMenuTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		//Render title
//		drawText(textX, textY, boldFontTitle, UIColor, "Catgirl & Shotgun", 1);

		//set toggle music text
		if (setting_Music)
		{
			buttons[1].setText("Music On");
		}
		else if (!setting_Music)
		{
			buttons[1].setText("Music Off");
		}
		//Render buttons
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].checkButton(mouses, mouseX, mouseY);
			buttons[i].render(gRenderer);
		}

		//Update screen
		SDL_RenderPresent(gRenderer);
	}

	//remove all buttons
	buttons.clear();

	switch (choice)
	{
	case 0: //start
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		break;
	case 1: //toggle music
		setting_Music = !setting_Music;
		break;
	case 2: //quit
		exit(0);
		break;
	}

	//get backdrop
	m_GameUI.backdrop = m_GameUI.gMenuTexture.getSDLTexture();
}

void GSMenu::handleMenuEvent(int& choice)
{
	//Poll events
	while (SDL_PollEvent(&event))
	{
		//check events
		switch (event.type)
		{
		case SDL_QUIT: //User hit the X
			choice = 2;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				//resize window
				SDL_SetWindowSize(gWindow, event.window.data1, event.window.data2);
				//SCREEN_WIDTH = event.window.data1;
				//SCREEN_HEIGHT = event.window.data2;
			}
			break;
		case SDL_KEYDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
/**/
			//start button
			if (buttons[0].checkInside(mouseX, mouseY))
			{
				choice = 0;
			}
			//toggle music button
			if (buttons[1].checkInside(mouseX, mouseY))
			{
				choice = 1;
			}
			//quit
			if (buttons[2].checkInside(mouseX, mouseY))
			{
				choice = 2;
			}

			break;
		}
	}

	//play or pause music
	if (setting_Music)
	{
		Mix_ResumeMusic();
	}
	else if (!setting_Music)
	{
		Mix_PauseMusic();
	}
}

void GSMenu::Menu()
{
	//play background music
	Sound::GetInstance()->playMenuMusic();

	Sound::GetInstance()->stopBackgroundLoop();

	//show back the cursor
	SDL_ShowCursor(SDL_ENABLE);
	//SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); //set the cursor to center of the window

	//set text positions
	int textOffset = SCREEN_HEIGHT / 4;
	int textX = SCREEN_WIDTH / 2;
	int textY = SCREEN_HEIGHT / 2 - textOffset;

	//add buttons
	//start button
	int buttonpy = textY + SCREEN_HEIGHT / 7.5 + 75;
	myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Start", m_GameResource.regularFont);
	buttons.push_back(myButton);
	//toggle music button
	buttonpy += 75;
	myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Toggle music", m_GameResource.regularFont);
	buttons.push_back(myButton);
	//quit button
	buttonpy += 75;
	myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Quit", m_GameResource.regularFont); 
	buttons.push_back(myButton);

	int choice = -1; //0 for yes, 1 for no

	while (choice == -1)
	{
		deltaTimer.tick();
		mouses = SDL_GetMouseState(&mouseX, &mouseY);
		handleMenuEvent(choice);

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		//Render black overlay 
		m_GameUI.gMenuTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		//Render title
//		drawText(textX, textY, boldFontTitle, UIColor, "Catgirl & Shotgun", 1);

		//set toggle music text
		if (setting_Music)
		{
			buttons[1].setText("Music On");
		}
		else if (!setting_Music)
		{
			buttons[1].setText("Music Off");
		}
		//Render buttons
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].checkButton(mouses, mouseX, mouseY);
			buttons[i].render(gRenderer);
		}

		//Update screen
		SDL_RenderPresent(gRenderer);
	}

	//remove all buttons
	buttons.clear();
	/*
	StateStruct temp;
	switch (choice)
	{
	case 0: //start
		initedLevel = false;
		temp.StatePointer = Game;
		g_StateStack.push(temp);
		break;
	case 1: //toggle music
		setting_Music = !setting_Music;
		break;
	case 2: //quit
		showConfirmScreen(confirmState::QUIT);
		temp.StatePointer = Confirm;
		g_StateStack.push(temp);
	}
	*/
	//get backdrop
	m_GameUI.backdrop = m_GameUI.gMenuTexture.getSDLTexture();
}
#pragma endregion




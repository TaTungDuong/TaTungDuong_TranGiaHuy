#include "Include/Global.h"
#include "Include/Graphics.h"
#include "Include/Player.h"
#include "Include/PlayerAnimation.h"
#include "Include/Zombie.h"
#include "Include/Weapon.h"
#include "Include/Timer.h"
#include "Include/Audio.h"
#include "Include/PopUpText.h"
#include "Include/Button.h"

#include "Include/SpriteSheet.h"
SpriteSheet m_SpriteSheet;

#include "Include/GameEnvironment.h"
GameEnvironment m_GameEnvironment;
GameObjective m_GameObjective;

#include "Include/GameResource.h"
GameResource m_GameResource;

#include "Include/GameDialogue.h"
GameDialogue m_GameDialogue;

#include "Include/GameUI.h"
GameUI m_GameUI;

#include "Include/GameWindows.h"
GameWindows m_GameWindows;

#pragma region Create_Variables
#pragma region Rendering
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
#pragma endregion

#pragma region Menus
std::stack<StateStruct> g_StateStack;
std::stack<StateStruct> emptyStack; //for clearing stack

//menu screen
void Menu();
void handleMenuEvent(int& choice);

//game screen
void Game();
void handleGameEvent();
void handleGameInput();

//pause screen
void Pause();
bool paused = false; //flag
void handlePauseEvent();

//confirm screen
void Confirm();
enum class confirmState { FALSE, RETRY, QUIT, QUIT_TO_MENU };
confirmState confirmMode;
void showConfirmScreen(confirmState m);
void hideConfirmScreen();
bool confirmScreen = false; //flag
void handleConfirmEvent(int& choice);

//end game screen
void EndGame();
enum class endState { FALSE, WIN, LOSE, TIME_OVER };
endState endGameMode = endState::FALSE;
void showEndGamecreen(endState m);
void hideEndGameScreen();
bool endGameScreen = false; //flag
void handleEndGameEvent(int& choice);

//exit
void Exit();
#pragma endregion
#pragma region Game_Objects
player myPlayer;
playerAnimation myPlayerAnimation;

zombie myZombie;
gameObject myTree;
gameObject myHarmZone;
gameObject mySignalZone;
gameObject myHealthPickup;
#pragma endregion
/**/
#pragma region Audio
audioManager myAudio;
#pragma endregion

#pragma region Framerate
LTimer systemTimer; //The frames per second timer
LTimer deltaTimer; //The frames per second cap timer
int countedFrames = 0; //total frames
#pragma endregion

#pragma region Input
int mouseX;
int mouseY;
const Uint8* keys;
Uint32 mouses;
#pragma endregion

#pragma region Flags
bool initedLevel = false;
bool quit = false;
bool cheat = false;
#pragma endregion

#pragma region Event_Handler
SDL_Event event;
#pragma endregion

#pragma region Camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
#pragma endregion

#pragma region Button
button myButton;
std::vector<button> buttons;
#pragma endregion
#pragma endregion

#pragma region Init_And_Load_Media
bool init()
{
	//Initialization flag
	bool success = true;
	success = m_GameWindows.init();
	
	StateStruct state;
	//add menu 
	state.StatePointer = Menu;
	g_StateStack.push(state);
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	success = m_GameEnvironment.loadMedia(m_SpriteSheet);
	success = m_GameUI.loadMedia();
#pragma region Load_animations_textures
	//Load animation textures
	success = m_SpriteSheet.loadPlayerAnimationMedia();
	success = m_SpriteSheet.loadPlayerMedia();
	success = m_SpriteSheet.loadEnemyMedia();
#pragma endregion

#pragma region Load_audio
	//Load audio
	myAudio.loadAudio();
#pragma endregion
	success = m_GameResource.loadMedia();
	success = m_GameDialogue.loadMedia();

	return success;
}
#pragma endregion

#pragma region Menu_Screen
void handleMenuEvent(int& choice)
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

void Menu()
{
	//play background music
	myAudio.playMenuMusic();

	myAudio.stopBackgroundLoop();

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
		
		m_GameWindows.frameCap(myPlayer);
	}

	//remove all buttons
	buttons.clear();

	m_GameWindows.clearScreen();

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

	//get backdrop
	m_GameUI.backdrop = m_GameUI.gMenuTexture.getSDLTexture();
}
#pragma endregion

#pragma region Game_Screen
void initLevel()
{
	//reset state and flags
	endGameMode = endState::FALSE;
	confirmMode = confirmState::FALSE;
	paused = false;
	confirmScreen = false;
	endGameScreen = false;
	m_GameEnvironment.canSpawnEnemy = false;

	//clear level objects
	m_GameEnvironment.init();

	//reset difficulty
	DIFFICULTY = 1;
	m_GameObjective.totalZombieKilled = 0;

	//reset timer
	m_GameObjective.timeLeft = TIME_LIMIT;

	//reset sound effects
	Mix_HaltChannel(-1);

	//if tutorial have been finished
	if (m_GameObjective.currentObjective >= 2)
	{
		//reset objectives
		m_GameObjective.currentObjective = 3;
		m_GameObjective.objective[0] = true;
		m_GameObjective.objective[1] = true;
		m_GameObjective.objective[2] = true;
		m_GameObjective.tutorial = false;
		for (int i = 3; i < TOTAL_OBJECTIVE; i++)
		{
			m_GameObjective.objective[i] = false;
		}
		m_GameObjective.obj_zombieKilled = 0;
		m_GameEnvironment.canSpawnEnemy = true;
		//reset dialogues
		m_GameDialogue.dialogue.currentLine = 16;
		m_GameDialogue.dialogue.currentPart = 4;
	}
	else
	{
		//reset objectives
		m_GameObjective.currentObjective = -1;
		for (int i = 0; i < TOTAL_OBJECTIVE; i++)
		{
			m_GameObjective.objective[i] = false;
		}
		for (int i = 0; i < 3; i++)
		{
			m_GameObjective.obj_keyPressed[i] = false;
		}
		m_GameObjective.tutorial = true;
		//reset dialogues
		m_GameDialogue.dialogue.currentLine = 0;
		m_GameDialogue.dialogue.currentPart = 0;
	}

	//init player
	myPlayer.initPlayer();
	myPlayerAnimation.initPlayer();

	//create weapon
	myPlayer.myWeapon[0].init(PISTOL_NAME, PISTOL_DAMAGE, PISTOL_RATE_OF_FIRE, PISTOL_CLIP_SIZE, PISTOL_CLIP_SIZE, PISTOL_RELOAD_TIME);
	myPlayer.myWeapon[1].init(RIFLE_NAME, RIFLE_DAMAGE, RIFLE_RATE_OF_FIRE, RIFLE_CLIP_SIZE, RIFLE_CLIP_SIZE, RIFLE_RELOAD_TIME);

	//create trees
	createGameObjectRandom(myTree, m_GameEnvironment.trees,
		MAX_TREE_NUM, MIN_TREE_SIZE, MAX_TREE_SIZE, -1, TREES_CLIP);

	//create harmzone
	createGameObjectRandom(myHarmZone, m_GameEnvironment.harmZones, 
		MAX_HARM_ZONE_NUM * DIFFICULTY, MIN_HARM_ZONE_SIZE, MAX_HARM_ZONE_SIZE, 360, -1);

	//create health pickups
	createGameObjectRandom(myHealthPickup, m_GameEnvironment.healthPickUps, 
		MAX_HEALTH_PICKUP_NUM, HEALTH_PICKUP_SIZE, HEALTH_PICKUP_SIZE, 0, -1);

	//create objective zones for objective 5 (find the random signals)
	createGameObjectRandom(mySignalZone, m_GameEnvironment.signalZones, 
		TOTAL_SIGNAL_ZONE, 500, 500, 0, -1); //random objective zone
	m_GameObjective.obj_zones = m_GameEnvironment.signalZones.size();
	for (int i = 0; i < m_GameEnvironment.signalZones.size(); i++)
	{
		printf("signalZones[%i] px = %f, py = %f\n", i, m_GameEnvironment.signalZones[i].px, m_GameEnvironment.signalZones[i].py);
	}
	printf("---inited level---\n");
}

void checkEndGame()
{
	if (m_GameObjective.timeLeft <= 0)
	{
		if (m_GameObjective.objective[TOTAL_OBJECTIVE - 1])
		{
			showEndGamecreen(endState::WIN);
		}
		else
		{
			showEndGamecreen(endState::TIME_OVER);
		}
	}
	if (myPlayer.health <= 0)
	{
		showEndGamecreen(endState::LOSE);
	}
}
void setDifficulty()
{
	DIFFICULTY = 1 + m_GameObjective.totalZombieKilled / DIFFICULTY_REQUIREMENT;
	MAX_ZOMBIE_NUM = DIFFICULTY * ZOMBIE_NUMBER_STEP;
}

void handleGameEvent()
{
	Uint32 windowID = SDL_GetWindowID(gWindow);

	//Poll events
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: //User hit the X
			showConfirmScreen(confirmState::QUIT);
			break;
		case SDL_WINDOWEVENT:
			//if window is resized
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				//resize window
				SDL_SetWindowSize(gWindow, event.window.data1, event.window.data2);
				//SCREEN_WIDTH = event.window.data1;
				//SCREEN_HEIGHT = event.window.data2;
			}
			//if window have lost focus
			if (event.window.windowID == windowID)
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_FOCUS_LOST:

					paused = true;
					break;
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (myPlayer.myWeapon[myPlayer.currentWeapon].checkAmmo() &&
				!myPlayer.myWeapon[myPlayer.currentWeapon].checkReload()) //shoot
			{
				myPlayer.currentState = playerState::FIRE;
				myPlayer.currentFrame = 0;
				myPlayer.myWeapon[myPlayer.currentWeapon].resetTimer();
			}
			else if (!myPlayer.myWeapon[myPlayer.currentWeapon].checkAmmo())
			{
				myAudio.playGunEmpty();
			}
			break;
		case SDL_MOUSEWHEEL:
			myPlayer.cycleWeapon();
			myAudio.playSwapWeapon();
			myAudio.stopReload();
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_q) //cycle weapon
			{
				myPlayer.cycleWeapon();
				myAudio.playSwapWeapon();
				myAudio.stopReload();
			}
			if (event.key.keysym.sym == SDLK_r) //reload weapon
			{
				if (myPlayer.myWeapon[myPlayer.currentWeapon].ammo <= myPlayer.myWeapon[myPlayer.currentWeapon].getClipSize() &&
					!myPlayer.myWeapon[myPlayer.currentWeapon].getReloadFlag())
				{
/*					
					myPlayer.myWeapon[myPlayer.currentWeapon].reload();
					myPlayer.currentState = playerState::RELOAD;
					myPlayer.currentFrame = 0;
					myAudio.playReload();
*/
					//for objective 3
					m_GameObjective.checkObjective2();
				}
			}
			if (event.key.keysym.sym == SDLK_1) //weapon 1
			{
				if (myPlayer.currentWeapon != 0)
				{
					myPlayer.currentWeapon = 0;
					myAudio.playSwapWeapon();
					myAudio.stopReload();
				}
			}
			if (event.key.keysym.sym == SDLK_2) //weapon 2
			{
				if (myPlayer.currentWeapon != 1)
				{
					myPlayer.currentWeapon = 1;
					myAudio.playSwapWeapon();
					myAudio.stopReload();
				}
			}
			if (event.key.keysym.sym == SDLK_ESCAPE) //esc
			{
				paused = true;
			}

			if (event.key.keysym.sym == SDLK_BACKQUOTE) //cheat toggle
			{
				cheat = !cheat;
				printf("---cheat mode: %i---\n", cheat);
			}

			if (event.key.keysym.sym == SDLK_SPACE) //cheat: restore health
			{
				if (cheat)
				{
					myPlayer.health = 100;
					printf("Cheat: player health restored\n");
				}
			}

			if (event.key.keysym.sym == SDLK_HOME) //cheat: toggle god mode
			{
				if (cheat)
				{
					static bool godMode = false;
					godMode = !godMode;
					if (godMode) { myPlayer.health = 99999999; }
					if (!godMode) { myPlayer.health = 100; }
					printf("Cheat: god mode = %i\n", godMode);
				}
			}

			if (event.key.keysym.sym == SDLK_END) //cheat: instant kill
			{
				if (cheat)
				{
					myPlayer.health = -100;
					printf("Cheat: instant kill\n");
				}
			}

			if (event.key.keysym.sym == SDLK_DELETE) //cheat: kill all zombies
			{
				if (cheat)
				{
					m_GameEnvironment.zombies.clear();
					printf("Cheat: killed all zombies\n");
				}
			}

			if (event.key.keysym.sym == SDLK_INSERT) //cheat: spawn zombies
			{
				if (cheat)
				{
					m_GameEnvironment.canSpawnEnemy = !m_GameEnvironment.canSpawnEnemy;
					printf("Cheat: force spawn zombies\n");
				}
			}

			if (event.key.keysym.sym == SDLK_UP) //cheat: increase total zombie numbers
			{
				if (cheat)
				{
					m_GameObjective.totalZombieKilled += DIFFICULTY_REQUIREMENT;
					printf("Cheat: maximum zombies: %i\n", MAX_ZOMBIE_NUM);
				}
			}

			if (event.key.keysym.sym == SDLK_DOWN) //cheat: decrease total zombie numbers
			{
				if (cheat)
				{
					m_GameObjective.totalZombieKilled -= DIFFICULTY_REQUIREMENT;
					printf("Cheat: maximum zombies: %i\n", MAX_ZOMBIE_NUM);
				}
			}
			break;
		}
	}
}

void handleGameInput()
{
	keys = SDL_GetKeyboardState(NULL);
	mouses = SDL_GetMouseState(&mouseX, &mouseY);

	//check keyboard input
	if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])
	{
		if (myPlayer.py - myPlayer.size < 0)
		{
			myPlayer.vy = 0;
		}
		else
		{
			myPlayer.vy = -1;
			myPlayer.currentState = playerState::WALK;
			myPlayerAnimation.currentState = playerAnimationState::WALK;
		}

		//for objective 1
		m_GameObjective.checkObjective0(0);
	}
	if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])
	{
		if (myPlayer.py + myPlayer.size > LEVEL_HEIGHT)
		{
			myPlayer.vy = 0;
		}
		else
		{
			myPlayer.vy = 1;
			myPlayer.currentState = playerState::WALK;
			myPlayerAnimation.currentState = playerAnimationState::WALK;
		}

		//for objective 1		
		m_GameObjective.checkObjective0(1);
	}
	if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
	{
		if (myPlayer.px - myPlayer.size < 0)
		{
			myPlayer.vx = 0;
		}
		else
		{
			myPlayer.vx = -1;
			myPlayer.currentState = playerState::WALK;
			myPlayerAnimation.currentState = playerAnimationState::WALK;
		}

		//for objective 1
		m_GameObjective.checkObjective0(2);
	}
	if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
	{
		if (myPlayer.px + myPlayer.size > LEVEL_WIDTH)
		{
			myPlayer.vx = 0;
		}
		else
		{
			myPlayer.vx = 1;
			myPlayer.currentState = playerState::WALK;
			myPlayerAnimation.currentState = playerAnimationState::WALK;
		}

		//for objective 1
		m_GameObjective.checkObjective0(3);
	}

	if (keys[SDL_SCANCODE_LSHIFT]) //cheat: double speed
	{
		if (cheat)
		{
			myPlayer.vx *= 2;
			myPlayer.vy *= 2;
		}
	}
	myPlayerAnimation.vx = myPlayer.vx;
	myPlayerAnimation.vy = myPlayer.vy;

	//check mouse input
	if (mouses & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (myPlayer.myWeapon[myPlayer.currentWeapon].checkRateOfFire() &&
			myPlayer.myWeapon[myPlayer.currentWeapon].checkAmmo() &&
			!myPlayer.myWeapon[myPlayer.currentWeapon].checkReload())
		{
			myPlayer.currentState = playerState::FIRE;
			myPlayer.currentFrame = 0;
//			myPlayer.myWeapon[myPlayer.currentWeapon].ammo--;

			SDL_GetMouseState(&mouseX, &mouseY);
			bullet myBullet(camera, myPlayer, mouseX, mouseY);
			m_GameEnvironment.bullets.push_back(myBullet);
			myAudio.playGunshot(myPlayer);

			//for objective 2
			m_GameObjective.checkObjective1();
		}
	}
}

void Game()
{
	m_GameWindows.clearScreen();

	if (!initedLevel)
	{
		//init level
		initLevel();

		//play background music
		if (setting_Music)
		{
			myAudio.playMainMusic();
		}
		myAudio.playBackgroundLoop();

		initedLevel = true;
	}

	//While application is running
	while (initedLevel && !quit && !paused && !confirmScreen && !endGameScreen)
	{
		deltaTimer.tick();
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_ShowCursor(SDL_DISABLE);
		myPlayer.previousState = myPlayer.currentState;
		myPlayerAnimation.previousState = myPlayerAnimation.currentState;
		m_GameUI.setCamera(camera, myPlayer);

		//Set the player back to idle mode
		myPlayer.currentState = playerState::IDLE;
		myPlayerAnimation.currentState = playerAnimationState::IDLE;
		myPlayer.vx = 0;
		myPlayer.vy = 0;
		myPlayerAnimation.vx = 0;
		myPlayerAnimation.vy = 0;

		setDifficulty();

		handleGameEvent();
		handleGameInput();

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		//Render ground
		m_GameEnvironment.renderGround(camera);

		//Render blood pool
		m_GameEnvironment.renderBloodPool(camera);

		//Update and render bullets
		m_GameEnvironment.updateBullet(
			myPlayer, m_GameObjective, myAudio
		);

		//render health pickups
		renderGameObject(camera, m_GameEnvironment.gHealthPickUpTexture, m_GameEnvironment.healthPickUps);

		//Update and render player
		m_SpriteSheet.updatePlayer(
			myPlayer,
			myPlayerAnimation,
			mouseX,
			mouseY,
			m_GameEnvironment.trees,
			m_GameEnvironment.harmZones,
			m_GameEnvironment.bloodpools,
			m_GameEnvironment.zombies,
			m_GameEnvironment.bullets,
			m_GameEnvironment.signalZones,
			m_GameEnvironment.healthPickUps,
			deltaTimer,
			myAudio
		);

		//Update and render zombie
//		updateZombie();
		m_GameEnvironment.updateEnemy(m_SpriteSheet, myPlayer, myAudio, camera);

		//Render lightings
		m_GameUI.renderLighting(m_GameEnvironment);

		//Render other game objects
		//render trees
		renderGameObject(camera, m_GameEnvironment.gTreeTexture, m_GameEnvironment.trees, m_GameEnvironment.gTreeClips);
		//render harm zone
		m_GameUI.gLightTexture.setColor(255, 0, 0, 200);
		renderGameObject(camera, m_GameUI.gLightTexture, m_GameEnvironment.harmZones);
		//check objective 4 and render objective zones
		m_GameObjective.checkObjective4(
			m_GameEnvironment.signalZones,
			m_GameUI.gLightTexture,
			myPlayer,
			myAudio
		);

		//Render UI
//		drawUI();
		m_GameUI.drawUI(
			myPlayer,
			m_GameResource,
			m_GameObjective,
			m_GameEnvironment,
			m_GameDialogue,
			myAudio
		);

		//Render crosshair
		m_GameUI.renderCrosshair(myPlayer, mouseX, mouseY);

		//Update animation timer
		m_SpriteSheet.updateAnimation(
			myPlayer,
			myPlayerAnimation,
			m_GameEnvironment.zombies,
			deltaTimer
		);

		//cap frame rate
		m_GameWindows.frameCap(myPlayer);

		//check if end game condition is met
		checkEndGame();

		float offsetX = 0;
		float offsetY = 20;
		float distance = 20.0f;
		double theta = myPlayer.rotation * (M_PI / 180);
		float posX = myPlayer.px + (offsetX * cos(theta) - offsetY * sin(theta));
		float posY = myPlayer.py + (offsetX * sin(theta) + offsetY * cos(theta));

		//Update screen
		SDL_RenderPresent(gRenderer);
	}

	//get backdrop
	SDL_Surface* screencap = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(gRenderer, NULL, SDL_PIXELFORMAT_ARGB8888, screencap->pixels, screencap->pitch);
	m_GameUI.backdrop = SDL_CreateTextureFromSurface(gRenderer, screencap);
	SDL_FreeSurface(screencap);

	StateStruct temp;
	//handle menus
	if (paused)
	{
		temp.StatePointer = Pause;
		g_StateStack.push(temp);
	}
	if (confirmScreen)
	{
		temp.StatePointer = Confirm;
		g_StateStack.push(temp);
	}
	if (endGameScreen)
	{
		temp.StatePointer = EndGame;
		g_StateStack.push(temp);
	}
	if (quit)
	{
		while (!g_StateStack.empty())
		{
			g_StateStack.pop();
		}
	}
}
#pragma endregion

#pragma region Pause_Screen
void handlePauseEvent()
{
	//Poll events
	while (SDL_PollEvent(&event))
	{
		//check events
		switch (event.type)
		{
		case SDL_QUIT: //User hit the X	
			showConfirmScreen(confirmState::QUIT);
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
			if (event.key.keysym.sym == SDLK_ESCAPE) //esc
			{
				paused = false;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			//resume button
			if (buttons[0].checkInside(mouseX, mouseY))
			{
				paused = false;
			}
			//retry button
			if (buttons[1].checkInside(mouseX, mouseY))
			{
				showConfirmScreen(confirmState::RETRY);
			}
			//quit to menu button
			if (buttons[2].checkInside(mouseX, mouseY))
			{
				showConfirmScreen(confirmState::QUIT_TO_MENU);
			}
			break;
		}
	}
}

void Pause()
{
	//pause all playing audios
	Mix_PauseMusic();
	Mix_Pause(-1);

	//show back the cursor
	SDL_ShowCursor(SDL_ENABLE);
	//SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); //set the cursor to center of the window

	//set text positions
	int pausedOffset = SCREEN_HEIGHT / 3.5;
	int pausedX = SCREEN_WIDTH / 2;
	int pausedY = SCREEN_HEIGHT / 2 - pausedOffset;
	int tipsX = SCREEN_WIDTH / 2;
	int tipsY = pausedY + SCREEN_HEIGHT / 5;

	//add buttons
	//resume button
	int buttonpy = tipsY + 75;
	myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Resume", m_GameResource.regularFont);
	buttons.push_back(myButton);
	//retry button
	buttonpy += 75;
	myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Retry", m_GameResource.regularFont);
	buttons.push_back(myButton);
	//quit to menu button
	buttonpy += 75;
	myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Quit to menu", m_GameResource.regularFont);
	buttons.push_back(myButton);

	//set tips
	std::string fullTips;
	m_GameDialogue.dialogueTips.currentLine = GetRandomInt(0, m_GameDialogue.tipsLine.size() - 2, 1);
	fullTips = "Tips: " + m_GameDialogue.tipsLine[m_GameDialogue.dialogueTips.currentLine];

	while (paused && !confirmScreen)
	{
		deltaTimer.tick();
		mouses = SDL_GetMouseState(&mouseX, &mouseY);
		handlePauseEvent();

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		//Render backdrop
		SDL_RenderCopy(gRenderer, m_GameUI.backdrop, NULL, NULL);

		//Render black overlay 
		m_GameUI.gWhiteTexture.setColor(0, 0, 0, 175);
		m_GameUI.gWhiteTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		//Render paused text
		drawText(pausedX, pausedY, m_GameResource.boldFontTitle, m_GameResource.UIColor, "Paused", 1);

		//Render tips
		drawText(tipsX, tipsY, m_GameResource.regularFontSmall, m_GameResource.UIColor, fullTips, 1);

		//Render buttons
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].checkButton(mouses, mouseX, mouseY);
			buttons[i].render(gRenderer);
		}

		//Update screen
		SDL_RenderPresent(gRenderer);

		m_GameWindows.frameCap(myPlayer);
	}
	//resume all paused audios
	Mix_ResumeMusic();
	Mix_Resume(-1);

	//remove all buttons
	buttons.clear();

	m_GameWindows.clearScreen();

	StateStruct temp;
	if (confirmScreen)
	{
		temp.StatePointer = Confirm;
		g_StateStack.push(temp);
	}
	else
	{
		g_StateStack.pop();
	}
}
#pragma endregion

#pragma region Confirm_Screen
void showConfirmScreen(confirmState m)
{
	confirmScreen = true;
	confirmMode = m;
}

void hideConfirmScreen()
{
	confirmScreen = false;
	confirmMode = confirmState::FALSE;
	g_StateStack.pop();
}

void handleConfirmEvent(int& choice)
{
	//Poll events
	while (SDL_PollEvent(&event))
	{
		//check events
		switch (event.type)
		{
		case SDL_QUIT: //User hit the X
			choice = 2;
			//confirmMode = confirmState::QUIT;
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
			if (event.key.keysym.sym == SDLK_ESCAPE) //esc
			{
				choice = 1;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			//yes button
			if (buttons[0].checkInside(mouseX, mouseY))
			{
				choice = 0;
			}
			//no button
			if (buttons[1].checkInside(mouseX, mouseY))
			{
				choice = 1;
			}
			break;
		}
	}
}

void Confirm()
{
	//pause all playing audios
	Mix_PauseMusic();
	Mix_Pause(-1);

	//show back the cursor
	SDL_ShowCursor(SDL_ENABLE);
	//SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); //set the cursor to center of the window

	//set text positions
	int textOffset = SCREEN_HEIGHT / 10;
	int textX = SCREEN_WIDTH / 2;
	int textY = SCREEN_HEIGHT / 2 - textOffset;

	//add buttons
	//yes button
	int buttonpy = textY + 75;
	myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Yes", m_GameResource.regularFont);
	buttons.push_back(myButton);
	//no button
	buttonpy += 75;
	myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "No", m_GameResource.regularFont);
	buttons.push_back(myButton);

	int choice = -1; //0 for yes, 1 for no

	while (choice == -1)
	{
		deltaTimer.tick();
		mouses = SDL_GetMouseState(&mouseX, &mouseY);
		handleConfirmEvent(choice);

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		//Render backdrop
		SDL_RenderCopy(gRenderer, m_GameUI.backdrop, NULL, NULL);

		//Render black overlay 
		m_GameUI.gWhiteTexture.setColor(0, 0, 0, 175);
		m_GameUI.gWhiteTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		std::string confirmText = "";
		//Render text
		switch (confirmMode)
		{
		case confirmState::RETRY:
			confirmText = "Are you sure you want to retry the level?";
			break;
		case confirmState::QUIT:
			confirmText = "Are you sure you want to quit?";
			break;
		case confirmState::QUIT_TO_MENU:
			confirmText = "Are you sure you want to quit to menu?";
			break;
		}
		drawText(textX, textY, m_GameResource.boldFontLarge, m_GameResource.UIColor, confirmText, 1);

		//Render buttons
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].checkButton(mouses, mouseX, mouseY);
			buttons[i].render(gRenderer);
		}

		//Update screen
		SDL_RenderPresent(gRenderer);

		m_GameWindows.frameCap(myPlayer);
	}

	//resume all paused audios
	Mix_ResumeMusic();
	Mix_Resume(-1);

	//remove all buttons
	buttons.clear();

	m_GameWindows.clearScreen();

	StateStruct temp;
	switch (choice)
	{
	case 0:
		if (confirmMode == confirmState::RETRY) //retry
		{
			hideConfirmScreen();
			initedLevel = false;
			paused = false;
			g_StateStack.pop();
		}
		if (confirmMode == confirmState::QUIT) //quit
		{
			temp.StatePointer = Exit;
			g_StateStack.push(temp);
		}
		if (confirmMode == confirmState::QUIT_TO_MENU) //quit to menu
		{
			g_StateStack.swap(emptyStack);
			temp.StatePointer = Menu;
			g_StateStack.push(temp);
		}
		break;
	case 1:
		hideConfirmScreen();
		break;
	case 2:
		hideConfirmScreen();
		showConfirmScreen(confirmState::QUIT);
		temp.StatePointer = Confirm;
		g_StateStack.push(temp);
	}
}
#pragma endregion

#pragma region End_Game_Screen
void showEndGamecreen(endState m)
{
	endGameScreen = true;
	endGameMode = m;
}

void hideEndGameScreen()
{
	endGameScreen = false;
	endGameMode = endState::FALSE;
	paused = false;
	confirmScreen = false;
	g_StateStack.pop();
}

void handleEndGameEvent(int& choice)
{
	//Poll events
	while (SDL_PollEvent(&event))
	{
		//check events
		switch (event.type)
		{
		case SDL_QUIT: //User hit the X
			choice = 2;
			//confirmMode = confirmState::QUIT;
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
			//retry button
			if (buttons[0].checkInside(mouseX, mouseY))
			{
				choice = 0;
			}
			//quit to menu button
			if (buttons[1].checkInside(mouseX, mouseY))
			{
				choice = 1;
			}
			break;
		}
	}
}

void EndGame()
{
	//pause all playing audios
	Mix_PauseMusic();
	Mix_Pause(-1);
	switch (endGameMode)
	{
	case endState::WIN:
		myAudio.playGameWin();
		break;
	case endState::LOSE:
		myAudio.playGameLose();
		break;
	case endState::TIME_OVER:
		myAudio.playGameLose();
		break;
	}

	//show back the cursor
	SDL_ShowCursor(SDL_ENABLE);
	//SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); //set the cursor to center of the window

	//set text positions
	int textOffset = SCREEN_HEIGHT / 5;
	int textX = SCREEN_WIDTH / 2;
	int textY = SCREEN_HEIGHT / 2 - textOffset;
	int tipsX = SCREEN_WIDTH / 2;
	int tipsY = textY + SCREEN_HEIGHT / 5;

	//add buttons
	//yes button
	int buttonpy = tipsY + 75;
	myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Retry", m_GameResource.regularFont);
	buttons.push_back(myButton);
	//no button
	buttonpy += 75;
	myButton.init(SCREEN_WIDTH / 2, buttonpy, 50, "Quit to menu", m_GameResource.regularFont);
	buttons.push_back(myButton);

	int choice = -1; //0 for retry, 1 for quit to menu

	//set tips
	std::string fullTips;
	m_GameDialogue.dialogueTips.currentLine = GetRandomInt(0, m_GameDialogue.tipsLine.size() - 2, 1);
	fullTips = "Tips: " + m_GameDialogue.tipsLine[m_GameDialogue.dialogueTips.currentLine];

	while (choice == -1)
	{
		deltaTimer.tick();
		mouses = SDL_GetMouseState(&mouseX, &mouseY);
		handleConfirmEvent(choice);

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);

		//Render backdrop
		SDL_RenderCopy(gRenderer, m_GameUI.backdrop, NULL, NULL);

		std::string endGameText = "";
		SDL_Color endGameColor = { 255, 255, 255 };
		//Render text
		switch (endGameMode)
		{
		case endState::WIN:
			m_GameUI.gWhiteTexture.setColor(0, 100, 0, 175);
			endGameText = "You win!";
			endGameColor = { 0, 200, 0 };
			break;
		case endState::LOSE:
			m_GameUI.gWhiteTexture.setColor(100, 0, 0, 175);
			endGameText = "You died!";
			endGameColor = { 255, 0, 0 };
			break;
		case endState::TIME_OVER:
			m_GameUI.gWhiteTexture.setColor(100, 0, 0, 175);
			endGameText = "Time over!";
			endGameColor = { 255, 0, 0 };
			break;
		}
		//Render overlay 
		m_GameUI.gWhiteTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		//Render text
		drawText(textX, textY, m_GameResource.boldFontTitle, endGameColor, endGameText, 1);

		//Render tips
		drawText(tipsX, tipsY, m_GameResource.regularFontSmall, m_GameResource.UIColor, fullTips, 1);

		//Render buttons
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].checkButton(mouses, mouseX, mouseY);
			buttons[i].render(gRenderer);
		}

		//Update screen
		SDL_RenderPresent(gRenderer);

		m_GameWindows.frameCap(myPlayer);
	}

	//resume all paused audios
	Mix_ResumeMusic();
	Mix_Resume(-1);

	//remove all buttons
	buttons.clear();

	m_GameWindows.clearScreen();

	StateStruct temp;
	switch (choice)
	{
	case 0: //retry		
		hideEndGameScreen();
		initedLevel = false;
		break;
	case 1: //quit to menu
		hideEndGameScreen();
		showConfirmScreen(confirmState::QUIT_TO_MENU);
		temp.StatePointer = Confirm;
		g_StateStack.push(temp);
		break;
	case 2: //pressed exit
		hideEndGameScreen();
		showConfirmScreen(confirmState::QUIT);
		temp.StatePointer = Confirm;
		g_StateStack.push(temp);
	}
}
#pragma endregion

#pragma region Exit
void close()
{
	//Free static textures and vectors
	m_GameEnvironment.close();

	//Free loaded UI textures
	m_GameUI.close();

	//free backdrop
	SDL_DestroyTexture(m_GameUI.backdrop);

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	m_GameResource.close();
	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	g_StateStack.swap(emptyStack);
}

void Exit()
{
	close();
}
#pragma endregion

#pragma region Main
int execute(int argc, char* argv[])
{
	srand((unsigned)time(0)); //random seed

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//start the timers
			systemTimer.tick();

			// Our game loop is just a while loop that breaks when our state stack is empty. //
			while (!g_StateStack.empty())
			{
				g_StateStack.top().StatePointer();
			}
		}

		return 0;
	}
}
#pragma endregion
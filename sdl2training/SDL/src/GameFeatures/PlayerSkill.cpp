#pragma once
#include "Include/PlayerSkill.h"
#include "SDL.h"

#pragma region Player Skill
void playerSkill::initPlayer(player& myPlayer)
{
	COOLDOWN_TIME_STEP = 0.0f;
	COOLDOWN_TIME_COUNTER = COOLDOWN_TIME_INTERVAL;
	myPlayer.skill = SCREEN_WIDTH / 5;

	//set up Dominus Shield
	myDominus.initPlayer();

	//set up 6 Sand Soldiers for Emperor Divide
	myEmperorDivide.clear();
	for (int i = 0; i < 6; i++)
	{
		emperorDivide soldier;
		soldier.initPlayer();
		myEmperorDivide.push_back(soldier);
	}

	//set up 1 Nyan Cat
	myCat.initPlayer();
}
void playerSkill::setAnimation(
	std::map<playerSkillState, LTexture>& gPlayerSkillTexture,
	std::map<playerSkillState, std::vector <SDL_Rect>>& gPlayerSkillClips
)
{
	//Dominus
	myDominus.currentTotalFrame = 1;
	myDominus.setAnimation(gPlayerSkillTexture[playerSkillState::DOMINUS],
		gPlayerSkillClips[playerSkillState::DOMINUS][myDominus.currentFrame]);

	//Emperor Divide
	for (auto& soldier : myEmperorDivide)
	{
		soldier.currentTotalFrame = PLAYER_EMPEROR_DIVIDE_ANIMATION_FRAMES;
		soldier.setAnimation(gPlayerSkillTexture[playerSkillState::EMPEROR_DIVIDE],
			gPlayerSkillClips[playerSkillState::EMPEROR_DIVIDE][soldier.currentFrame]);
	}

	//Call Of The Forge God
	myCat.currentTotalFrame = PLAYER_CALL_OF_THE_FORGE_GOD_ANIMATION_FRAMES;
	myCat.setAnimation(gPlayerSkillTexture[playerSkillState::CALL_OF_THE_FORGE_GOD],
		gPlayerSkillClips[playerSkillState::CALL_OF_THE_FORGE_GOD][myCat.currentFrame]);
}
void playerSkill::updateAnimation()
{
	//Dominus
	myDominus.currentFrame = 0;

	//Emperor Divide
	for (auto& soldier : myEmperorDivide)
	{
		soldier.currentFrame++;
		if (soldier.currentFrame > soldier.currentTotalFrame - 1)
		{
			soldier.currentFrame = 0;
		}
	}

	//Call Of The Forge God
	myCat.currentFrame++;
	if (myCat.currentFrame > myCat.currentTotalFrame - 1)
	{
		myCat.currentFrame = 0;
	}
}

bool playerSkill::initSkill(player& myPlayer)
{
	if (COOLDOWN_TIME_COUNTER < COOLDOWN_TIME_INTERVAL) return false;
	Sound::GetInstance()->playSkillActivation();

	COOLDOWN_TIME_COUNTER = 0.0f;//set skill cooldown time counter to zero
	myPlayer.skill = 0; // set player cooldown time bar to 0
	
	//switch skill based on current weapon
	switch (myPlayer.currentWeapon)
	{
	case 0:// pistol
		currentState = playerSkillState::DOMINUS;
		break;
	case 1:// heavy cannon
		currentState = playerSkillState::EMPEROR_DIVIDE;
		break;
	case 2:// chaingun
		currentState = playerSkillState::CALL_OF_THE_FORGE_GOD;
		break;
	default:
		currentState = playerSkillState::CALL_OF_THE_FORGE_GOD;
		break;
	}

	//set up skill based on current skill
	Sound::GetInstance()->playSkillSfx(myPlayer.currentWeapon);
	switch (currentState)
	{
	case playerSkillState::DOMINUS:
		initDominus(myPlayer);
		break;
	case playerSkillState::EMPEROR_DIVIDE:
		initEmperorDivide(myPlayer);
		break;
	case playerSkillState::CALL_OF_THE_FORGE_GOD:
		initCallOfTheForgeGod(myPlayer);
		break;
	default:
		initCallOfTheForgeGod(myPlayer);
		break;
	}
	return true;
}
void playerSkill::cooldownSkill(player& myPlayer)
{
	COOLDOWN_TIME_COUNTER += deltaTimer.getDeltaTime();
	if (COOLDOWN_TIME_COUNTER > COOLDOWN_TIME_INTERVAL)
	{
		COOLDOWN_TIME_COUNTER = COOLDOWN_TIME_INTERVAL;
	}

	//when cooldown time reach a step, increase player skill time,
	COOLDOWN_TIME_STEP += deltaTimer.getDeltaTime();
	if (COOLDOWN_TIME_STEP >= (COOLDOWN_TIME_INTERVAL / float(SCREEN_WIDTH / 5.0f)))
	{
		COOLDOWN_TIME_STEP = 0.0f;
		myPlayer.skill = myPlayer.skill + (myPlayer.skill >= SCREEN_WIDTH / 5 ? 0 : 1);

	}
}
void playerSkill::activateSkill(player& myPlayer)
{
	if (COOLDOWN_TIME_COUNTER >= COOLDOWN_TIME_INTERVAL) return;
	switch (currentState)
	{
	case playerSkillState::DOMINUS:
		activateDominus(myPlayer);
		break;
	case playerSkillState::EMPEROR_DIVIDE:
		activateEmperorDivide(myPlayer);
		break;
	case playerSkillState::CALL_OF_THE_FORGE_GOD:
		activateCallOfTheForgeGod(myPlayer);
		break;
	default:
		break;
	}
}

#pragma region Dominus
void playerSkill::initDominus(player& myPlayer)
{
	myDominus.px = myPlayer.px;
	myDominus.py = myPlayer.py;
	myDominus.lifeTimeCounter = 0.0f;
}
void playerSkill::activateDominus(player& myPlayer)
{
	myDominus.move();
	myDominus.updateRenderPosition();
	myDominus.render(camera);
}
#pragma endregion

#pragma region Emperor Divide
void playerSkill::initEmperorDivide(player& myPlayer)
{
	for (auto& soldier : myEmperorDivide)
	{
		int mouseX, mouseY;
		// Get mouse position
		SDL_GetMouseState(&mouseX, &mouseY);

		soldier.isFlipped = (mouseX < SCREEN_WIDTH / 2);

		soldier.rotation = myPlayer.rotation;
	}
	float i = -2.5f;
	float step = 48.0f;
	for (auto& soldier : myEmperorDivide)
	{
		soldier.calPosition(myPlayer, i * step);
		i += 1.0f;
	}
	for (auto& soldier : myEmperorDivide)
	{
		soldier.lifeTimeCounter = 0.0f;
		soldier.entranceTimeCounter = 0.0f;
		soldier.moveTimeCounter = 0.0f;
	}
	//for (auto& soldier : myEmperorDivide)
	//{
	//	soldier.vx = myPlayer.vx;
	//	soldier.vy = myPlayer.vy;
	//}
}
void playerSkill::activateEmperorDivide(player& myPlayer)
{
	bool isReady = true;
	for (auto& soldier : myEmperorDivide)
	{
		if (soldier.lifeTimeCounter >= soldier.lifeTimeInterval)
		{
			isReady = false;
			soldier.px = LEVEL_WIDTH * 2;
			soldier.py = LEVEL_WIDTH * 2;
			soldier.updateRenderPosition();
			soldier.render(camera);
		}
	}

	if (isReady)
	{
		//printf("ACTIVATE -> EMPEROR DIVIDE\n");
		for (auto& soldier : myEmperorDivide)
		{
			soldier.move();
			soldier.updateRenderPosition();
			soldier.render(camera);
		}
	}
}
#pragma endregion

#pragma region Call_Of_The_Forge_God
void playerSkill::initCallOfTheForgeGod(player& myPlayer)
{
	myPlayer.isActive = 0;
	myCat.rotation = myPlayer.rotation;
	myCat.isRecasted = false;
	myCat.calPosition(myPlayer);
	myCat.isFlipped = (myCat.px >= myPlayer.px);
}
void playerSkill::activateCallOfTheForgeGod(player& myPlayer)
{
	myCat.move(myPlayer);
	myCat.updateRenderPosition();
	myCat.render(camera);
}
#pragma endregion

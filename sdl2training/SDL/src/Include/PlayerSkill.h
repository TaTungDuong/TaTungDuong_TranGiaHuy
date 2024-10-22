#pragma once
#include "Include/Global.h"
#include "Include/GameObject.h"
#include "Include/Timer.h"
#include "Sound.h"

#include "Include/Player.h"
#include "Include/PlayerEffect.h"

#include "Include/EmperorDivide.h"
#include "Include/CallOfTheForgeGod.h"

enum class playerSkillState
{
	EMPEROR_DIVIDE,
	CALL_OF_THE_FORGE_GOD
};

//Player Skill
class playerSkill
{
public:
	playerSkillState currentState;

	void initPlayer(player& myPlayer);
	
	//Handle animations
	void setAnimation(
		std::map<playerSkillState, LTexture>& gPlayerSkillTexture,
		std::map<playerSkillState, std::vector <SDL_Rect>>& gPlayerSkillClips
	);
	void updateAnimation();

	void cooldownSkill(player& myPlayer);
	bool initSkill(player& myPlayer);
	void activateSkill(player& myPlayer);

	std::vector<emperorDivide> myEmperorDivide; //store Sand Soldiers
	callOfTheForgeGod myCat; //the cat
private:
	float COOLDOWN_TIME_STEP;

	void initEmperorDivide(player& myPlayer);
	void activateEmperorDivide(player& myPlayer);

	void initCallOfTheForgeGod(player& myPlayer);
	void activateCallOfTheForgeGod(player& myPlayer);
};
#include "GameStateBase.h"
#include "GSIntro.h"
#include "GSIntroMenu.h"
#include "GSMenu.h"
#include "GSIntroCutscene.h"
#include "GSPlay.h"

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		//GSINTRO;
		break;
	case StateType::STATE_INTRO_MENU:
		gs = std::make_shared<GSIntroMenu>();
		//GSINTRO_MENU;
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		//GSMENU
		break;
	case StateType::STATE_INTRO_CUTSCENE:
		gs = std::make_shared<GSIntroCutscene>();
		//GSINTRO_CUTSCENE;
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		//GSPLAY
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}

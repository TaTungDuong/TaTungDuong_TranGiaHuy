#pragma once
#include "Include/Global.h"
#include "Include/Graphics.h"
#include "Include/PopUpText.h"

class GameDialogue
{
public:

#pragma region Dialogues
	std::vector <std::string> dialogueLine; //dialogue texts
	std::vector <std::string> tipsLine; //tips texts
	popUpText dialogue;// (3.0f, 1.0f);
	popUpText dialogueTips;// (3.0f, 2.0f);
#pragma endregion

	GameDialogue();
	bool loadMedia(); // check load medias
	void close(); //free
};


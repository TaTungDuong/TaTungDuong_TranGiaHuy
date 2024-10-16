#pragma once
#include "Include/GameDialogue.h"

GameDialogue::GameDialogue():
	dialogue(3.0f, 1.0f),
	dialogueTips(3.0f, 2.0f)
{

}

bool GameDialogue::loadMedia()
{
	bool success = true;
#pragma region Load_text_line
	//Load dialogues line
	std::string str;
	std::ifstream dialoguesFile("assets-main/resources/dialogues/dialogues.txt");
	if (dialoguesFile.fail()) {
		printf("Failed to load dialogue file!\n");
		success = false;
	}
	else {
		while (std::getline(dialoguesFile, str))
		{
			dialogueLine.push_back(str);
		}
	}

	std::ifstream tipsFile("assets-main/resources/dialogues/tips.txt");
	if (tipsFile.fail()) {
		printf("Failed to load dialogue file!\n");
		success = false;
	}
	else {
		while (std::getline(tipsFile, str))
		{
			tipsLine.push_back(str);
		}
	}
#pragma endregion
	return success;
}

void GameDialogue::close()
{

}
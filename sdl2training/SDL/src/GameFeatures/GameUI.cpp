#pragma once
#include "Include/GameUI.h"

bool GameUI::loadMedia()
{
	//Loading success flag
	bool success = true;

#pragma region Load_static_textures
	if (!gCrosshairTexture.loadFromFile("assets-main/sprites/ui/cursor/crosshair.png"))
	{
		printf("Failed to load player texture!\n");
		success = false;
	}

	if (!gWhiteTexture.loadFromFile("assets-main/sprites/ui/others/white.png"))
	{
		printf("Failed to load white texture!\n");
		success = false;
	}

	if (!gSkillTexture.loadFromFile("assets-main/sprites/ui/others/white.png"))
	{
		printf("Failed to load white texture!\n");
		success = false;
	}

	if (!gMenuTexture.loadFromFile("assets-main/sprites/ui/boot_splash/menu_background.png"))
	{
		printf("Failed to load menu background texture!\n");
		success = false;
	}
#pragma endregion

#pragma region Load_UI_textures
	//Load UI texture
	if (!gHealthIconTexture.loadFromFile("assets-main/sprites/ui/icons/health_icon.png"))
	{
		printf("Failed to load health icon texture!\n");
		success = false;
	}

	if (!gPistolIconTexture.loadFromFile("assets-main/sprites/weapons/shotgun/icon_shotgun.png"))//_white.png"))
	{
		printf("Failed to load pistol icon texture!\n");
		success = false;
	}

	if (!gRifleIconTexture.loadFromFile("assets-main/sprites/weapons/heavy_cannon/icon_heavy_cannon.png"))//_white.png"))
	{
		printf("Failed to load rifle icon texture!\n");
		success = false;
	}
#pragma endregion

#pragma region Load_screen_effect_textures
	//Load screen effect texture
	if (!gVignetteTexture.loadFromFile("assets-main/resources/textures/light/vignette.png"))
//	if (!gVignetteTexture.loadFromFile("assets-main/sprites/ui/others/empty.png"))
	{
		printf("Failed to load vignette texture!\n");
		success = false;
	}

	if (!gLightTexture.loadFromFile("assets-main/resources/textures/light/light_halo.png"))
//	if (!gLightTexture.loadFromFile("assets-main/sprites/ui/others/empty.png"))
	{
		printf("Failed to load light halo texture!\n");
		success = false;
	}

	if (!gLensDirtTexture.loadFromFile("assets-main/resources/textures/overlay/lens_dirt.png"))
//	if (!gLensDirtTexture.loadFromFile("assets-main/sprites/ui/others/empty.png"))
	{
		printf("Failed to load len dirt texture!\n");
		success = false;
	}

//	if (!gBloodOverlayTexture.loadFromFile("assets-main/resources/textures/blood/blood_overlay.png"))
	if (!gBloodOverlayTexture.loadFromFile("assets-main/resources/textures/blood/blood_overlay(1).png"))
	{
		printf("Failed to load blood overlay texture!\n");
		success = false;
	}
#pragma endregion

	return success;
}

void GameUI::renderLighting(GameEnvironment& m_GameEnvironment)
{
//	return;
	//bullet lightings
	///player bullets
	for (int i = 0; i < m_GameEnvironment.bullets.size(); i++)
	{
		int lightSize1 = 750;
		int lightSize2 = 300;
		
		// Get the bullet's position
		float bulletX = m_GameEnvironment.bullets[i].rx;
		float bulletY = m_GameEnvironment.bullets[i].ry;

		// Render the larger, dimmer outer light
		gLightTexture.setColor(200, 150, 0, 100);
		gLightTexture.render(
			camera, 
			bulletX - lightSize1 / 2, 
			bulletY - lightSize1 / 2, 
			lightSize1, lightSize1
		);

		// Render the smaller, brighter inner light
		gLightTexture.setColor(250, 175, 0, 125);
		gLightTexture.render(
			camera, 
			bulletX - lightSize2 / 2, 
			bulletY - lightSize2 / 2, 
			lightSize2, lightSize2
		);
	}
//	return;
	///zombie bullets
	for (int i = 0; i < m_GameEnvironment.zombieBullets.size(); i++)
	{
		int lightSize1 = 90 * m_GameEnvironment.zombieBullets[i].size / 48;
		int lightSize2 = 90 * m_GameEnvironment.zombieBullets[i].size / 48;

		// Get the bullet's position
		float bulletX = m_GameEnvironment.zombieBullets[i].rx - m_GameEnvironment.zombieBullets[i].size / 2;
		float bulletY = m_GameEnvironment.zombieBullets[i].ry - m_GameEnvironment.zombieBullets[i].size / 2;

		// Render the larger, dimmer outer light
		gLightTexture.setColor(225, 80, 0, 100);
		gLightTexture.render(
			camera,
			bulletX,
			bulletY,
			lightSize1, lightSize1
		);
//		continue;
		// Render the smaller, brighter inner light
		gLightTexture.setColor(255, 85, 75, 125);
		gLightTexture.render(
			camera,
			bulletX,
			bulletY,
			lightSize2, lightSize2
		);
	}
}

void GameUI::renderCrosshair(player& myPlayer, int mouseX, int mouseY)
{
	if (myPlayer.currentState == playerState::RELOAD || !myPlayer.myWeapon[myPlayer.currentWeapon].checkAmmo())
	{
		gCrosshairTexture.setColor(150, 150, 150);
	}
	else
	{
		gCrosshairTexture.setColor(255, 255, 255);
	}
	gCrosshairTexture.render(mouseX + CROSSHAIR_SIZE / 2, mouseY + CROSSHAIR_SIZE / 2, CROSSHAIR_SIZE, CROSSHAIR_SIZE);
}

void GameUI::setCamera(SDL_Rect& camera, gameObject target) {
	//Center the camera over the target
	camera.x = int(target.px - SCREEN_WIDTH / 2);
	camera.y = int(target.py - SCREEN_HEIGHT / 2);

	//Keep the camera in bounds.
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void GameUI::drawWeapon(player& myPlayer, GameResource m_GameResource)
{
	//draw weapon icon
	int weaponIconSize = SCREEN_HEIGHT / 5; //TODO: make a switch statement for current weapon here
	int weaponIconX = SCREEN_WIDTH - V_BORDER - weaponIconSize;
	int weaponIconY = SCREEN_HEIGHT - H_BORDER - weaponIconSize;

	switch (myPlayer.currentWeapon)
	{
	case 0:
		gPistolIconTexture.render(weaponIconX, weaponIconY, weaponIconSize, weaponIconSize);
		break;
	case 1:
		gRifleIconTexture.render(weaponIconX, weaponIconY, weaponIconSize, weaponIconSize);
		break;
	}

	//weaponIconTexture.free();

	//draw current weapon's clip size
	int renderedTextWidth;
	int clipSizeX = SCREEN_WIDTH - V_BORDER - weaponIconSize;
	int clipSizeY = int(SCREEN_HEIGHT - H_BORDER - weaponIconSize / 1.5);
	int clipSize = myPlayer.myWeapon[myPlayer.currentWeapon].getClipSize();
	renderedTextWidth = drawText(clipSizeX, clipSizeY, m_GameResource.regularFont, { 128,128,128 }, std::to_string(clipSize), 2);

	//draw current ammo
	int currentAmmoX = int(SCREEN_WIDTH - V_BORDER - weaponIconSize - renderedTextWidth * 1.1);
	int currentAmmoY = int(SCREEN_HEIGHT - H_BORDER - weaponIconSize / 1.5);
	int currentAmmo = myPlayer.myWeapon[myPlayer.currentWeapon].ammo;
	drawText(currentAmmoX, currentAmmoY, m_GameResource.boldFontLarge, m_GameResource.UIColor, std::to_string(currentAmmo), 2);
}

void GameUI::updateObjective(
	GameObjective& m_GameObjective, 
	GameEnvironment& m_GameEnvironment,
	GameDialogue& m_GameDialogue
)
{
	static int spawned = false;

	switch (m_GameObjective.currentObjective)
	{
	case -1: //waiting for first dialogue to finish
		m_GameObjective.objectiveText = "Waiting for objective...";
//		m_GameObjective.checkPreObjective();
		if (m_GameDialogue.dialogue.currentPart == 1)
		{
			m_GameObjective.currentObjective++;
		}
		break;
	case 0: //objective 1: (tutorial): press w,a,s,d
		m_GameObjective.objectiveText = "Move around the area by pressing W, A, S, D";
		break;
	case 1: //objective 2: (tutorial): shoot gun
		m_GameObjective.objectiveText = "Shoot your gun by pressing Left Mouse Button";
		break;
	case 2: //objective 3: (tutorial): reload gun
		m_GameObjective.objectiveText = "Activate the skill by pressing R";
		break;
	case 3: //objective 4: kill required amount of zombies (tutorial ended, zombie start spawning now)
		m_GameObjective.objectiveText = "Kill " 
			+ std::to_string(ZOMBIE_NEEDED_TO_KILL) + " enemies, " 
			+ std::to_string(ZOMBIE_NEEDED_TO_KILL - m_GameObjective.obj_zombieKilled) 
			+ "/" + std::to_string(ZOMBIE_NEEDED_TO_KILL) + " left";
		//spawn zombie
		if (!spawned)
		{
			m_GameEnvironment.canSpawnZombie = true;
			spawned = true;
		}
		break;
	case 4: //objective 5: destroy 5 signals
		m_GameObjective.objectiveText = "Destroy all the signals, " 
			+ std::to_string(m_GameObjective.obj_zones) + "/" + std::to_string(TOTAL_SIGNAL_ZONE) + " left";
		break;

	case TOTAL_OBJECTIVE: //objective 5: All objective finished
		m_GameObjective.objectiveText = "Survive!";
		break;
	}

	//if dialogue haven't finish
	if (m_GameObjective.objective[m_GameObjective.currentObjective]
		&& m_GameDialogue.dialogue.currentPart == m_GameObjective.currentObjective + 1
		&& m_GameObjective.currentObjective < TOTAL_OBJECTIVE)
	{
		m_GameObjective.objectiveText = "Waiting for objective...";
	}
}
void GameUI::drawObjective(
	GameResource& m_GameResource,
	GameObjective& m_GameObjective,
	GameEnvironment& m_GameEnvironment,
	GameDialogue& m_GameDialogue
)
{
	updateObjective(
		m_GameObjective,
		m_GameEnvironment,
		m_GameDialogue
	);

	//draw the text "Objective"
	int renderedTextWidth;
	int objectiveTextX = V_BORDER;
	int objectiveTextY = H_BORDER;
	renderedTextWidth = drawText(objectiveTextX, objectiveTextY, m_GameResource.boldFont, m_GameResource.UIColor, "Objective: ", 0);

	//draw objectives
	int objectiveX = int(V_BORDER + renderedTextWidth * 1.05);
	int objectiveY = objectiveTextY;
	drawText(objectiveX, objectiveY, m_GameResource.regularFont, m_GameResource.UIColor, m_GameObjective.objectiveText, 0);
	if (m_GameObjective.currentObjective == 4)
	{
		for (int i = 0; i < m_GameEnvironment.signals.size(); i++)
		{
			if (m_GameEnvironment.signals[i].health > 0)
			{
				std::string signalPosition = "[+] : [X = " + std::to_string(int(m_GameEnvironment.signalZones[i].px))
					+ ", Y = " + std::to_string(int(m_GameEnvironment.signalZones[i].py)) + "]";
				drawText(objectiveTextX, objectiveY + 32 * (i + 1),
					m_GameResource.regularFont, m_GameResource.UIColor, signalPosition, 0);
			}
		}
	}
}
void GameUI::drawTimer(GameResource& m_GameResource, GameObjective& m_GameObjective)
{
	static float timeCounter = 0;
	//calulate countdown time
	if (!systemTimer.isPaused() && !m_GameObjective.tutorial && m_GameObjective.timeLeft > 0)
	{
		timeCounter += systemTimer.getDeltaTime();
	}

	if (timeCounter >= 1)
	{
		m_GameObjective.timeLeft -= 1;
		timeCounter = 0;
	}

	//format time
	int m;
	int s;
	s = m_GameObjective.timeLeft % 60;
	m = m_GameObjective.timeLeft / 60;
	if (s == 60)
	{
		s = 0;
	}

	char timerText[20] = "tutorial section";
	if (!m_GameObjective.tutorial)
	{
		sprintf_s(timerText, "%02i:%02i", m, s);
	}

	//draw timer
	int renderedTextWidth;
	int timerX = SCREEN_WIDTH - V_BORDER;
	int timerY = H_BORDER;
	renderedTextWidth = drawText(timerX, timerY, m_GameResource.regularFont, m_GameResource.UIColor, timerText, 2); //TODO: change to actual timer with format

	//draw the text "Time Left"
	int timerTextX = int(SCREEN_WIDTH - V_BORDER - renderedTextWidth * 1.1);
	int timerTextY = timerY;
	drawText(timerTextX, timerTextY, m_GameResource.boldFont, m_GameResource.UIColor, "Time Left: ", 2);
}
void GameUI::drawPosition(player& myPlayer, GameResource& m_GameResource, GameObjective& m_GameObjective)
{
	//draw the text Position of the player
	int positionTextX = int(SCREEN_WIDTH - V_BORDER);
	int positionTextY = H_BORDER + 32;
	std::string myPosition = "[X:" + std::to_string(int(myPlayer.px)) + ", Y:" + std::to_string(int(myPlayer.py)) + "]";
	drawText(positionTextX, positionTextY, m_GameResource.boldFont, m_GameResource.UIColor, myPosition, 2);
}

void GameUI::drawHealth(player& myPlayer, GameResource& m_GameResource)
{
	//set health to 0 if it drop below 0
	if (myPlayer.health < 0)
	{
		myPlayer.health = 0;
	}

	//size of icons
	int healthBarWidth = map(myPlayer.health, 0, 100, 0, SCREEN_WIDTH / 5); //map player's current health to the health bar width
	int healthBarHeight = SCREEN_HEIGHT / 100;
	int healthIconSize = SCREEN_HEIGHT / 20;

	//position of icons
	int healthBarOffset = SCREEN_HEIGHT / 20;
	int healthBarX = V_BORDER;
	int healthBarY = SCREEN_HEIGHT - H_BORDER - healthBarOffset;
	int healthIconX = int(V_BORDER * 1.25);
	int healthIconY = healthBarY - healthBarHeight - healthIconSize;
	int healthX = int(healthIconX + healthIconSize * 1.5);
	int healthY = healthIconY;

	//draw heath icon
	gHealthIconTexture.render(healthIconX, healthIconY, healthIconSize, healthIconSize);

	//draw heath
	drawText(healthX, healthY, m_GameResource.boldFont, m_GameResource.UIColor, std::to_string(int(myPlayer.health)), 0);

	//draw heath bar
	gWhiteTexture.setColor(255, 255, 255, 255);
	gWhiteTexture.render(healthBarX, healthBarY, healthBarWidth, healthBarHeight);
}
void GameUI::drawSkill(GameResource& m_GameResource)
{
	//set cooldown time counter to max
	if (COOLDOWN_TIME_COUNTER > COOLDOWN_TIME_INTERVAL)
	{
		COOLDOWN_TIME_COUNTER = COOLDOWN_TIME_INTERVAL;
	}

	//size of icons
	int skillBarWidth = map(myPlayer.skill, 0, SCREEN_WIDTH / 5, 0, SCREEN_WIDTH / 5); //map player's current skill time to the skill bar width
	int skillBarHeight = SCREEN_HEIGHT / 100;
	int skillIconSize = SCREEN_HEIGHT / 20;
	//printf("-> %d, %d\n", map(myPlayer.skill, 0, SCREEN_WIDTH / 5, 0, SCREEN_WIDTH / 5), myPlayer.skill);

	//position of icons
	int skillBarOffset = SCREEN_HEIGHT / 20;
	int skillBarX = V_BORDER;
	int skillBarY = SCREEN_HEIGHT - H_BORDER - skillBarOffset + 32;
	int skillIconX = int(V_BORDER * 1.25);
	int skillIconY = skillBarY - skillBarHeight - skillIconSize;
	int skillX = int(skillIconX + skillIconSize * 1.5);
	int skillY = skillIconY;

	//draw heath icon
	//gHealthIconTexture.render(skillIconX, skillIconY, skillIconSize, skillIconSize);

	//draw text
	//drawText(skillX, skillY, m_GameResource.boldFont, m_GameResource.UIColor, std::to_string(int(myPlayer.health)), 0);

	//draw skill bar
	gSkillTexture.setColor(255, 255, 255, 255);
	gSkillTexture.render(skillBarX, skillBarY, skillBarWidth, skillBarHeight);
}
void GameUI::drawDialogue(
	GameResource& m_GameResource,
	GameObjective& m_GameObjective,
	GameDialogue& m_GameDialogue
)
{
	static std::string fullDialogue;
	if (m_GameDialogue.dialogue.check())
	{
		if (!m_GameDialogue.dialogue.onScreen())
		{
			m_GameDialogue.dialogue.setFlag(true);
			fullDialogue = " ";

			//check if current line reached end of part of the dialogue
			if (m_GameDialogue.dialogue.currentLine < m_GameDialogue.dialogueLine.size() &&
				m_GameDialogue.dialogueLine[m_GameDialogue.dialogue.currentLine] == "//end part//")
			{
				m_GameDialogue.dialogue.currentLine += 1;
				m_GameDialogue.dialogue.currentPart++;
			}

			if (m_GameObjective.currentObjective != TOTAL_OBJECTIVE)
			{
				//dialogue part for next object when current objective is finished (or when the game just start and dialogue 1 havent be finished)
				if (m_GameObjective.objective[m_GameObjective.currentObjective]
					&& m_GameDialogue.dialogue.currentPart == m_GameObjective.currentObjective + 1
					|| m_GameObjective.currentObjective == -1 && m_GameDialogue.dialogue.currentPart == 0)
				{
					if (m_GameDialogue.dialogue.currentLine < m_GameDialogue.dialogueLine.size())
					{
						fullDialogue = "Luxon: " 
							+ m_GameDialogue.dialogueLine[m_GameDialogue.dialogue.currentLine];
						m_GameDialogue.dialogue.currentLine++;
						Sound::GetInstance()->playRadio();
					}
				}
				else if (m_GameObjective.objective[m_GameObjective.currentObjective]
					&& m_GameDialogue.dialogue.currentPart == m_GameObjective.currentObjective + 2)
				{
					m_GameObjective.currentObjective++;
				}
			}
		}

		//draw dialogue
		int dialogueOffset = SCREEN_HEIGHT / 10;
		int dialogueX = SCREEN_WIDTH / 2;
		int dialogueY = SCREEN_HEIGHT - H_BORDER - dialogueOffset;
		drawText(dialogueX, dialogueY, m_GameResource.regularFont, m_GameResource.UIColor, fullDialogue, 1);
	}
}
void GameUI::drawUI(
	player& myPlayer,
	GameResource& m_GameResource,
	GameObjective& m_GameObjective,
	GameEnvironment& m_GameEnvironment,
	GameDialogue& m_GameDialogue
)
{
	//Render screen effect
	//color filter
	gWhiteTexture.setColor(75, 100, 200, 50);
	gWhiteTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//vignette effect
	int healthColor = int((255 - map(myPlayer.health, 0, 100, 0, 255)) * 0.2);
	gVignetteTexture.setColor(healthColor, 0, 0);
	gVignetteTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//lens dirt effect
	gLensDirtTexture.setColor(255, unsigned char(255 - healthColor), unsigned char(255 - healthColor), 25);
	gLensDirtTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//blood overlay effect
	gBloodOverlayTexture.setColor(255, 255, 255, unsigned char(healthColor));
	gBloodOverlayTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	drawWeapon(myPlayer, m_GameResource);
	updateObjective(
		m_GameObjective,
		m_GameEnvironment,
		m_GameDialogue
	);
	drawObjective(
		m_GameResource,
		m_GameObjective,
		m_GameEnvironment,
		m_GameDialogue
	);
	drawTimer(m_GameResource, m_GameObjective);
	drawPosition(
		myPlayer,
		m_GameResource, 
		m_GameObjective
	);
	drawHealth(myPlayer, m_GameResource);
	drawSkill(m_GameResource);
	drawDialogue(
		m_GameResource,
		m_GameObjective,
		m_GameDialogue
	);
/*
	if (cheat)
	{
		drawText(SCREEN_WIDTH / 2, H_BORDER, m_GameResource.boldFontSmall, m_GameResource.UIColor, "cheat mode: on", 1);
	}
*/
}

void GameUI::close()
{
	//free static textures
	gWhiteTexture.free();
	gMenuTexture.free();
	//Free loaded UI textures
	gHealthIconTexture.free();
	gPistolIconTexture.free();
	gRifleIconTexture.free();
	gCrosshairTexture.free();

	//Free loaded screen effect textures
	gVignetteTexture.free();
	gLightTexture.free();
	gLensDirtTexture.free();
	gBloodOverlayTexture.free();

	//free backdrop
	SDL_DestroyTexture(backdrop);
}

#pragma once
#include "SDL_mixer.h"
#include <string.h>
#include <map>
#include "Singleton.h"

#include "Include/GameObject.h"

class Sound :public CSingleton<Sound>
{
public:
	Sound();
	~Sound();
	bool Init();
	void PlaySound(const std::string& name, int loop);
	void PauseSound();
	void ResumeSound();
	void StopSound();
	void LoadSound(const std::string& name);
	void LoadSfx(const std::string& name);
	void PlaySfx(const std::string& name, int repeat = 0);
	void CleanUp();

	//Bgm
	void playMenuMusic();
	void playStoryMusic();
	void playMainMusic();
	void playBossMusic();
	void playGameLose();
	void playGameWin();

	//Voicelines
	void playVoiceIntro(int voiceline);

	//Sfx
	void playBackgroundLoop();
	void stopBackgroundLoop();
	void playRadio();
	void playPlayerHurt();
	void playHitTree();
	void playReload();
	void stopReload();
	void playSpawnSignal();
	void playCollectObject();
	void playDrinkMilk();
	void playExplosion();
	void playZombieAttack();
	void playZombieShoot();
	void playHitZombie();
	void playZombieDie();
	void playGunshot();
	void playSwapWeapon();
	void playGunEmpty();
	void playSkillActivation();
	void playSkillSfx(int weapon);
	void playGlassBreak();
	void playWardenDive(int direction);

private:
	//Bgm
	const std::string p_MenuMusic = "bgm/blue.mp3";
	const std::string p_MainMusic = "bgm/silence.mp3";
	const std::string p_BossMusic = "bgm/crypt.mp3";
	const std::string p_StoryMusic = "bgm/control.mp3";
	//Voicelines
	const std::string p_VoiceIntro[2] = { 
		"voicelines/intro.mp3", 
		"voicelines/intro_2.mp3" 
	};
	
	//Sfx
	const std::string p_Radio = "sfx/objects/radio_beep.mp3";
	const std::string p_GunEmpty = "sfx/weapons/gun_empty.mp3";
	const std::string p_Reload = "sfx/weapons/reload.mp3";
	const std::string p_SwapWeapon = "sfx/weapons/weapon.mp3";
	const std::string p_Walk = "sfx/player/walk.mp3";
	const std::string p_HitTree = "sfx/objects/hit_tree.mp3";
	const std::string p_SpawnSignal = "sfx/objects/big_chest.mp3";
	const std::string p_CollectObject = "sfx/objects/collect_object.mp3";
	const std::string p_DrinkMilk = "sfx/effects/drink.mp3";
	const std::string p_Explosion = "sfx/effects/explosion.mp3";
	const std::string p_PlayerHit = "sfx/player/hurt.mp3";
	const std::string p_GameLose = "sfx/effects/game_lose.wav";
	const std::string p_GameWin = "sfx/effects/game_win.wav";
	const std::string p_GunShot[3] = {
		"sfx/weapons/gunshot(1).mp3",
		"sfx/weapons/gunshot(2).mp3",
		"sfx/weapons/gunshot(3).mp3"
	};
	std::string p_ZombieAttack[7] = {
		"sfx/npcs/zombie_attack(1).mp3",
		"sfx/npcs/zombie_attack(2).mp3",
		"sfx/npcs/zombie_attack(3).mp3",
		"sfx/npcs/zombie_attack(4).mp3",
		"sfx/npcs/zombie_attack(5).mp3",
		"sfx/npcs/zombie_attack(6).mp3",
		"sfx/npcs/zombie_attack(7).mp3"
	};
	std::string p_ZombieHit[4] = {
		"sfx/npcs/hit_zombie(1).wav",
		"sfx/npcs/hit_zombie(2).wav",
		"sfx/npcs/hit_zombie(3).wav",
		"sfx/npcs/hit_zombie(4).wav"
	};
	const std::string p_ZombieShoot = "sfx/npcs/enemy_shoot.mp3";
	const std::string p_ZombieDie = "sfx/npcs/enemy_die.mp3";
	const std::string p_PlayerSkill = "sfx/skills/_skill.mp3";
	const std::string p_Dominus = "sfx/skills/dominus.mp3";
	const std::string p_EmperorDivide = "sfx/skills/emperor_divide.mp3";
	const std::string p_CallOfTheForgeGod = "sfx/skills/call_of_the_forge_god.mp3";

	const std::string p_WardenDive1 = "sfx/npcs/enemy_dive_1.mp3";
	const std::string p_WardenDive2 = "sfx/npcs/enemy_dive_2.mp3";

	const std::string p_GlassBreak[3] = {
		"sfx/objects/glass_break(1).mp3",
		"sfx/objects/glass_break(2).mp3",
		"sfx/objects/glass_break(3).mp3"
	};

	//Fixed channel for some sound effect
	const int AMBIENT_CHANNEL = 0;
	const int WALK_CHANNEL = 1;
	const int RELOAD_CHANNEL = 2;
	const int SWAP_WEAPON_CHANNEL = 3;
	const int PLAYER_HURT_CHANNEL = 4;

	//number of variations for some sound effect
	const int PLAYER_HURT_VARIATION = 6;
	const int GUNSHOT_VARIATION = 3;
	const int ZOMBIE_ATTACK_VARIATION = 7;
	const int HIT_ZOMBIE_VARIATION = 4;

	std::string m_PathMusic;
	//Mix_Music* m_Music = NULL;
	std::map< std::string, Mix_Chunk*> m_Sfxs;
	std::map<std::string, Mix_Music*> m_Sounds;
};

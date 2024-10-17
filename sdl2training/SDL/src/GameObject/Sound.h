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
	void PlaySound(const std::string& name);
	void PauseSound();
	void ResumeSound();
	void StopSound();
	void LoadSound(const std::string& name);
	void LoadSfx(const std::string& name);
	void PlaySfx(const std::string& name, int repeat = 0);
	void CleanUp();

	void playMenuMusic();
	void playMainMusic();
	void playBackgroundLoop();
	void stopBackgroundLoop();
	void playRadio();
	void playPlayerHurt();
	void playHitTree();
	void playReload();
	void stopReload();
	void playCollectObject();
	void playDrinkMilk();
	void playGameLose();
	void playGameWin();
	void playZombieAttack();
	void playHitZombie();
	void playGunshot();
	void playSwapWeapon();
	void playGunEmpty();

private:
	//Bgm
	const std::string p_MenuMusic = "bgm/blue.mp3";
	const std::string p_MainMusic = "bgm/silence.mp3";
	//Sfx
	const std::string p_Radio = "sfx/objects/radio_beep.mp3";
	const std::string p_GunEmpty = "sfx/weapons/gun_empty.mp3";
	const std::string p_Reload = "sfx/weapons/reload.mp3";
	const std::string p_SwapWeapon = "sfx/weapons/weapon.mp3";
	const std::string p_Walk = "sfx/player/walk.mp3";
	const std::string p_HitTree = "sfx/objects/hit_tree.mp3";
	const std::string p_CollectObject = "sfx/objects/collect_object.mp3";
	const std::string p_DrinkMilk = "sfx/effects/drink.mp3";
	const std::string p_PlayerHit = "sfx/player/hit.mp3";
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
/*
	//The music that will be played
	Mix_Music* menu_bgm;
	Mix_Music* main_bgm;

	//The sound effects that will be used
	Mix_Chunk* ambient;
	Mix_Chunk* radio;
	Mix_Chunk* walk;
	Mix_Chunk* reload;
	Mix_Chunk* swapWeapon;
	Mix_Chunk* gunEmpty;
	Mix_Chunk* hitTree;
	Mix_Chunk* drinkMilk;
	Mix_Chunk* collectObject;
	Mix_Chunk* gameLose;
	Mix_Chunk* gameWin;
	std::vector<Mix_Chunk*> playerHurt;
	std::vector<Mix_Chunk*> gunshot;
	std::vector<Mix_Chunk*> zombieAttack;
	std::vector<Mix_Chunk*> hitZombie;
*/
	std::string m_PathMusic;
	//Mix_Music* m_Music = NULL;
	std::map< std::string, Mix_Chunk*> m_Sfxs;
	std::map<std::string, Mix_Music*> m_Sounds;
};

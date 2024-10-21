#include"Sound.h"
#include <SDL_ttf.h>

Sound::Sound()
{
    m_PathMusic = "assets-main/audio/";
    Init();
}

Sound::~Sound()
{
    CleanUp();
}

bool Sound::Init()
{
    bool ret = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) //SDL_INIT_AUDIO for Init SDL audio
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        ret = false;
        
    }
    //Initialize SDL_mixer
      // first argument sets the sound frequency, and 44100 is a standard frequency that works on most systems. The second argument determines the sample format, which again here we're using the default. The third argument is the number of hardware channels, and here we're using 2 channels for stereo. The last argument is the sample size, which determines the size of the chunks we use when playing sound. 2048 bytes (AKA 2 kilobyes) worked fine for me, but you may have to experiment with this value to minimize lag when playing sounds.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        ret = false;
    }
    return ret;
}

void Sound::PlaySound(const std::string& name)
{

    Mix_Music* music = NULL;
    auto it = m_Sounds.find(name);
    if (it != m_Sounds.end())
    {
        music = it->second;
    }
    //If there is no music playing
    if (Mix_PlayingMusic() == 0)
    {
        //Play the music
        if (music != nullptr)
        {
            Mix_PlayMusic(music, -1); // The first argument is the music we want to play and the last argument is the number of times to repeat it. -1 for loop it util stop
        }
        else
        {
            printf("No sound available can play: %s\n", name.c_str());// 
        }
    }
    //If music is being played
    else
    {
        //If the music is paused
        if (Mix_PausedMusic() == 1)
        {
            //Resume the music
            Mix_ResumeMusic();
        }
        //If the music is playing
        else
        {
            //Pause the music
            Mix_PauseMusic();
        }
    }
}

void Sound::PauseSound()
{
    //Pause the music
    Mix_PauseMusic();
}

void Sound::ResumeSound()
{
    //Resume the music
    Mix_ResumeMusic();
}

void Sound::StopSound()
{
    //Stop the music
    Mix_HaltMusic();
}

void Sound::LoadSound(const std::string& name)
{
    //Load music
    std::string pathFile = m_PathMusic + name;
    auto it = m_Sounds.find(name);
    if (it != m_Sounds.end())
    {
        return;
    }
   Mix_Music* m_Music = Mix_LoadMUS(pathFile.c_str());
   if (m_Music != nullptr)
   {
       m_Sounds.insert(std::pair<const std::string&, Mix_Music*>(name, (m_Music)));
   }
   else
   {
       printf("Failed to load beat music: %s! SDL_mixer Error: %s\n", name.c_str(), Mix_GetError());

   }
}

void Sound::LoadSfx(const std::string& name)
{
    auto it = m_Sfxs.find(name);
    if (it != m_Sfxs.end())
    {
        return ;
    }
	unsigned int ret = 0;
    std::string path = m_PathMusic + name;
	Mix_Chunk * chunk = Mix_LoadWAV(path.c_str());
	if (chunk == nullptr)
	{
        printf("Failed to load beat music: %s! SDL_mixer Error: %s\n", name.c_str(), Mix_GetError());
	}
	else
	{
		m_Sfxs.insert(std::pair<const std::string&, Mix_Chunk*>(name,(chunk)));
		
	}
}

void Sound::PlaySfx(const std::string& name, int repeat)
{
    Mix_Chunk* chunk = NULL;
    auto it = m_Sfxs.find(name);
    if (it != m_Sfxs.end())
    {
        chunk = it->second;
    }
	if (chunk!= nullptr)
	{
		Mix_PlayChannel(-1, chunk, repeat);
	}
    else
    {
        printf("Cannot play sfx: %s\n", name.c_str());
    }
}

void Sound::CleanUp()
{
    //Free Music
	for (auto it = m_Sfxs.begin(); it != m_Sfxs.end(); it++)
	{
		Mix_FreeChunk(it->second);
	}
	m_Sfxs.clear();
    for (auto it = m_Sounds.begin(); it != m_Sounds.end(); it++)
    {
        Mix_FreeMusic(it->second);
    }
  
   
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

#pragma region Play_Audio
void Sound::playMenuMusic()
{
    //Play the menu music
    StopSound();
    LoadSound(p_MenuMusic);
    PlaySound(p_MenuMusic);
}

void Sound::playMainMusic()
{
    //Play the game music
    StopSound();
    LoadSound(p_MainMusic);
    PlaySound(p_MainMusic);
}


void Sound::playBackgroundLoop()
{
    //Play ambient sound and walk loop
    ///walk
    LoadSfx(p_Walk);
    PlaySfx(p_Walk, -1);
    ///ambient sound
}

void Sound::stopBackgroundLoop()
{
    PauseSound();
}

void Sound::playRadio()
{
    LoadSfx(p_Radio);
    PlaySfx(p_Radio);
}

void Sound::playPlayerHurt()
{
    return;
    LoadSfx(p_PlayerHit);
    PlaySfx(p_PlayerHit);
}

void Sound::playHitTree()
{
    LoadSfx(p_HitTree);
    PlaySfx(p_HitTree);
}

void Sound::playReload()
{
    LoadSfx(p_Reload);
    PlaySfx(p_Reload);
}

void Sound::stopReload()
{
    Mix_HaltChannel(RELOAD_CHANNEL); //to stop the last sound effect from playing
}

void Sound::playSwapWeapon() {
    LoadSfx(p_SwapWeapon);
    PlaySfx(p_SwapWeapon);
}

void Sound::playGunshot() {
    int i = GetRandomInt(0, GUNSHOT_VARIATION - 2, 1);
    LoadSfx(p_GunShot[i]);
    PlaySfx(p_GunShot[i]);
}

void Sound::playZombieAttack() {
    int i = GetRandomInt(0, ZOMBIE_ATTACK_VARIATION - 2, 1);
    LoadSfx(p_ZombieAttack[i]);
    PlaySfx(p_ZombieAttack[i]);
}

void Sound::playZombieShoot() {
    LoadSfx(p_ZombieShoot);
    PlaySfx(p_ZombieShoot);
}

void Sound::playHitZombie() {
    int i = GetRandomInt(0, HIT_ZOMBIE_VARIATION - 2, 1);
    LoadSfx(p_ZombieHit[i]);
    PlaySfx(p_ZombieHit[i]);
}

void Sound::playGunEmpty()
{
    LoadSfx(p_GunEmpty);
    PlaySfx(p_GunEmpty);
}

void Sound::playCollectObject()
{
    LoadSfx(p_CollectObject);
    PlaySfx(p_CollectObject);
}

void Sound::playDrinkMilk()
{
    LoadSfx(p_DrinkMilk);
    PlaySfx(p_DrinkMilk);
}

void Sound::playSkillActivation()
{
    LoadSfx(p_PlayerSkill);
    PlaySfx(p_PlayerSkill);
}

void Sound::playGameLose()
{
    StopSound();
    LoadSound(p_GameLose);
    PlaySound(p_GameLose);
}

void Sound::playGameWin()
{  
    StopSound();
    LoadSound(p_GameWin);
    PlaySound(p_GameWin);
}
#pragma endregion

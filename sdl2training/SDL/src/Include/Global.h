#pragma once

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "SDL2_ttf.lib")

//include SDL stuff
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//include ability to exit program
#include <stdio.h>
#include <stdlib.h>

//include other stuffs
#include <stack>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include "Define.h"
#include "Singleton.h"

#include "Include/Timer.h"

extern SDL_Rect camera;

//render window
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//frame rate
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

//screen size
//static int SCREEN_WIDTH = 1280;
//static int SCREEN_HEIGHT = 720;
const int V_BORDER = SCREEN_WIDTH / 50;
const int H_BORDER = SCREEN_HEIGHT / 50;

//dimensions of the level
const int GROUND_TILE_SIZE = 512;
const int LEVEL_SIZE = 5;// 25;
const int LEVEL_WIDTH = GROUND_TILE_SIZE * LEVEL_SIZE;
const int LEVEL_HEIGHT = GROUND_TILE_SIZE * LEVEL_SIZE;

//texture related
const int TREES_CLIP = 14;
const int CROSSHAIR_SIZE = SCREEN_HEIGHT / 35;

//level elements' properties
static int DIFFICULTY = 1; //difficulty will increase the maximum zombie numbers when spawning
const int DIFFICULTY_REQUIREMENT = 5; //10; //the required zombies to kill in order to advance to next level
const int ZOMBIE_NUMBER_STEP = 1; //3; //how many zombie added for each difficulty
const int COLLIDER_TOLERANCE = 2; //the collider size tolerance for the game objects
//trees
const int MAX_TREE_NUM = 2 * LEVEL_SIZE;
static int MIN_TREE_SIZE = 128;
static int MAX_TREE_SIZE = 192;
//harm zones
const int MAX_HARM_ZONE_NUM = 1 * LEVEL_SIZE;
const int MIN_HARM_ZONE_SIZE = 192;
const int MAX_HARM_ZONE_SIZE = 256;
const int MAX_HARM_ZONE_DAMAGE = 20;
//blood pool
const int MAX_BLOOD_POOL_NUM = 10;
const int MAX_DEAD_ZOMBIE_NUM = MAX_BLOOD_POOL_NUM;

//objectives
const int TIME_LIMIT = 300; //total game time in second
const int TOTAL_OBJECTIVE = 5;
const int ZOMBIE_NEEDED_TO_KILL = 10;
const int TOTAL_SIGNAL_ZONE = 3;

//pickupables
//health pickup
const int MAX_HEALTH_PICKUP_NUM = 15;
const int HEALTH_PICKUP_HEAL = 25;
const int HEALTH_PICKUP_SIZE = 75;

//player properties
const int PLAYER_SIZE = 100;
const int PLAYER_STATE = 4;
const int PLAYER_SPEED = 300;
const int PLAYER_WEAPON_SLOT = 3;

//weapon properties
const int BULLET_SPEED = 2500;
const int BULLET_SIZE = 48;
//pistol
static std::string PISTOL_NAME = "pistol";
static float PISTOL_DAMAGE = 5.0f;
static float PISTOL_RATE_OF_FIRE = 0.75f;
static int PISTOL_CLIP_SIZE = 12;
static float PISTOL_RELOAD_TIME = 1.0f;
//rifle
static std::string RIFLE_NAME = "assault rifle";
static float RIFLE_DAMAGE = 3.5f;
static float RIFLE_RATE_OF_FIRE = 0.2f;
static int RIFLE_CLIP_SIZE = 30;
static float RIFLE_RELOAD_TIME = 2.0f;
//chaingun
static std::string CHAINGUN_NAME = "chaingun";
static float CHAINGUN_DAMAGE = 1.5f;
static float CHAINGUN_RATE_OF_FIRE = 0.1f;
static int CHAINGUN_CLIP_SIZE = 30;
static float CHAINGUN_RELOAD_TIME = 2.0f;

//zombie properties
static int MAX_ZOMBIE_NUM = DIFFICULTY_REQUIREMENT;
//normal zombie
const int NORMAL_ZOMBIE_CHANCE = 5;
const float NORMAL_ZOMBIE_HEALTH = 20;
const float NORMAL_ZOMBIE_SPEED = PLAYER_SPEED * 0.75;
const float NORMAL_ZOMBIE_DAMAGE = 5.0f;
const float NORMAL_ZOMBIE_ATTACK_RANGE = 50.0f;
const float NORMAL_ZOMBIE_ATTACK_SPEED = 2.5f;// 0.35f;
//fast zombie
const int FAST_ZOMBIE_CHANCE = 3;
const float FAST_ZOMBIE_HEALTH = 15;
const float FAST_ZOMBIE_SPEED = PLAYER_SPEED * 1.0;
const float FAST_ZOMBIE_DAMAGE = 10.0f;
const float FAST_ZOMBIE_ATTACK_RANGE = 50.0f;
const float FAST_ZOMBIE_ATTACK_SPEED = 4.0f;// 0.15f;
//tank zombie
const int TANK_ZOMBIE_CHANCE = 2;
const float TANK_ZOMBIE_HEALTH = 50;
const float TANK_ZOMBIE_SPEED = PLAYER_SPEED * 0.5;
const float TANK_ZOMBIE_DAMAGE = 15.0f;
const float TANK_ZOMBIE_ATTACK_RANGE = 50.0f;
const float TANK_ZOMBIE_ATTACK_SPEED = 4.0f;// 0.75f;

//signal properties
const float SIGNAL_HEALTH = 160;

//boss properties
//warden
const float BOSS_WARDEN_HEALTH = 900;
const float BOSS_WARDEN_SPEED = PLAYER_SPEED * 0.35;

//animations properties
const float ANIMATION_INTERVAL = 0.075f; //animation interval until next frame in second
//player
// player animations
const int PLAYER_ANIMATION_IDLE_ANIMATION_FRAMES = 20;
const int PLAYER_ANIMATION_WALK_ANIMATION_FRAMES = 20;
const int PLAYER_ANIMATION_FIRE_ANIMATION_FRAMES = 3;
const int PLAYER_ANIMATION_RELOAD_ANIMATION_FRAMES = 15;
// pistol
const int PLAYER_PISTOL_IDLE_ANIMATION_FRAMES = 1;
const int PLAYER_PISTOL_WALK_ANIMATION_FRAMES = 1;
const int PLAYER_PISTOL_FIRE_ANIMATION_FRAMES = 1;
const int PLAYER_PISTOL_RELOAD_ANIMATION_FRAMES = 1;
// rifle
const int PLAYER_RIFLE_IDLE_ANIMATION_FRAMES = 1;
const int PLAYER_RIFLE_WALK_ANIMATION_FRAMES = 1;
const int PLAYER_RIFLE_FIRE_ANIMATION_FRAMES = 1;
const int PLAYER_RIFLE_RELOAD_ANIMATION_FRAMES = 1;
// chaigun
const int PLAYER_CHAINGUN_IDLE_ANIMATION_FRAMES = 1;
const int PLAYER_CHAINGUN_WALK_ANIMATION_FRAMES = 1;
const int PLAYER_CHAINGUN_FIRE_ANIMATION_FRAMES = 1;
const int PLAYER_CHAINGUN_RELOAD_ANIMATION_FRAMES = 1;

//player skills
const float COOLDOWN_TIME_INTERVAL = 10.0f;
static float COOLDOWN_TIME_COUNTER = COOLDOWN_TIME_INTERVAL;
const int PLAYER_EMPEROR_DIVIDE_ANIMATION_FRAMES = 8;
const int PLAYER_CALL_OF_THE_FORGE_GOD_ANIMATION_FRAMES = 8;
const int PLAYER_DOMINUS_SHIELD_FRAMES = 6;

//player effects
const int PLAYER_EFFECT_ANIMATION_FRAMES = 16;
const float PLAYER_EFFECT_ANIMATION_TIME_INTERVAL = 1.2f;

//zombie
const int ZOMBIE_WALK_ANIMATION_FRAMES = 17;
const int ZOMBIE_ATTACK_ANIMATION_FRAMES = 9;

//signal
const int SIGNAL_INTRO_ANIMATION_FRAMES = 16;
const int SIGNAL_IDLE_ANIMATION_FRAMES = 16;
const int SIGNAL_HURT_ANIMATION_FRAMES = 4;
const int SIGNAL_DEAD_ANIMATION_FRAMES = 16;

//boss
//warden
const int BOSS_WARDEN_INTRO_ANIMATION_FRAMES = 16;
const int BOSS_WARDEN_IDLE_ANIMATION_FRAMES = 16;
const int BOSS_WARDEN_WALK_ANIMATION_FRAMES = 16;
const int BOSS_WARDEN_DIVE_ANIMATION_FRAMES = 16;
const int BOSS_WARDEN_HIDE_ANIMATION_FRAMES = 1;
const int BOSS_WARDEN_HURT_ANIMATION_FRAMES = 6;
const int BOSS_WARDEN_DEAD_ANIMATION_FRAMES = 10;
const int BOSS_WARDEN_CLONE_ANIMATION_FRAMES = 8;

//settings
static bool setting_Music = true;

int GetRandomInt(int min_value, int max_value, int step);
float GetRandomFloat(float min_value, float max_value, float step);
float map(float x, float in_min, float in_max, float out_min, float out_max);
float calOnScreenXPosition(SDL_Rect& camera, int targetX);
float calOnScreenYPosition(SDL_Rect& camera, int targetY);
float calDistance(float x1, float y1, float x2, float y2);

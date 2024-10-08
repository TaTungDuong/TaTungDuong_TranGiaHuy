#include "Player.h"
#include "GameWindows.h"
#include "ResourceManagers.h"
#include "Define.h"
#include "string"
// Player textures
LTexture Player::gIdleTexture;
LTexture Player::gWalkTexture;

// Animation clips
SDL_Rect Player::gIdleClips[6];
SDL_Rect Player::gWalkClips[8];

bool Player::loadMedia() {
    bool success = true;

    if (!gIdleTexture.loadFromFile("Data/Textures/player_idle.png", GameWindows::gRenderer)) {
        printf("Failed to load idle animation texture!\n");
        success = false;
    }
    else {
        for (int i = 0; i < 6; ++i) {
            gIdleClips[i].x = i * (gIdleTexture.getWidth() / 6);
            gIdleClips[i].y = 0;
            gIdleClips[i].w = gIdleTexture.getWidth() / 6;
            gIdleClips[i].h = gIdleTexture.getHeight();
        }
    }

    if (!gWalkTexture.loadFromFile("Data/Textures/player_walk.png", GameWindows::gRenderer)) {
        printf("Failed to load walking animation texture!\n");
        success = false;
    }
    else {
        for (int i = 0; i < 8; ++i) {
            gWalkClips[i].x = i * (gWalkTexture.getWidth() / 8);
            gWalkClips[i].y = 0;
            gWalkClips[i].w = gWalkTexture.getWidth() / 8;
            gWalkClips[i].h = gWalkTexture.getHeight();
        }
    }

    return success;
}

void Player::render(int playerX, int playerY, bool isFlipped, bool isMoving, int frame) {
    SDL_Rect* currentClip;

    if (isMoving) {
        currentClip = &gWalkClips[frame / 4];
        gWalkTexture.render(playerX, playerY, GameWindows::gRenderer, currentClip, isFlipped);
    }
    else {
        currentClip = &gIdleClips[frame / 4];
        gIdleTexture.render(playerX, playerY, GameWindows::gRenderer, currentClip, isFlipped);
    }
}

void Player::free() {
    gIdleTexture.free();
    gWalkTexture.free();
}

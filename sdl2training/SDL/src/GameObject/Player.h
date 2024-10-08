#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "LTexture.h"
const int PLAYER_WIDTH = 32; // Define the player dimensions
const int PLAYER_HEIGHT = 32;


class Player {
public:
    // Load player media
    static bool loadMedia();

    // Render the player
    static void render(int playerX, int playerY, bool isFlipped, bool isMoving, int frame);

    // Free the player resources
    static void free();

private:
    // Player textures
    static LTexture gIdleTexture;
    static LTexture gWalkTexture;

    // Animation clips
    static SDL_Rect gIdleClips[6];
    static SDL_Rect gWalkClips[8];
};

#endif

#include "KeyEvents.h"
#include <SDL.h>

// Define the speed of the player movement
const float PLAYER_SPEED = 1.0f;

bool handleKeyEvents(bool& isMoving, bool& isFlipped, float& playerX, float& playerY) {
    SDL_Event e;
    bool quit = false;
    int mouseX, mouseY;

    // Handle events
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }

    const Uint8* keyStates = SDL_GetKeyboardState(NULL);

    // Reset isMoving to false by default
    isMoving = false;

    // Check for movement keys and update player position
    if (keyStates[SDL_SCANCODE_W] || keyStates[SDL_SCANCODE_UP]) {
        playerY -= PLAYER_SPEED;  // Move up
        isMoving = true;
    }
    if (keyStates[SDL_SCANCODE_S] || keyStates[SDL_SCANCODE_DOWN]) {
        playerY += PLAYER_SPEED;  // Move down
        isMoving = true;
    }
    if (keyStates[SDL_SCANCODE_A] || keyStates[SDL_SCANCODE_LEFT]) {
        playerX -= PLAYER_SPEED;  // Move left
        isMoving = true;
        isFlipped = true;  // Flip left
    }
    if (keyStates[SDL_SCANCODE_D] || keyStates[SDL_SCANCODE_RIGHT]) {
        playerX += PLAYER_SPEED;  // Move right
        isMoving = true;
        isFlipped = false;  // Face right
    }


    // Get mouse position
    SDL_GetMouseState(&mouseX, &mouseY);

    // If the mouse is to the left of the player, flip horizontally
    if (mouseX < playerX) {
        isFlipped = true;
    }
    else {
        isFlipped = false;
    }

    return quit;
}

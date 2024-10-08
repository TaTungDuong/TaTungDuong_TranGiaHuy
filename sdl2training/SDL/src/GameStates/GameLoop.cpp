#include "GameLoop.h"
#include "Define.h"
GameLoop::GameLoop() {
    // Initialize game state variables
    quit = false;
    isMoving = false;
    isFlipped = false;
    frame = 0;
    playerX = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
    playerY = SCREEN_HEIDHT / 2 - PLAYER_HEIGHT / 2;
}

void GameLoop::run() {
    while (!quit) {
        // Handle key and mouse events, pass playerX for mouse comparison
        quit = handleKeyEvents(isMoving, isFlipped, playerX, playerY);

        SDL_SetRenderDrawColor(GameWindows::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(GameWindows::gRenderer);

        // Render player with the correct animation (idle or walking)
        Player::render(playerX, playerY, isFlipped, isMoving, frame);

        // Render the weapon (if applicable)
        Weapon::render(playerX + PLAYER_WIDTH / 2, playerY + PLAYER_HEIGHT / 2, isFlipped);

        SDL_RenderPresent(GameWindows::gRenderer);

        // Increment frame, cycle animation frames
        ++frame;
        if (isMoving) {
            if (frame / 4 >= 8) frame = 0;  // For walking animation
        }
        else {
            if (frame / 4 >= 6) frame = 0;  // For idle animation
        }
    }
}

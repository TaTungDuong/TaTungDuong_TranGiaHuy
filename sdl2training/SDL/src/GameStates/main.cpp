#include "Game.h"
#include "GameLoop.h"

int main(int argc, char* args[]) {
    Game game;

    if (!game.init()) {
        printf("Failed to initialize!\n");
    }
    else {
        if (!game.loadMedia()) {
            printf("Failed to load media!\n");
        }
        else {
            // Create and start the game loop
            GameLoop gameLoop;
            gameLoop.run();
        }
    }

    game.close();
    return 0;
}

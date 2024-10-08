#include"Game.h"
#include <stdio.h>
/*
int main(int argc, char* args[])
{
	//Start up SDL and create window
	Game::GetInstance()->Run();
	//Free resources and close SDL
	Game::GetInstance()->FreeInstance();

	return 0;
}
*/

#include "GameWindows.h"
#include "GameLoop.h"

int main(int argc, char* args[]) {
    GameWindows game;

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

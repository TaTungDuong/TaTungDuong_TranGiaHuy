#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "GameWindows.h"
#include "Player.h"
#include "Weapon.h"
#include "KeyEvents.h"

class GameLoop {
public:
    // Initializes variables and game objects
    GameLoop();

    // Starts the game loop
    void run();

private:
    bool quit;
    bool isMoving;
    bool isFlipped;
    int frame;
    float playerX;
    float playerY;
};

#endif

#ifndef WEAPON_H
#define WEAPON_H

#include <SDL.h>
#include "LTexture.h"

class Weapon {
public:
    // Load weapon media
    static bool loadMedia();

    // Render the weapon
    static void render(int playerX, int playerY, bool isFlipped);

    // Free the weapon resources
    static void free();

private:
    static LTexture gWeaponTexture;
    static const float WEAPON_SCALE;
};

#endif
#pragma once

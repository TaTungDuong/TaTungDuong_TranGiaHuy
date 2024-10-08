#include "Weapon.h"
#include "GameWindows.h"
#include <stdio.h> // or #include <cstdio>
#include <LTexture.h>

LTexture Weapon::gWeaponTexture;
const float Weapon::WEAPON_SCALE = 2.0f / 3.0f;

bool Weapon::loadMedia() {
    bool success = true;

    if (!gWeaponTexture.loadFromFile("Data/Textures/heavy_cannon.png", GameWindows::gRenderer)) {
        printf("Failed to load weapon texture!\n");
        success = false;
    }

    return success;
}

void Weapon::render(int playerX, int playerY, bool isFlipped) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Calculate the rotation angle
    double angle = atan2(mouseY - playerY, mouseX - playerX) * (180.0 / M_PI);

    // Scale the weapon dimensions
    int weaponWidth = gWeaponTexture.getWidth() * WEAPON_SCALE;
    int weaponHeight = gWeaponTexture.getHeight() * WEAPON_SCALE;

    // Render the weapon with flipping
    SDL_Rect renderQuad = { playerX - weaponWidth / 2, playerY + weaponHeight * 2 / 3, weaponWidth, weaponHeight };
    SDL_RenderCopyEx(GameWindows::gRenderer, gWeaponTexture.getTexture(), NULL, &renderQuad, angle, NULL, isFlipped ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
}


void Weapon::free() {
    gWeaponTexture.free();
}

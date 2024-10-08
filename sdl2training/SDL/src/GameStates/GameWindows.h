#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

class GameWindows {
public:
    // Initializes the SDL and creates a window
    bool init();

    // Loads all media (textures, etc.)
    bool loadMedia();

    // Closes the game and frees all resources
    void close();

    // The window we'll be rendering to
    static SDL_Window* gWindow;

    // The window renderer
    static SDL_Renderer* gRenderer;
};

#endif
#pragma once

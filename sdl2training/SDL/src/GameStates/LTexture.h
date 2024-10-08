#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL.h>
#include <string>

class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer); // Pass the renderer

    //Deallocates texture
    void free();

    //Renders texture at given point with optional flip and rotation
    void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, bool flipHorizontal = false, double angle = 0.0); // Pass the renderer

    //Gets image dimensions
    int getWidth();
    int getHeight();

    //Gets the SDL_Texture pointer
    SDL_Texture* getTexture();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif

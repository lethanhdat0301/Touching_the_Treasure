#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstring>

using namespace std;

class LTexture
{
public:
    LTexture();
    ~LTexture();

    //bool loadFromRenderedText
    bool loadFromFile(string path);

    void free();

    void render(int x, int y, SDL_Rect* clip = NULL);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};



#endif // TEXTURE_H_INCLUDED

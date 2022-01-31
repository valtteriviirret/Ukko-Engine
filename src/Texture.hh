#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "Renderer.hh"
#include "ScreenSize.hh"

namespace Texture
{
	SDL_Texture* load(std::string path);
	SDL_Texture* createTextureFromText(std::string text, TTF_Font* font, SDL_Color color);
}

#endif
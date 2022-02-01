#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Renderer.hh"
#include "ScreenSize.hh"

namespace Texture
{
	SDL_Texture* load(std::string path);
}

#endif
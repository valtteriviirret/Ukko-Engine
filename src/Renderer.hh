#ifndef RENDERER_HH
#define RENDERER_HH

#include <SDL2/SDL.h>

namespace Renderer
{
	// setter and getter for renderer
	SDL_Renderer* get();
	void set(SDL_Renderer* _renderer);

}

#endif
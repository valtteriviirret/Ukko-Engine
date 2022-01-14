#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include "ScreenSize.hh"
#include "Renderer.hh"
#include <iostream>

class Window
{
	public:
		Window();
		~Window();
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
};


#endif

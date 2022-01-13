#ifndef WINDOW_H
#define WINDOW_H

#include "ScreenSize.hh"
#include <iostream>
#include <SDL2/SDL.h>

// this class creates the window object
class Window
{
	public:
		Window();
		~Window();
		SDL_Window* getWindow();
	private:
		bool createWindow();
		void free();
		SDL_Window* window;
};

#endif

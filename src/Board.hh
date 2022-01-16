#ifndef BOARD_HH
#define BOARD_HH

#include <SDL2/SDL.h>
#include "ScreenSize.hh"
#include "Texture.hh"
#include "Renderer.hh"
#include "Window.hh"

class Board
{
	public: 
		Board();
		~Board();
		void render();
		SDL_Texture* getBoard();
	private:
		SDL_Texture* board;
};

#endif

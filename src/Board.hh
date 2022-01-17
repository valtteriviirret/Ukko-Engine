#ifndef BOARD_HH
#define BOARD_HH

#include <SDL2/SDL.h>
#include "ScreenSize.hh"
#include "Texture.hh"
#include "Renderer.hh"
#include "Window.hh"
#include "PieceFactory.hh"

class Board
{
	public: 
		Board();
		~Board();
		void render();
		SDL_Texture* getBoard();
		bool getDotDot();
	private:
		SDL_Texture* board;
		bool dotdot;
};

#endif

#ifndef BOARD_HH
#define BOARD_HH

#include <SDL2/SDL.h>
#include "ScreenSize.hh"
#include "Renderer.hh"

class Board
{
	public: 
		Board();
		void render();
		void makeBoard();
		void makeRects();
		SDL_Rect* getSquare(int x, int y);
	
	private:
		// source and destination for texture
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		SDL_Rect squares[8][8];
};

#endif

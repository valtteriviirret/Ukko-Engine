#ifndef BOARD_HH
#define BOARD_HH

#include <SDL2/SDL.h>
#include "ScreenSize.hh"
#include "Texture.hh"
#include "Renderer.hh"

class Board
{
	public: 
		Board();
		~Board();
		void render();
		SDL_Texture* getBoard();
		SDL_Rect getSquare(int x, int y);
	private:
		// source and destination for texture
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		void makeSquares();
		void makeRects();
		SDL_Texture* board;
		SDL_Rect squares[8][8];
};

#endif

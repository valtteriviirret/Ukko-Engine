#ifndef BOARD_HH
#define BOARD_HH

#include "Texture.hh"

class Board
{
	public: 
		Board();
		~Board();
		SDL_Texture* getBoard();
	private:
		SDL_Texture* board;
};

#endif

#include "Board.hh"

Board::Board()
{
	board = Texture::load("Assets/board.png");

	if(!board)	
		std::cout << "Failed to load board\n";
}

Board::~Board()
{
	SDL_DestroyTexture(board);
	board = nullptr;
}

SDL_Texture* Board::getBoard() { return board; }


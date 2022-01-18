#include "Move.hh"

Board* _board = nullptr;
PieceFactory* _factory = nullptr;

void Move::init(Board* board, PieceFactory* factory)
{
	_board = board;
	_factory = factory;
}

void Move::setPosition(int x, int y)
{
	SDL_RenderCopy(Renderer::get(), _factory->getPiece(3), nullptr, _board->getSquare(x, y));	
}

/*
void Move::render()
{
	// example
	//SDL_RenderCopy(Renderer::get(), _factory->getPiece(11), nullptr, _board->getSquare(3, 1));
}
*/


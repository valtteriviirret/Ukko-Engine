#include "Move.hh"

Board* _board = nullptr;
PieceFactory* _factory = nullptr;

void Move::init(Board* board, PieceFactory* factory)
{
	_board = board;
	_factory = factory;
}

void Move::initBoard()
{
	// example
	SDL_RenderCopy(Renderer::get(), _factory->getPiece(11), nullptr, _board->getSquare(3, 1));
}


#include "Move.hh"

Board* _board = nullptr;
PieceFactory* _factory = nullptr;

void Move::init(Board* board, PieceFactory* factory)
{
	_board = board;
	_factory = factory;
}

void Move::renderInPosition(Piece piece)
{
	if(piece.alive)
	{
		SDL_RenderCopy(Renderer::get(), _factory->getPiece(7), nullptr, _board->getSquare(piece.x, piece.y));
	}
}


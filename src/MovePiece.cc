#include "MovePiece.hh"
#include "Renderer.hh"

MovePiece::MovePiece(Board* board, PieceFactory* factory) : _board(board), _factory(factory)
{
	StartUp();
}

MovePiece::~MovePiece()
{
	_board = nullptr;
	_factory = nullptr;
}

void MovePiece::StartUp()
{
	SDL_RenderCopy(Renderer::get(), _factory->getPiece(0), _board->getSquare(0, 0), nullptr);
}

void MovePiece::render()
{
	StartUp();
}

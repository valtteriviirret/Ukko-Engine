#include "PieceRenderer.hh"

Board* _board = nullptr;
PieceFactory* _factory = nullptr;

void PieceRenderer::init(Board* board, PieceFactory* factory)
{
	_board = board;
	_factory = factory;
}

void PieceRenderer::renderInPosition(Piece piece)
{
	if(piece.alive)
	{
		int n;

		// correlating value from PieceFactory
		switch(piece.type)
		{
			case KING: n = (piece.color == BLACK) ? 2 : 8; break;
			case PAWN: n = (piece.color == BLACK) ? 3 : 9; break;
			case ROOK: n = (piece.color == BLACK) ? 5 : 11; break;
			case KNIGHT: n = (piece.color == BLACK) ? 1 : 7; break;
			case QUEEN: n = (piece.color == BLACK) ? 4 : 10; break;
			case BISHOP: n = (piece.color == BLACK) ? 0 : 6; break;
		}
		
		// render the piece
		SDL_RenderCopy(Renderer::get(), _factory->getPiece(n), nullptr, _board->getSquare(piece.x, piece.y));
	}
}

#include "LegalMoves.hh"


namespace LegalMove
{
	// vector type might need to be pointer
	std::vector<Square> show(Piece piece)
	{
		// vector to be returned
		std::vector<Square> sqrs;

		switch(piece.type)
		{
			case PAWN:

				// 
				// does this make any sense?
				if(Game::whiteBottom && piece.color == WHITE)
				{	
					// first row is special
					if(piece.y == 6)
						if(Sqr::getSquare(piece.x, 4).piece == NONE)
							sqrs.push_back(Sqr::getSquare(piece.x, 4));

					// left
					if(Sqr::getSquare((piece.x - 1), (piece.y - 1)).piece != NONE)
						sqrs.push_back(Sqr::getSquare((piece.x - 1), (piece.y - 1)));

					// center
					if(Sqr::getSquare((piece.x), (piece.y - 1)).piece == NONE)
						sqrs.push_back(Sqr::getSquare((piece.x), (piece.y - 1)));

					// right
					if(Sqr::getSquare((piece.x - 1), (piece.y + 1)).piece != NONE)
						sqrs.push_back(Sqr::getSquare((piece.x - 1), (piece.y + 1)));

				}
				else if((!Game::whiteBottom) && piece.color == WHITE)
				{

				}
				else if(Game::whiteBottom && piece.color == BLACK)
				{

				}

				// (!Game::whiteBottom) && piece.color == BLACK
				else
				{
					if(piece.y == 1)
						if(Sqr::getSquare(piece.x, 3).piece == NONE)
							sqrs.push_back(Sqr::getSquare(piece.x, 3));
				}

			break;
			case KNIGHT: break;
			case QUEEN: break;
			case KING: break;
			case BISHOP: break;
			case ROOK: break;
			case NONE: break;
		}

		return sqrs;
	}
}

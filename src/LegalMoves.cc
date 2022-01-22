#include "LegalMoves.hh"
#include "SquareManager.hh"

void KnightFunc(Piece piece, int x, int y, std::vector<Square> v)
{
	if(Sqr::getSquare(x, y).piece.type == NONE)
		v.push_back(Sqr::getSquare(x, y));
	else
		if(Sqr::getSquare(x, y).piece.color != piece.color)
			v.push_back(Sqr::getSquare(x, y));
}

/*
void RookFunc(Piece piece, int dir, std::vector<Square>v)
{

}
*/


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

				if(piece.user == PLAYER)
				{	
					// first row is special
					if(piece.y == 6)
						if(Sqr::getSquare(piece.x, 4).piece.type == NONE)
							sqrs.push_back(Sqr::getSquare(piece.x, 4));

					// left
					if(Sqr::getSquare((piece.x - 1), (piece.y - 1)).piece.type != NONE)
						if(Sqr::getSquare((piece.x - 1), (piece.y - 1)).piece.color != piece.color)
							sqrs.push_back(Sqr::getSquare((piece.x - 1), (piece.y - 1)));

					// center
					if(Sqr::getSquare(piece.x, (piece.y - 1)).piece.type == NONE)
						sqrs.push_back(Sqr::getSquare(piece.x, (piece.y - 1)));

					// right
					if(Sqr::getSquare((piece.x + 1), (piece.y - 1)).piece.type != NONE)
						if(Sqr::getSquare((piece.x + 1), (piece.y - 1)).piece.color != piece.color)
							sqrs.push_back(Sqr::getSquare((piece.x + 1), (piece.y - 1)));

				}

				// same for upside
				else
				{
					if(piece.y == 1)
						if(Sqr::getSquare(piece.x, 3).piece.type == NONE)
							sqrs.push_back(Sqr::getSquare(piece.x, 3));
				
					if(Sqr::getSquare((piece.x + 1), piece.y + 1).piece.type != NONE)
						if(Sqr::getSquare((piece.x + 1), piece.y + 1).piece.color != piece.color)
							sqrs.push_back(Sqr::getSquare((piece.x + 1), (piece.y + 1)));
 					
					if(Sqr::getSquare(piece.x, (piece.y + 1)).piece.type == NONE)
						sqrs.push_back(Sqr::getSquare(piece.x, (piece.y + 1)));

					if(Sqr::getSquare((piece.x - 1), (piece.y + 1)).piece.type != NONE)
						if(Sqr::getSquare((piece.x - 1), (piece.y + 1)).piece.color != piece.color)
							sqrs.push_back(Sqr::getSquare((piece.x - 1), (piece.y + 1)));
				}
			break;
			case KNIGHT:
				KnightFunc(piece, 2, 1, sqrs);
				KnightFunc(piece, 1, 2, sqrs);
				KnightFunc(piece, 2, -1, sqrs);
				KnightFunc(piece, -2, 1, sqrs);
				KnightFunc(piece, -1, 2, sqrs);
				KnightFunc(piece, -2, 1, sqrs);
				KnightFunc(piece, -2, -1, sqrs);
				KnightFunc(piece, -2, -1, sqrs);
			break;
			case QUEEN: 
					
				
			break;
			case KING: break;
			case BISHOP: break;

			case ROOK:
			/*
				for(int i = piece.x; ;i++)
				{
					if(Sqr::getSquare(i, piece.y).piece.type == NONE)
						sqrs.push_back(Sqr::getSquare(i, piece.y));
					else
						if(Sqr::getSquare(i, piece.y).piece.color != piece.color)
							sqrs.push_back(Sqr::getSquare(i, piece.y));
					break;
				}
			*/
			break;
			case NONE: break;
		}

		return sqrs;
	}
}



#include "LegalMoves.hh"

namespace LegalMove
{
	// the vector to be returned
	std::vector<Square> sqrs;

	void KnightFunc(Piece piece, int x, int y)
	{
		// add if free square
		if(Sqr::getSquare((piece.x + x), (piece.y + y)).piece.type == NONE)
			LegalMove::AddMe(Sqr::getSquare((piece.x + x), (piece.y + y)));
		
		// add if enemy is on square, why does this work???
		else
			if(Sqr::getSquare((piece.x + x), (piece.y + y)).piece.color == piece.color)
				LegalMove::AddMe(Sqr::getSquare((piece.x + x), (piece.y + y)));
	}

	// input sanitation
	void AddMe(Square square)
	{
		if((square.x >= 0) && (square.x < 8) && (square.y >= 0) && (square.y < 8))
			sqrs.push_back(square);
	}

	// vector type might need to be pointer
	std::vector<Square> show(Piece piece)
	{
		// clear vector to be sure
		sqrs.clear();

		switch(piece.type)
		{
			case PAWN:

				if(piece.user == PLAYER)
				{	
					// first row is special
					if(piece.y == 6)
						if(Sqr::getSquare(piece.x, 4).piece.type == NONE)
							AddMe(Sqr::getSquare(piece.x, 4));

					// left
					if(Sqr::getSquare((piece.x - 1), (piece.y - 1)).piece.type != NONE)
						if(Sqr::getSquare((piece.x - 1), (piece.y - 1)).piece.color != piece.color)
							AddMe(Sqr::getSquare((piece.x - 1), (piece.y - 1)));

					// center
					if(Sqr::getSquare(piece.x, (piece.y - 1)).piece.type == NONE)
						AddMe(Sqr::getSquare(piece.x, (piece.y - 1)));

					// right
					if(Sqr::getSquare((piece.x + 1), (piece.y - 1)).piece.type != NONE)
						if(Sqr::getSquare((piece.x + 1), (piece.y - 1)).piece.color != piece.color)
							AddMe(Sqr::getSquare((piece.x + 1), (piece.y - 1)));

				}

				// same for upside
				else
				{
					if(piece.y == 1)
						if(Sqr::getSquare(piece.x, 3).piece.type == NONE)
							AddMe(Sqr::getSquare(piece.x, 3));
				
					if(Sqr::getSquare((piece.x + 1), piece.y + 1).piece.type != NONE)
						if(Sqr::getSquare((piece.x + 1), piece.y + 1).piece.color != piece.color)
							AddMe(Sqr::getSquare((piece.x + 1), (piece.y + 1)));
 					
					if(Sqr::getSquare(piece.x, (piece.y + 1)).piece.type == NONE)
						AddMe(Sqr::getSquare(piece.x, (piece.y + 1)));

					if(Sqr::getSquare((piece.x - 1), (piece.y + 1)).piece.type != NONE)
						if(Sqr::getSquare((piece.x - 1), (piece.y + 1)).piece.color != piece.color)
							AddMe(Sqr::getSquare((piece.x - 1), (piece.y + 1)));
				}
			break;
			case KNIGHT:
			
			for(int i = -2; i < 3; i++)
				for(int j = -2; j < 3; j++)
					if((i != 0 && j != 0) && abs(i) != abs(j))
						KnightFunc(piece, i, j);
	
			break;
			
			case QUEEN: 
					
				
			break;
			case KING: break;
			case BISHOP: break;

			case ROOK: break;
			case NONE: break;
		}

		return sqrs;
	}
}



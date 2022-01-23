#include "LegalMoves.hh"
#include "SquareManager.hh"

namespace LegalMove
{
	// the vector to be returned
	std::vector<Square> sqrs;

	// knight, king
	void HandyFunc(Piece p, int x, int y)
	{
		// if square is not on board
		if(Sqr::squareHelper((p.x + x), (p.y + y)) != nullptr)
		{
			// if square is empty
			if(Sqr::squareHelper((p.x + x), (p.y + y))->piece.type == NONE)
				sqrs.push_back(*Sqr::squareHelper((p.x + x), (p.y + y)));
			
			// add if enemy is on square, why does this work??? somewhere booleans are wrong
			else
				if(Sqr::squareHelper((p.x + x), (p.y + y))->piece.color != p.color)
					sqrs.push_back(*Sqr::squareHelper((p.x + x), (p.y + y)));
		}
	}

	// rook, 
	void LooperFunc(Piece p, int x, int y)
	{
		// max distance
		for(int i = 0; i < 8; i++)
		{
			if(Sqr::squareHelper((p.x + i * x), (p.y + i * y)) != nullptr)
			{
				if(Sqr::squareHelper((p.x + i * x), (p.y + i * y))->piece.type == NONE)
					sqrs.push_back(*Sqr::squareHelper((p.x + i * x), (p.y + i * y)));
				else
				{
					if(Sqr::squareHelper((p.x + i * x), (p.y + i * y))->piece.color == p.color)
						sqrs.push_back(*Sqr::squareHelper((p.x + i * x), (p.y + i * y)));
					else
						break;
				}
			}
			else
				break;
		}
	}


	// vector type might need to be pointer
	std::vector<Square> show(Piece piece)
	{
		// clear vector to be sure
		sqrs.clear();

		switch(piece.type)
		{
			case PAWN:

				// no need to use squareHelper because PAWN can never escape board
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
			
			for(int i = -2; i < 3; i++)
				for(int j = -2; j < 3; j++)
					if((i != 0 && j != 0) && abs(i) != abs(j))
						HandyFunc(piece, i, j);
	
			break;
			case QUEEN: 
				
			break;
			case KING:

			for(int i = -1; i < 2; i++)
				for(int j = -1; j < 2; j++)
					if(!(i == 0 && j == 0))
						HandyFunc(piece, i, j);
			
			break;

			case BISHOP: break;

			case ROOK: 

				LooperFunc(piece, 1, 0);
				LooperFunc(piece, -1, 0);
				LooperFunc(piece, 0, 1);
				LooperFunc(piece, 0, -1);
				
			break;
			case NONE: break;
		}

		return sqrs;
	}
}



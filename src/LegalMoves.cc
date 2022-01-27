#include "LegalMoves.hh"

namespace LegalMove
{
	// the vector to be returned
	std::vector<Square> sqrs;

	// KNIGHT, KING
	void xyFindFunc(Piece p, int x, int y)
	{
		Square* s = Sqr::squareHelper((p.x + x), (p.y + y));
		// if square is not on board
		if(s != nullptr)
		{
			// if square is empty
			if(s->piece.type == NONE)
				sqrs.push_back(*s);
			
			// add if enemy
			else
				if(s->piece.color != p.color)
					sqrs.push_back(*s);
		}
	}

	// ROOK, BISHOP, QUEEN
	void LooperFunc(Piece p, int x, int y)
	{
		// max distance
		for(int i = 1; i < 8; i++)
		{
			Square* s = Sqr::squareHelper(p.x + i * x, p.y + i * y);

			// if square is not in board
			if(s != nullptr)
			{
				// add if square is empty
				if(s->piece.type == NONE)
				{
					sqrs.push_back(*s);
					continue;
				}
				else
				{
					// break the loop if see piece, add if enemy
					if(s->piece.color != p.color)
						sqrs.push_back(*s);
					break;
				}
			}
			else
				break;
		}
	}

	void PawnFunc(Piece p, bool player)
	{
		int m = -1;
		if(player)
		{
			// first row is special
			if(p.y == 6)
				if(Sqr::squareHelper(p.x, 4)->piece.type == NONE)
					sqrs.push_back(*Sqr::squareHelper(p.x, 4));
		}
		else
		{
			if(p.y == 1)
				if(Sqr::squareHelper(p.x, 3)->piece.type == NONE)
					sqrs.push_back(*Sqr::squareHelper(p.x, 3));

			m = 1;
		}
		
		// left
		Square* l = Sqr::squareHelper(p.x + 1 * m, p.y + 1 * m);
		// check that square is on the board
		if(l != nullptr)
			// check if square is empty of pieces
			if(l->piece.type != NONE)
				// check that the square color is different to piece
				if(l->piece.color != p.color)
					// add square
					sqrs.push_back(*l);

		// center
		Square* c = Sqr::squareHelper(p.x, p.y + 1 * m);
		if(c != nullptr)
			if(c->piece.type == NONE)
				sqrs.push_back(*c);

		// right
		Square* r = Sqr::squareHelper(p.x - 1 * m, p.y + 1 * m);
		if(r != nullptr)
			if(r->piece.type != NONE)
				if(r->piece.color != p.color)
					sqrs.push_back(*r);
	}

	
	// get legal moves
	std::vector<Square> get(Piece piece)
	{
		// clear vector to be sure
		sqrs.clear();
	
		switch(piece.type)
		{
			case PAWN:

			if(piece.user == PLAYER)
				PawnFunc(piece, true);
			else
				PawnFunc(piece, false);

			break;
			case KNIGHT:
			
			for(int i = -2; i < 3; i++)
				for(int j = -2; j < 3; j++)
					if((i != 0 && j != 0) && abs(i) != abs(j))
						xyFindFunc(piece, i, j);
	
			break;
			case QUEEN:

			for(int i = -1; i < 2; i++)
				for(int j = -1; j < 2; j++)
					if(!(i == 0 && j == 0))
						LooperFunc(piece, i, j);
				
			break;
			case KING:

			for(int i = -1; i < 2; i++)
				for(int j = -1; j < 2; j++)
					if(!(i == 0 && j == 0))
						xyFindFunc(piece, i, j);
			
			break;
			case BISHOP:

			LooperFunc(piece, 1, 1);
			LooperFunc(piece, 1, -1);
			LooperFunc(piece, -1, 1);
			LooperFunc(piece, -1, -1);

			break;
			case ROOK: 

			LooperFunc(piece, 1, 0);
			LooperFunc(piece, 0, 1);
			LooperFunc(piece, -1, 0);
			LooperFunc(piece, 0, -1);
			
			break;
			case NONE: break;
		}
		
		// return legal moves for the piece
		return sqrs;
	}
}

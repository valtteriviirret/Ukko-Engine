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

	void Castling(Piece p, bool dir)
	{
		// different directions for castling
		int n = -1;
		if(dir)
			n = 1;

		// max distance
		for(int i = 1; i < 5; i++)
		{
			// king side castle is smaller
			if(dir && i == 4)
				break;

			Square* s = Sqr::squareHelper(p.x + i * n, p.y);

			// if not on board, this should never happen
			if(s != nullptr)
			{
				// empty square
				if(s->piece.type == NONE)
					continue;

					// something in the middle, cant castle
				else if(s->piece.type != NONE && s->piece.type != ROOK)
					break;

					// can castle
				else
					sqrs.push_back(*Sqr::squareHelper(p.x + 2 * n, p.y));
			}
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


	// give legal moves
	std::vector<Square> getLegal(Piece piece)
	{ 
		// get raw legal moves for the piece
		std::vector<Square> v = LegalMove::get(piece); 

		// loop all the possible moves 
		for(auto i = v.begin(); i != v.end(); i++) 
		{
			// making fake move
			Sqr::getSquare(i->piece.x, i->piece.y).piece = myPiece(piece);

			// has the fake move been deleted?
			bool deleted = false;

			// creating empty piece
			Piece none = ghost(i->piece.x, i->piece.y);

			// getting the opponent's pieces
			int a = piece.user == PLAYER ? 0 : 16;
			int b = piece.user == PLAYER ? 16 : 32;

			// loop all opponent's pieces
			for(int j = a; j < b; j++)
			{
				// get all raw legal moves for the opponent's pieces
				std::vector<Square> temp = LegalMove::get(Pieces::get(j));

				// loop legal moves for the piece
				for(int k = 0; k < (int)temp.size(); k++)
				{
					// king is in check
					if(temp.at(k).piece.type == KING)
					{
						// delete fake move
						Sqr::getSquare(i->piece.x, i->piece.y).piece = none;
						deleted = true;

						// delete move and set counter smaller after deletion
						v.erase(i--);
					}
				}
			}
			
			// if the move was legal, delete fake move
			if(!deleted)
				Sqr::getSquare(i->piece.x, i->piece.y).piece = none;
		}

		// return filtered moves
		return v;
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


				if(piece.user == PLAYER)
				{
					if(Global::playerCanCastleK)
						Castling(piece, true);

					if(Global::playerCanCastleQ)
						Castling(piece, false);
				}

				else
				{
					if(Global::engineCanCastleK)
						Castling(piece, true);

					if(Global::engineCanCastleQ)
						Castling(piece, false);
				}

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

		// return raw moves
		return sqrs;
	}
}

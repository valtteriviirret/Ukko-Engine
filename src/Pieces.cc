#include "Pieces.hh"

namespace Pieces
{
	// the pieces
	// TODO
	static Piece p[32];

	Piece& get(int n) { return p[n]; }

	Piece* getModify(int n) { return &p[n]; }

	void set(Piece piece, int x, int y)
	{
		for(int i = 0; i < 32; i++)
		{
			if(get(i).x == x && get(i).y == y)
			{
				Piece* x = &p[i];
				x->color = piece.color;
				x->type = piece.type;
				x->user = piece.user;
			}
		}
	}

	Piece& getReal(Piece* piece)
	{
		for(int i = 0; i < 32; i++)
			if(p[i].x == piece->x && p[i].y == piece->y
			&& p[i].user == piece->user && p[i].type == piece->type)
				return p[i];

		// TODO fix this, although this should never happen
		
		return p[31];
	}

	void init()
	{
		// 0-7 		ENGINE PAWNS
		// 8-15 	ENGINE PIECES
		// 16-23 	PLAYER PAWNS
		// 24-31 	PLAYER PIECES
	
		Color engineColor = BLACK;
		Color PlayerColor = WHITE;
	
		// engine pawns
		for(int i = 0; i < 8; i++)
		{
			p[i] = { PAWN, engineColor, i, 1, ENGINE };
			Sqr::getSquare(i, 1).piece = p[i];
		}

		// player pawns
		for(int i = 16; i < 24; i++)
		{
			p[i] = { PAWN, PlayerColor, (i - 16), 6, PLAYER };
			Sqr::getSquare((i - 16), 6).piece = p[i];
		}

		// engine pieces
		p[8] = { ROOK, engineColor, 0, 0, ENGINE };
		p[9] = { ROOK, engineColor, 7, 0, ENGINE };
		p[10] = { KNIGHT, engineColor, 1, 0, ENGINE };
		p[11] = { KNIGHT, engineColor, 6, 0, ENGINE };
		p[12] = { BISHOP, engineColor, 2, 0, ENGINE };
		p[13] = { BISHOP, engineColor, 5, 0, ENGINE };
		p[14] = { QUEEN, engineColor, 3, 0, ENGINE };
		p[15] = { KING, engineColor, 4, 0, ENGINE };

		// player pieces
		p[24] = { ROOK, PlayerColor, 0, 7, PLAYER };
		p[25] = { ROOK, PlayerColor, 7, 7, PLAYER };
		p[26] = { KNIGHT, PlayerColor, 1, 7, PLAYER };
		p[27] = { KNIGHT, PlayerColor, 6, 7, PLAYER };
		p[28] = { BISHOP, PlayerColor, 2, 7, PLAYER };
		p[29] = { BISHOP, PlayerColor, 5, 7, PLAYER };
		p[30] = { QUEEN, PlayerColor, 3, 7, PLAYER };
		p[31] = { KING, PlayerColor, 4, 7, PLAYER };


		// update squares
		Sqr::getSquare(0, 0).piece = p[8];
		Sqr::getSquare(7, 0).piece = p[9];
		Sqr::getSquare(1, 0).piece = p[10];
		Sqr::getSquare(6, 0).piece = p[11];
		Sqr::getSquare(2, 0).piece = p[12];
		Sqr::getSquare(5, 0).piece = p[13];
		Sqr::getSquare(3, 0).piece = p[14];
		Sqr::getSquare(4, 0).piece = p[15];
		Sqr::getSquare(0, 7).piece = p[24];
		Sqr::getSquare(7, 7).piece = p[25];
		Sqr::getSquare(1, 7).piece = p[26];
		Sqr::getSquare(6, 7).piece = p[27];
		Sqr::getSquare(2, 7).piece = p[28];
		Sqr::getSquare(5, 7).piece = p[29];
		Sqr::getSquare(3, 7).piece = p[30];
		Sqr::getSquare(4, 7).piece = p[31];

		// TODO
		// initialize empty squares as empty
		for (int y = 2; y < 6; y++)
			for (int x = 0; x < 8; x++)
				Sqr::getSquare(x, y).piece = ghost(x, y);
	}
}

#include "Pieces.hh"

namespace Pieces
{

	Piece& get(int n) { return p[n]; }

	void init()
	{
		// 0-7 		ENGINE PAWNS
		// 8-15 	ENGINE PIECES
		// 16-23 	PLAYER PAWNS
		// 24-31 	PLAYER PIECES

		// setting all pieces alive
		for (int i = 0; i < 32; i++)
		{
			p[i].alive = true;
		}

		// initializing enemy's pieces colors
		for (int i = 0; i < 16; i++)
		{
			if (Settings::PlayerColor == Color::WHITE)
				p[i].color = Color::BLACK;
			else
				p[i].color = Color::WHITE;
		}

		// initializing player's pieces colors
		for (int i = 16; i < 32; i++)
		{
			if (Settings::PlayerColor == Color::WHITE)
				p[i].color = Color::WHITE;
			else
				p[i].color = Color::BLACK;
		}

		// engine pawns
		for (int i = 0; i < 8; i++)
		{
			p[i].type = PAWN;
			p[i].x = i;
			p[i].y = 1;
			p[i].user = ENGINE;
			Sqr::getSquare(i, 1).piece = p[i];
		}

		// player pawns
		for (int i = 16; i < 24; i++)
		{
			p[i].type = PAWN;
			p[i].x = (i - 16);
			p[i].y = 6;
			p[i].user = PLAYER;
			Sqr::getSquare((i - 16), 6).piece = p[i];
		}


		// ENGINE PIECES
		for (int i = 8; i < 16; i++)
		{
			p[i].y = 0;
			p[i].user = ENGINE;
		}

		p[8].type = ROOK;
		p[8].x = 0;
		Sqr::getSquare(0, 0).piece = p[8];

		p[9].type = ROOK;
		p[9].x = 7;
		Sqr::getSquare(7, 0).piece = p[9];

		p[10].type = KNIGHT;
		p[10].x = 1;
		Sqr::getSquare(1, 0).piece = p[10];

		p[11].type = KNIGHT;
		p[11].x = 6;
		Sqr::getSquare(6, 0).piece = p[11];

		p[12].type = BISHOP;
		p[12].x = 2;
		Sqr::getSquare(2, 0).piece = p[12];

		p[13].type = BISHOP;
		p[13].x = 5;
		Sqr::getSquare(5, 0).piece = p[13];

		p[14].type = QUEEN;
		p[14].x = 3;
		Sqr::getSquare(3, 0).piece = p[14];

		p[15].type = KING;
		p[15].x = 4;
		Sqr::getSquare(4, 0).piece = p[15];


		// PLAYER PIECES
		for (int i = 24; i < 32; i++)
		{
			p[i].y = 7;
			p[i].user = PLAYER;
		}

		p[24].type = ROOK;
		p[24].x = 0;
		Sqr::getSquare(0, 7).piece = p[24];

		p[25].type = ROOK;
		p[25].x = 7;
		Sqr::getSquare(7, 7).piece = p[25];

		p[26].type = KNIGHT;
		p[26].x = 1;
		Sqr::getSquare(1, 7).piece = p[26];

		p[27].type = KNIGHT;
		p[27].x = 6;
		Sqr::getSquare(6, 7).piece = p[27];

		p[28].type = BISHOP;
		p[28].x = 2;
		Sqr::getSquare(2, 7).piece = p[28];

		p[29].type = BISHOP;
		p[29].x = 5;
		Sqr::getSquare(5, 7).piece = p[29];

		p[30].type = QUEEN;
		p[30].x = 3;
		Sqr::getSquare(3, 7).piece = p[30];

		p[31].type = KING;
		p[31].x = 4;
		Sqr::getSquare(4, 7).piece = p[31];

		// initialize empty squares as empty
		for (int y = 2; y < 6; y++)
			for (int x = 0; x < 8; x++)
			{
				Piece piece =
						{
								NONE,
								UNDEFINED,
								true,
								x,
								y,
								GHOST
						};
				Sqr::getSquare(x, y).piece = piece;
			}
	}
}

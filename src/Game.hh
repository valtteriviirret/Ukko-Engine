#ifndef GAME_HH
#define GAME_HH

#include "Piece.hh"
#include "PieceRenderer.hh"
#include "SquareManager.hh"
#include "Square.hh"

#define ARRSIZE(arr) (int)(sizeof(arr)/sizeof(arr[0]))

class Game
{
	public:
		Game();
		void update();
		Piece* getPieces();
	private:
		void initPieces(bool whiteBottom);
		Piece p[32];
};

#endif

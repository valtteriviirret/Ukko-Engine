#ifndef GAME_HH
#define GAME_HH

#include "Piece.hh"
#include "PieceRenderer.hh"
#include "SquareManager.hh"
#include "Square.hh"
#include "Board.hh"
#include "PieceFactory.hh"

#define ARRSIZE(arr) (int)(sizeof(arr)/sizeof(arr[0]))

class Game
{
	public:
		Game();
		~Game();
		void render();
	private:
		void initPieces(bool whiteBottom);
		Piece p[32];
		Board* board = nullptr;
		PieceFactory* pieces = nullptr;
		
};

#endif

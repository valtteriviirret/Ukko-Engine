#ifndef GAME_HH
#define GAME_HH

#include "Piece.hh"
#include "Move.hh"

#define ARRSIZE(arr) (int)(sizeof(arr)/sizeof(arr[0]))

class Game
{
	public:
		Game();
		void update();
	private:
		void initPieces();
		Piece pieces[32];
};

#endif

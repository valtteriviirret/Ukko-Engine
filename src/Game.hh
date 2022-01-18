#ifndef GAME_HH
#define GAME_HH

#include "Piece.hh"
#include "Move.hh"

class Game
{
	public:
		Game();
		void update();
	private:
		Piece pieces[32];
};

#endif

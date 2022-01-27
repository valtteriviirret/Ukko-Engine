#ifndef ENGINE_HH
#define ENGINE_HH

#include "Piece.hh"
#include "Pieces.hh"
#include "Global.hh"
#include "LegalMoves.hh"
#include "Move.hh"
#include <vector>

class Engine
{
	public:
		Engine();
		~Engine();
		void PlayMove();
	private:
		void getPieces();
		void evaluate();
		Piece pieces[32];
};

#endif

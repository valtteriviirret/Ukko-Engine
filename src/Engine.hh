#ifndef ENGINE_HH
#define ENGINE_HH

#include "Piece.hh"
#include "Pieces.hh"
#include "Global.hh"
#include "LegalMoves.hh"
#include "Move.hh"
#include <vector>
#include <iostream>

class Engine
{
	public:
		Engine();
		~Engine();
		void PlayMove();
	private:
		int pickRandomPiece();
		int selectedPiece = 0;
		bool isMoveDecided = false;
		Square move;
};

#endif

#ifndef GLOBAL_HH
#define GLOBAL_HH

#include "Piece.hh"

// check these out!
static bool staleMate = false;
static bool playerTurn;
static Piece p[32];

class Global
{
	public:
		// castling
		static bool playerKingMoved;
		static bool playerQsideRookMoved;
		static bool playerKsideRookMoved;

		static bool engineKingMoved;
		static bool engineQsideRookMoved;
		static bool engineKsideRookMoved;
};


#endif

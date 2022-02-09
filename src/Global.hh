#ifndef GLOBAL_HH
#define GLOBAL_HH

#include "Piece.hh"

static enum { GAME_ON, VICTORY, DEFEAT, DRAW } currentGameState;
static bool playerTurn;
static Piece p[32];

// return ghost struct
Piece ghost(int x, int y);

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

		static bool playerCanCastleK;
		static bool playerCanCastleQ;
		static bool engineCanCastleK;
		static bool engineCanCastleQ;

		// check
		static bool playerInCheck;
		static bool engineInCheck;
};

#endif

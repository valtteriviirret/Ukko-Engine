#ifndef GLOBAL_HH
#define GLOBAL_HH

#include "Piece.hh"
#include "iostream"

// check these out!
static bool staleMate = false;
static bool playerTurn;
static Piece p[32];
static std::string output;

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

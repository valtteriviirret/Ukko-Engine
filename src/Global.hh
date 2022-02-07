#ifndef GLOBAL_HH
#define GLOBAL_HH

#include "Piece.hh"

// check these out!
typedef enum { GAME_ON, VICTORY, DEFEAT, STALEMATE } currentGameState;
static bool playerTurn;
static Piece p[32];

// return ghost struct
Piece ghost(int x, int y);
Piece myPiece(Piece piece);

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
		[[maybe_unused]] static bool playerInCheck;
		static bool engineInCheck;
};

#endif

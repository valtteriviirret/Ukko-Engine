#ifndef GLOBAL_HH
#define GLOBAL_HH

#include "Piece.hh"
#include "Square.hh"
#include "SquareManager.hh"

#define ARRSIZE(arr) (int)(sizeof(arr)/sizeof(arr[0]))

typedef enum { GAME_ON, VICTORY, DEFEAT, DRAW, END } currentGameState;

class Global
{
	public:

		// 1 ENGINE WIN -- -1 ENGINE LOSE
		static double evaluation;

		static bool playerTurn;
		static currentGameState state;
		static Square* en_passant;

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

		static bool inPromotion;
};

#endif

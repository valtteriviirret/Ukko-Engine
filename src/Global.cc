#include "Global.hh"

bool Global::playerKingMoved = false;
bool Global::engineKingMoved = false;
bool Global::playerQsideRookMoved = false;
bool Global::playerKsideRookMoved = false;
bool Global::engineQsideRookMoved = false;
bool Global::engineKsideRookMoved = false;

bool Global::playerCanCastleK = true;
bool Global::playerCanCastleQ = true;
bool Global::engineCanCastleK = true;
bool Global::engineCanCastleQ = true;

bool Global::playerInCheck = false;
bool Global::engineInCheck = false;

Piece ghost(int x, int y)
{
	return { NONE, UNDEFINED, true, x, y, GHOST };
}

Piece myPiece(Piece piece)
{
	return { piece.type, piece.color, true, piece.x, piece.y, piece.user };
}

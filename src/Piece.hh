#ifndef PIECE_HH
#define PIECE_HH

#include <string>

typedef struct Piece
{
	std::string type;
	bool color;
	bool alive;
	// location
    int x, y;
} Piece;

typedef enum { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING } Type;

#endif


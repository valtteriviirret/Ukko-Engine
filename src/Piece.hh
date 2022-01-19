#ifndef PIECE_HH
#define PIECE_HH

typedef enum { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, NONE } Type;
typedef enum { BLACK, WHITE } Color;

typedef struct Piece
{
	Type type;
	Color color;
	bool alive;
    int x, y;
} Piece;


#endif


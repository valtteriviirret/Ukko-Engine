#ifndef PIECE_HH
#define PIECE_HH

typedef enum { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, NONE } Type;
typedef enum { BLACK, WHITE, UNDEFINED } Color;
typedef enum { PLAYER, ENGINE, GHOST } User; 

typedef struct Piece
{
	Type type;
	Color color;
    int x, y;
	User user;
} Piece;


#endif


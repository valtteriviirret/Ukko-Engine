#ifndef PIECE_HH
#define PIECE_HH

typedef enum { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, NONE } Type;
typedef enum { BLACK, WHITE } Color;
typedef enum { PLAYER, OPPONENT } User; 

typedef struct Piece
{
	Type type;
	Color color;
	bool alive;
    int x, y;
	User user;
} Piece;


#endif


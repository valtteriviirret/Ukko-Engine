#ifndef SQUARE_HH
#define SQUARE_HH

#include "Piece.hh"
#include <SDL2/SDL.h>

typedef struct Square
{
	SDL_Rect rect;
	Piece piece;
	int x, y;

} Square;

#endif

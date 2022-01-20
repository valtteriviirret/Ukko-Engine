#ifndef SQUARE_HH
#define SQUARE_HH

#include "Piece.hh"
#include <SDL2/SDL.h>

typedef struct Square
{
	SDL_Rect rect;
	Type piece = NONE;
	int x, y;

} Square;

#endif

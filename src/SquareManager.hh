#ifndef SQUAREMANAGER_HH
#define SQUAREMANAGER_HH

#include "Square.hh"

namespace Sqr
{
	Square& getSquare(int x, int y);
	void handleEvent(Square square, SDL_Event e);
}

#endif

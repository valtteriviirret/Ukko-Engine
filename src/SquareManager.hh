#ifndef SQUAREMANAGER_HH
#define SQUAREMANAGER_HH

#include "Square.hh"

namespace Sqr
{
	Square& getSquare(int x, int y);
	Square* squareHelper(int x, int y);
}

#endif

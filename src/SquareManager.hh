#ifndef SQUAREMANAGER_HH
#define SQUAREMANAGER_HH

#include "Square.hh"
#include <array>

namespace Sqr
{
	Square& getSquare(int x, int y);
	Square* squareHelper(int x, int y);

	std::array <std::array <Square, 8>, 8> copy();
};

#endif

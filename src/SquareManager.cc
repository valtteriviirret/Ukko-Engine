#include "SquareManager.hh"

namespace Sqr
{
	// the actual squares
	Square squares[8][8];

	Square* squareHelper(int x, int y)
	{
		if((x >= 0) && (x < 8) && (y >= 0) && (y < 8))
			return &getSquare(x, y);
		else
			return nullptr;
	}

	Square& getSquare(int x, int y) { return squares[x][y]; }

	Square squareCopy(int x, int y) { return squares[x][y]; }
}

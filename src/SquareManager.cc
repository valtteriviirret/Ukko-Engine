#include "SquareManager.hh"

// the actual squares
namespace Sqr
{
	std::array <std::array <Square, 8>, 8> squares;

	Square* squareHelper(int x, int y)
	{
		if((x >= 0) && (x < 8) && (y >= 0) && (y < 8))
			return &getSquare(x, y);
		else
			return nullptr;
	}

	Square& getSquare(int x, int y) { return squares[x][y]; }

	std::array <std::array <Square, 8>, 8> copy()
	{
		return squares;
	}
}

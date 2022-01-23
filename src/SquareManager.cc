#include "SquareManager.hh"

namespace Sqr
{
	// the actual squares
	Square squares[8][8];

	Square* squareHelper(int x, int y)
	{
		if(x < 0 || x > 7 || y < 0 || y > 7)
			return nullptr;
		else
			return &getSquare(x, y);
	}

	// getting individual square
	Square& getSquare(int x, int y) 
	{
		return squares[x][y];
	}
}

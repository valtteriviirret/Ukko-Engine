#include "SquareManager.hh"

namespace Sqr
{
	// the actual squares
	Square squares[8][8];

	// getting individual square
	Square& getSquare(int x, int y) { return squares[x][y]; }
}

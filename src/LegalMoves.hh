#ifndef LEGALMOVES_HH
#define LEGALMOVES_HH

#include "Square.hh"
#include "SquareManager.hh"
#include "Piece.hh"
#include "Settings.hh"
#include <vector>

namespace LegalMove
{
	std::vector<Square> show(Piece piece);
	void HandyFunc(Piece p, int x, int y);
	void LooperFunc(Piece p, int x, int y);
	void AddMe(Square* square);
}

#endif

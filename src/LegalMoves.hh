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
}

#endif

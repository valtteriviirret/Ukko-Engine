#ifndef LEGALMOVES_HH
#define LEGALMOVES_HH

#include "Square.hh"
#include "SquareManager.hh"
#include "Piece.hh"
#include "Game.hh"
#include <vector>

namespace LegalMove
{
	std::vector<Square> show(Piece piece);
}

#endif

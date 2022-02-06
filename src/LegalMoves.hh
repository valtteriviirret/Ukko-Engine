#ifndef LEGALMOVES_HH
#define LEGALMOVES_HH

#include "Square.hh"
#include "SquareManager.hh"
#include "Piece.hh"
#include "Global.hh"
#include "Settings.hh"
#include "Pieces.hh"
#include "Move.hh"
#include <vector>

namespace LegalMove
{
	// main function
	std::vector<Square> get(Piece piece);

	// get filtered version
	std::vector<Square> getLegal(Piece piece);
}

#endif

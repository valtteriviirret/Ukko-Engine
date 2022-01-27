#ifndef MOVE_HH
#define MOVE_HH

#include "Piece.hh"
#include "Square.hh"
#include "Pieces.hh"
#include "SquareManager.hh"
#include <iostream>

namespace Move
{
	void execute(Piece& source, Square target);
}

#endif

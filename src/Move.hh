#ifndef MOVE_HH
#define MOVE_HH

#include "Piece.hh"
#include "Square.hh"
#include "Pieces.hh"
#include "SquareManager.hh"
#include "Global.hh"
#include <iostream>
#include <string>

namespace Move
{
	void execute(Piece& source, Square target);
	std::string getName();
}

#endif

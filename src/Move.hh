#ifndef MOVE_HH
#define MOVE_HH

#include "Piece.hh"
#include "Square.hh"
#include "Pieces.hh"
#include "SquareManager.hh"
#include "Global.hh"
#include <iostream>
#include <string>

#define showPieces std::cout << "Q:QUEEN\nR:ROOK\nB:BISHOP\nN:KNIGHT\n";

namespace Move
{
	void execute(Piece* source, Square target, bool real);
	std::string getName();
}

#endif

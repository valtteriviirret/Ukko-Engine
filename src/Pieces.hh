#ifndef PIECES_HH
#define PIECES_HH

#include "Piece.hh"
#include "SquareManager.hh"
#include "Settings.hh"
#include "Global.hh"

namespace Pieces
{
	// initializing pieces in their correct positions
	void init();

	// getting individual piece
	Piece& get(int n);

}

#endif


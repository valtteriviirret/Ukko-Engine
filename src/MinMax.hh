#ifndef MINMAX_HH
#define MINMAX_HH

#include <utility>
#include "Piece.hh"
#include "Square.hh"

class MinMax
{
	public:
		double evaluation;
		std::pair<Piece*, Square> bestMove;
};

#endif

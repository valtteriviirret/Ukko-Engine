#ifndef MINMAX_HH
#define MINMAX_HH

#include <utility>
#include "Piece.hh"
#include "Square.hh"

class MinMax
{
	public:
		MinMax(double evaluation, std::pair<Piece*, Square> bestMove) 
			: _evaluation(evaluation), _bestMove(bestMove) {}
		MinMax() {};
		double _evaluation;
		std::pair<Piece*, Square> _bestMove;
};

#endif

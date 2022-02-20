#ifndef MINMAX_HH
#define MINMAX_HH

#include <utility>
#include "Piece.hh"
#include "Square.hh"

class MinMax
{
	public:
		MinMax(double evaluation, std::pair<Piece*, Square>* bestMove);
		MinMax();

		void setEval(double evaluation);
		void setMove(std::pair<Piece*, Square>* bestMove);

		double _evaluation;
		std::pair<Piece*, Square>* _bestMove;
};

#endif

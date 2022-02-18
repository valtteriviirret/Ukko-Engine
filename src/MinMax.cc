#include "MinMax.hh"

MinMax::MinMax(double evaluation, std::pair<Piece*, Square> bestMove)
		: _evaluation(evaluation), _bestMove(bestMove) {}

MinMax::MinMax() : _evaluation(0.0), _bestMove(std::pair<Piece*, Square>()) {}

void MinMax::setEval(double evaluation) { _evaluation = evaluation; }

void MinMax::setMove(std::pair<Piece*, Square> bestMove) { _bestMove = bestMove; }

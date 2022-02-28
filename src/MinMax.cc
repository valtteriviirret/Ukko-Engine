#include "MinMax.hh"

MinMax::MinMax(double evaluation, std::pair<Square, Square>* bestMove)
		: _evaluation(evaluation), _bestMove(bestMove) {}

MinMax::MinMax() : _evaluation(4.0), _bestMove(nullptr) {}

void MinMax::setEval(double evaluation) { _evaluation = evaluation; }

void MinMax::setMove(std::pair<Square, Square>* bestMove) { _bestMove = bestMove; }

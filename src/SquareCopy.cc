#include "SquareCopy.hh"

void SquareCopy::update(std::array <std::array <Square, 8>, 8> sqr) { _squares = sqr; }

std::array <std::array <Square, 8>, 8> SquareCopy::get() { return _squares; }


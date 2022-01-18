#ifndef MOVEPIECE_HH
#define MOVEPIECE_HH

#include <SDL2/SDL.h>
#include <iostream>
#include "Board.hh"
#include "Renderer.hh"
#include "PieceFactory.hh"

namespace Move
{
	void init(Board* board, PieceFactory* factory);
	void initBoard();
};

#endif


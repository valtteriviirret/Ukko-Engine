#ifndef PIECERENDERER_HH
#define PIECERENDERER_HH

#include <SDL2/SDL.h>
#include <iostream>
#include "Board.hh"
#include "Renderer.hh"
#include "PieceFactory.hh"
#include "Piece.hh"

namespace PieceRenderer
{
	void init(Board* board, PieceFactory* factory);
	void renderInPosition(Piece piece);
};

#endif


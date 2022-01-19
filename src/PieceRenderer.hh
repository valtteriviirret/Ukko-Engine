#ifndef PIECERENDERER_HH
#define PIECERENDERER_HH

#include <SDL2/SDL.h>
#include <iostream>
#include "Renderer.hh"
#include "PieceFactory.hh"
#include "Piece.hh"
#include "SquareManager.hh"

namespace PieceRenderer
{
	void init(PieceFactory* factory);
	void renderInPosition(Piece piece);
};

#endif


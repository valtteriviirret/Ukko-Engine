#ifndef ENGINE_HH
#define ENGINE_HH

#include "Piece.hh"
#include "Pieces.hh"
#include "Global.hh"
#include "LegalMoves.hh"
#include "Move.hh"
#include <vector>
#include <iostream>

class Engine
{
public:
	Engine();
	~Engine();
	static void PlayMove();
private:
	static int pickPiece();
};

#endif

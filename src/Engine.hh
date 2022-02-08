#ifndef ENGINE_HH
#define ENGINE_HH

#include "Piece.hh"
#include "Pieces.hh"
#include "Global.hh"
#include "LegalMoves.hh"
#include "Move.hh"
#include "SquareManager.hh"
#include <vector>
#include <iostream>

class Engine
{
public:
	Engine();
	~Engine();
	void PlayMove();
private:
	void getAllSquares();
	Square* squares[8][8] = {};
	int pickPiece();
};

#endif

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
#include <map>

class Engine
{
	public:
		Engine();
		~Engine();
		bool PlayMove();
	private:
		void makeFakeMove(std::pair<Piece*, Square> move);
		void getAllPieces();
		void getAllMoves();
		void getAllSquares();
		int evaluate();
		double materialValue(bool player);
		Square* squares[8][8] = {};
		std::vector<Piece*> pieces;
		std::vector<std::pair<Piece*, Square>> moves;
};

#endif

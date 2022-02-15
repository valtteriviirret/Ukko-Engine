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
		void getEnginePieces();
		void getEngineMoves();
		void getPlayerPieces();
		void getPlayerMoves();
		void getAllSquares();
		void getMaterialBalance();
		int evaluate();
		double min(int depth);
		double max(int depth);
		double materialValue(bool player);
		Square* squares[8][8] = {};
		std::vector<Piece*> enginePieces;
		std::vector<Piece*> playerPieces;
		std::vector<Square> engineMoves;
		std::vector<Square> playerMoves;
		std::vector<std::pair<Piece*, Square>> moves;
		double engineMaterial;
		double playerMaterial;
};

#endif

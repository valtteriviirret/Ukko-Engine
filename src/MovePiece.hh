#ifndef MOVEPIECE_HH
#define MOVEPIECE_HH

#include <SDL2/SDL.h>
#include "Board.hh"
#include "Renderer.hh"
#include "PieceFactory.hh"

class MovePiece
{
	public:
		MovePiece(Board* board, PieceFactory* factory);
		~MovePiece();
		void StartUp();
		void render();
	private:
		Board* _board;
		PieceFactory* _factory;

};

#endif


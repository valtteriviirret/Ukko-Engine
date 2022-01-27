#ifndef GAME_HH
#define GAME_HH

#include "Window.hh"
#include "Piece.hh"
#include "PieceRenderer.hh"
#include "SquareManager.hh"
#include "Square.hh"
#include "GUI.hh"
#include "Board.hh"
#include "PieceFactory.hh"
#include "Settings.hh"
#include "LegalMoves.hh"
#include "Pieces.hh"
#include <vector>
#include <SDL2/SDL.h>

#define ARRSIZE(arr) (int)(sizeof(arr)/sizeof(arr[0]))

class Game
{
	public:
		Game();
		~Game();
		void updateGame();
		bool ApplicationShouldClose = false;
		void Move(Piece& source, Square target);
	private:
		void render();
		void update();
		void eventHandler();
		Board* board = nullptr;
		PieceFactory* pieces = nullptr;
		Window* window = nullptr;
		SDL_Event e;
        SDL_Point mousePos;
        Square* selectedSquare = nullptr;
        Square* originalSquare = nullptr;
        bool isSquareSelected = false;
        bool isPieceSelected = false;
        bool playerTurn;
};

#endif

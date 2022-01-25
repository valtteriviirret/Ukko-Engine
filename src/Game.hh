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
#include <SDL2/SDL.h>
#include "Settings.hh"
#include "LegalMoves.hh"
#include <vector>

#define ARRSIZE(arr) (int)(sizeof(arr)/sizeof(arr[0]))

class Game
{
	public:
		Game();
		~Game();
		void updateGame();
		bool ApplicationShouldClose = false;
	private:
		void render();
		void update();
		void eventHandler();
		void initPieces(int playerColor);
		Piece p[32];
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

#ifndef GAME_HH
#define GAME_HH

#include "Board.hh"
#include "GUI.hh"
#include "LegalMoves.hh"
#include "Piece.hh"
#include "PieceFactory.hh"
#include "PieceRenderer.hh"
#include "Settings.hh"
#include "Square.hh"
#include "SquareManager.hh"
#include "Window.hh"
#include "Pieces.hh"
#include "Move.hh"
#include "Engine.hh"
#include "Global.hh"
#include <vector>
#include <SDL2/SDL.h>

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
		Board* board = nullptr;
		PieceFactory* pieces = nullptr;
		Window* window = nullptr;
		SDL_Event e;
        SDL_Point mousePos;
        Square* selectedSquare = nullptr;
        Square* originalSquare = nullptr;
        bool isSquareSelected = false;
        bool isPieceSelected = false;
		Engine engine;
};

#endif

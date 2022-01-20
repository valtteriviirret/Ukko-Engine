#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Window.hh"
#include "Renderer.hh"
#include "Globals.hh"
#include "Board.hh"
#include "PieceRenderer.hh"
#include "Game.hh"


int main(int argc, char* argv[])
{
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    unsigned int frameTime;

    SDL_Init(SDL_INIT_EVERYTHING);

    // create window and renderer
    Window window;

	// initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) &imgFlags))
		std::cout << "SDL_image could not initialize! " << IMG_GetError() << "\n";

	// create new board
	board = new Board;

	// create pieces
	pieces = new PieceFactory;

	// initialize rendering pieces
	PieceRenderer::init(pieces);

	// create game
	game = new Game;

    // event handler
    SDL_Event e;

    // Game loop:
    while (!applicationShouldClose)
    {
        frameStart = SDL_GetTicks();

        // handle events on queue
        while(SDL_PollEvent(&e))
        {
			// quit the program with esc or traditionally
			if((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT)
    			applicationShouldClose = true;

            // resize window accordingly
            window.resize(e);

            // draw white screen
            Renderer::setColor(255, 255, 255);
            Renderer::clear();

            // render board
            board->render();

            // update positions of the pieces
            game->update(e);
        }

        // update screen
        Renderer::render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

	Quit();

    return 0;
}


void Quit()
{
	delete board;
	delete pieces;
	delete game;
	
	// close SDL
	IMG_Quit();
    SDL_Quit();
}

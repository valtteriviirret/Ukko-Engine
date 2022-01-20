#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Window.hh"
#include "Renderer.hh"
#include "Game.hh"

#define FPS 60

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

	// create new game
	Game* game = new Game;

    // event handler
    SDL_Event e;

	bool ApplicationShouldClose = false;

    // Game loop:
    while(!ApplicationShouldClose)
	{
        // handle events on queue
        while(SDL_PollEvent(&e))
        {
			// quit the program with esc or traditionally
			if((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT)
				ApplicationShouldClose = true;
			
			// resize window accordingly
			window.resize(e);
        }

        frameStart = SDL_GetTicks();

	    // draw white screen
		Renderer::setColor(255, 255, 255);
		Renderer::clear();

		// main rendering
		game->render();

		// update screen
		Renderer::render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

	// end the program
	delete game;
	IMG_Quit();
	SDL_Quit();

    return 0;
}


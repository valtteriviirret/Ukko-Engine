#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Game.hh"

#define FPS 60

int main(int argc, char* argv[])
{
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    unsigned int frameTime;

    SDL_Init(SDL_INIT_EVERYTHING);

	// initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) &imgFlags))
		std::cout << "SDL_image could not initialize! " << IMG_GetError() << "\n";

	// initialize SDL_TTF
	TTF_Init();
	if(TTF_Init() < 0)
		std::cout << "SDL_ttf could not initialize! " << TTF_GetError() << "\n";

	// create new game
	Game game;

    // Game loop:
    while(!game.ApplicationShouldClose)
	{
        frameStart = SDL_GetTicks();

		game.updateGame();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

	// end the program
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

    return 0;
}


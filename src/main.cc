#include "SDL2/SDL.h"
#include "Window.hh"
#include "Renderer.hh"
#include "globals.hh"
#include "ScreenSize.hh"
#include "iostream"

#define FPS 60

int main(int argc, char* argv[]) 
{
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    unsigned int frameTime;
	Window window;

    SDL_Init(SDL_INIT_EVERYTHING);
<<<<<<< HEAD

    window = SDL_CreateWindow("Chess", 0, 0, width, height, SDL_WINDOW_FULLSCREEN);

    if (window) {
        applicationShouldClose = false;
        std::cout << "Window created successfully. \n";
    } else {
        applicationShouldClose = true;
        std::cout << "Error creating window. Closing application. \n";
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Game loop:
    while (applicationShouldClose)
    {
        frameStart = SDL_GetTicks();
=======

	// event handler
	SDL_Event e;
>>>>>>> valtteri-dev

	// Game loop:
	while (!applicationShouldClose)
	{
		// handle events on queue
		while(SDL_PollEvent(&e) != 0)
		{
			// user requests quit
			if(e.type == SDL_QUIT)
				applicationShouldClose = true;
		}

		// draw white screen
		SDL_SetRenderDrawColor(Renderer::get(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Renderer::get());

		frameStart = SDL_GetTicks();

		Update();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
		
		// update screen
		SDL_RenderPresent(Renderer::get());

	}

	// close SDL
	SDL_Quit();

    return 0;
}

void Update()
{

}

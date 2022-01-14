#include "SDL.h"
#include "globals.hh"

#define FPS 60


int main(int argc, char* argv[]) {

    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    unsigned int frameTime;

    SDL_Window* window;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Game loop:
    while (!applicationShouldClose)
    {
        frameStart = SDL_GetTicks();

        Update();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);

    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void Update()
{

}

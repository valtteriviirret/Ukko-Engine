#ifndef UKKOSHAKKI_GLOBALS_HH
#define UKKOSHAKKI_GLOBALS_HH

#include "SDL2/SDL.h"
#include "Board.hh"

static void Update();
static void Render(SDL_Renderer* ren);
static void Quit();

static bool applicationShouldClose;

Board* board = nullptr;

#endif //UKKOSHAKKI_GLOBALS_HH
#ifndef UKKOSHAKKI_GLOBALS_HH
#define UKKOSHAKKI_GLOBALS_HH

#include "SDL2/SDL.h"
#include "Board.hh"
#include "PieceFactory.hh"
#include "Game.hh"

#define FPS 60

static void Render();
static void Quit();

static bool applicationShouldClose;

Board* board = nullptr;
PieceFactory* pieces = nullptr;
Game* game = nullptr;

#endif //UKKOSHAKKI_GLOBALS_HH

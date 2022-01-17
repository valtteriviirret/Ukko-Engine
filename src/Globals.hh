#ifndef UKKOSHAKKI_GLOBALS_HH
#define UKKOSHAKKI_GLOBALS_HH

#include "SDL2/SDL.h"
#include "Board.hh"
#include "PieceFactory.hh"

static void Update();
static void Render();
static void Quit();

static bool applicationShouldClose;

Board* board = nullptr;
PieceFactory* pieces = nullptr;

#endif //UKKOSHAKKI_GLOBALS_HH

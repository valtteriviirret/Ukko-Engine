#ifndef GLOBAL_HH
#define GLOBAL_HH

#include "Piece.hh"

static bool staleMate = false;
static bool playerTurn;
static Piece p[32];

// castling
static bool playerKingMoved = false;
static bool playerQsideRookMoved = false;
static bool playerKsideRookMoved = false;

static bool enemyKingMoved = false;
static bool enemyQsideRookMoved = false;
static bool enemyKsideRookMoved = false;



#endif

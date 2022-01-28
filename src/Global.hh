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

static bool engineKingMoved = false;
static bool engineQsideRookMoved = false;
static bool engineKsideRookMoved = false;



#endif

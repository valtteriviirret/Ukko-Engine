#include "Global.hh"

currentGameState Global::state = GAME_ON;

bool Global::playerTurn = true;

Square* Global::en_passant = nullptr;

double Global::evaluation = 0;

bool Global::playerKingMoved = false;
bool Global::engineKingMoved = false;
bool Global::playerQsideRookMoved = false;
bool Global::playerKsideRookMoved = false;
bool Global::engineQsideRookMoved = false;
bool Global::engineKsideRookMoved = false;

bool Global::playerCanCastleK = true;
bool Global::playerCanCastleQ = true;
bool Global::engineCanCastleK = true;
bool Global::engineCanCastleQ = true;

bool Global::playerInCheck = false;
bool Global::engineInCheck = false;

bool Global::inPromotion = false;



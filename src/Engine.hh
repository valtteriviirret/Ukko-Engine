#ifndef ENGINE_HH
#define ENGINE_HH

#include "Piece.hh"
#include "Pieces.hh"
#include "Global.hh"
#include "LegalMoves.hh"
#include "Move.hh"
#include "SquareManager.hh"
#include <vector>
#include <iostream>
#include <map>

class Engine
{
public:
    Engine();
    ~Engine();
    void PlayMove();
private:
    void getEnginePieces();
    void getEngineMoves();
    void getAllSquares();
    void getMaterialBalance();
    int evaluate();
    static double materialValue(bool player);
    Square* squares[8][8] = {};
    std::vector<Piece*> enginePieces;
    std::vector<Piece*> playerPieces;
    std::vector<std::pair<Piece*, Square>> moves;
    double engineMaterial;
    double playerMaterial;
};

#endif
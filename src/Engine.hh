#ifndef ENGINE_HH
#define ENGINE_HH

#include "Piece.hh"
#include "Pieces.hh"
#include "Global.hh"
#include "LegalMoves.hh"
#include "Move.hh"
#include "SquareManager.hh"
#include "MinMax.hh"
#include <vector>
#include <iostream>
#include <map>
#include <climits>

class Engine
{
public:
    Engine();
    ~Engine();
    bool PlayMove();
private:
    // get all pieces
    void getEnginePieces();
    void getPlayerPieces();

    // get all possible moves
    void getEngineMoves();
    void getPlayerMoves();

    // get the best possible move
    MinMax engineBest();
    MinMax playerBest();
    // helping functions
    void getMaterialBalance();
    void makeFakeMove(std::pair<Piece*, Square>* move);
    void fakeMoveNormal(std::pair<Piece*, Square>* move);
    int evaluate();
	double oldEvaluate();
    double materialValue(bool player);
    static double getValue(Square square);
    void clearEngine();
    void clearPlayer();

    // minmax
    MinMax mini(int depth);
    MinMax maxi(int depth);

    // moves
    std::vector<std::pair<Piece*, Square>> enginePairs;
    std::vector<std::pair<Piece*, Square>> playerPairs;

    double engineMaterial;
    double playerMaterial;

    std::vector<Piece*> enginePieces;
    std::vector<Piece*> playerPieces;

    Piece* target;
	Piece* source;
};

#endif

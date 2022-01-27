#include "Engine.hh"

Engine::Engine()
{

}

Engine::~Engine()
{
	
}

void Engine::PlayMove()
{
	// get positions of all pieces before every move (this is a little bloated solution but works now)
	getPieces();

	// evaluate good move
	evaluate();

	// get all avainable moves
	std::vector legalMoves = LegalMove::get(pieces[1]);

	Square move;
	
	for(auto& i : legalMoves)
	{
		move = legalMoves.at(0);	
	}
	
	// execute move
	Move::execute(pieces[1], move);


	// players move after turn
	playerTurn = true;
}

void Engine::getPieces()
{
	for(int i = 0; i < 32; i++)
	{
		pieces[i] = Pieces::get(i);
	}
}

void Engine::evaluate()
{

}


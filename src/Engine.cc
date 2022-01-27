#include "Engine.hh"

Engine::Engine()
{}

Engine::~Engine() = default;

void Engine::PlayMove()
{
	selectedPiece = pickRandomPiece();
	// get legal moves
	std::vector<Square> legalMoves = LegalMove::get(Pieces::get(selectedPiece));
	if (!isMoveDecided)
	{
		if ((int)LegalMove::get(Pieces::get(selectedPiece)).size() > 0) isMoveDecided = true;
		else selectedPiece = pickRandomPiece();
	}

	move = Sqr::getSquare(LegalMove::get(Pieces::get(selectedPiece)).at(selectedPiece).x,
						  LegalMove::get(Pieces::get(selectedPiece)).at(selectedPiece).y);

	// execute move
	Move::execute(Pieces::get(selectedPiece), move);
}

int Engine::pickRandomPiece()
{
	return rand() % 15;
}
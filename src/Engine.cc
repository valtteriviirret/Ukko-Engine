#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

void Engine::PlayMove()
{
	// get random num
	int piece = pickPiece();

	// this is bad
	Square s;

	// get moves for random num
	std::vector<Square> v = LegalMove::getLegal(Pieces::get(piece));

	// get piece that has legal moves
	for (;;)
	{
		if (!v.empty())
			break;
		else
		{
			piece = pickPiece();
			v = LegalMove::getLegal(Pieces::get(piece));
		}
	}

	for (auto &i: v)
	{
		s = Sqr::getSquare(i.x, i.y);
		if (Sqr::getSquare(i.x, i.y).piece.type != NONE && Sqr::getSquare(i.x, i.y).piece.user == PLAYER)
			break;
	}
	Move::execute(Pieces::get(piece), s);
}

int Engine::pickPiece()
{
	// TODO: Evaluate the board. Pick pieces based on player's and AI's legal moves.
	return rand() % 16;
}

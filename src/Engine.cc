#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

void Engine::PlayMove()
{
	// get random num
	int piece = pickPiece();
	int count = 0;
	Square s;

	// get moves for random num
	std::vector<Square> v = LegalMove::get(Pieces::get(piece));

	for(;;)
	{
		if (count == 15)
		{
			staleMate = true;
			break;
		}
		if(!v.empty() && Pieces::get(piece).alive)
			break;
		else
		{
			piece = pickPiece();
			v = LegalMove::get(Pieces::get(piece));
			count++;
		}
	}

	if(!staleMate)
	{
		for (int i = 0; i < v.size(); i++)
			s = Sqr::getSquare(v[i].x, v[i].y);

		Move::execute(Pieces::get(piece), s);
	}
}

int Engine::pickPiece()
{
	return rand() % 15;
}
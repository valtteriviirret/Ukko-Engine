#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

void Engine::PlayMove()
{
	moves.clear();

	// get fresh squares
	getAllSquares();
	
	// get legal moves
	getAllMoves();

	int n = pickPiece();

	while(Global::state == GAME_ON)
	{
		if(moves.find(n) == moves.end())
		{
			n = pickPiece();
		}
		else
			break;
	}

	if(moves.empty())
	{
		if(Global::engineInCheck)
		{
			Global::state = VICTORY;
			Global::playerTurn = true;
		}
		else
		{
			Global::state = DRAW;
			Global::playerTurn = true;
		}
	}

	else
		Move::execute(Pieces::get(moves.extract(n).key()), moves.at(n));
}

int Engine::pickPiece()
{
	// TODO: Evaluate the board. Pick pieces based on player's and AI's legal moves.
	return rand() % 16;
}

// get all squares
void Engine::getAllSquares()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			squares[i][j] = Sqr::squareHelper(i, j);
}

void Engine::makeFakeMove(Piece source, Square target)
{
	// source goes to target
	squares[target.x][target.y]->piece = source;

	// source is set to zero
	squares[source.x][source.y]->piece = ghost(source.x, source.y);
}


void Engine::getAllMoves()
{
	for(int i = 0; i < 16; i++)
	{
		std::vector<Square> temp = LegalMove::getLegal(Pieces::get(i));

		for(auto j = temp.begin(); j < temp.end(); j++)
		{
			moves.insert(std::pair<int, Square>(i, *j));
		}
	}
}



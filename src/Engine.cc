#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

bool Engine::PlayMove()
{
	pieces.clear();

	// get fresh squares
	getAllSquares();

	getAllMoves();

	int n = pickPiece();

	if (!moves.empty())
	{
		Move::execute(moves.at(n).first, moves.at(n).second);
		return true;
	}
	else
	{
		Global::state = VICTORY;
		return false;
	}
}

int Engine::pickPiece()
{
	// TODO: Evaluate the board. Pick pieces based on player's and AI's legal moves.
	return rand() % 16;
}

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


void Engine::getAllPieces()
{
	for(int i = 0; i < 16; i++)
		pieces.push_back(&Pieces::get(i));
}

void Engine::getAllMoves()
{
	getAllPieces();

	for(int i = 0; i < (int)pieces.size(); i++)
	{
		std::vector<Square> temp = LegalMove::getLegal(Pieces::get(i));

		for(int j = 0; j < (int)temp.size(); j++)
		{
			moves.push_back(std::make_pair(pieces[i], temp[j]));
		}
	}
}


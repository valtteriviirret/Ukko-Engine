#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

bool Engine::PlayMove()
{
	// clear existing stuff
	pieces.clear();
	moves.clear();

	// get fresh squares
	getAllSquares();

	// get all the avainable moves
	getAllMoves();

	if (!moves.empty())
	{
		int n = evaluate();
		Move::execute(moves.at(n).first, moves.at(n).second);
		return true;
	}
	else
	{
		if(Global::engineInCheck)
			Global::state = VICTORY;
		else
			Global::state = DRAW;
		return false;
	}
}

int Engine::evaluate()
{
	// TODO: Evaluate the board. Pick pieces based on player's and AI's legal moves.
	getMaterialBalance();

	return 0;
}

void Engine::getMaterialBalance()
{
	engineMaterial = materialValue(false);
	playerMaterial = materialValue(true);
}

double Engine::materialValue(bool player)
{
	int a = player ? 16 : 0;
	int b = player ? 32 : 16;
	double n = 0;

	for(int i = a; i < b; i++)
	{
		switch(Pieces::get(i).type)
		{
			case KING: break;
			case NONE: break;
			case ROOK: n += 5; break;
			case PAWN: n += 1; break;
			case QUEEN: n += 9; break;
			case KNIGHT: n += 3; break;
			case BISHOP: n += 3.25; break;
		}	
	}

	// return materialvalue
	return n;
}

void Engine::getAllSquares()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			squares[i][j] = Sqr::squareHelper(i, j);
}

void Engine::makeFakeMove(std::pair<Piece*, Square> move)
{
	// source goes to target
	squares[move.second.x][move.second.y]->piece = *move.first;

	// source is set to zero
	squares[move.first->x][move.first->y]->piece = ghost(move.first->x, move.first->y);
}

void Engine::getAllPieces()
{
	for(int i = 0; i < 16; i++)
		pieces.push_back(&Pieces::get(i));
}

void Engine::getAllMoves()
{
	// get all pieces first
	getAllPieces();

	for(int i = 0; i < (int)pieces.size(); i++)
	{
		// don't include captured pieces
		if(pieces[i]->type != 6 && pieces[i]->user == ENGINE)
		{
			// get legal moves for the piece
			std::vector<Square> temp = LegalMove::getLegal(Pieces::get(i));

			// make pairs from piece and where the 
			for(int j = 0; j < (int)temp.size(); j++)
				moves.push_back(std::make_pair(pieces[i], temp[j]));
		}
	}
}


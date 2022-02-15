#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

bool Engine::PlayMove()
{
	// clear existing stuff
	enginePieces.clear();
	moves.clear();

	// get fresh squares
	getAllSquares();

	// get all the avainable moves
	getEngineMoves();

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

	double calc = engineMaterial - playerMaterial;
	double eval = calc / 20;
	Global::evaluation = eval;	

	
	// return eval
	return 0;
}


void Engine::getMaterialBalance()
{
	engineMaterial = materialValue(false);
	playerMaterial = materialValue(true);
}

double Engine::max(int depth)
{
	if(depth == 0)
		return evaluate();

	double max = -std::numeric_limits<double>::infinity();
	int score;

	getEngineMoves();
	for(int i = 0; i < (int)engineMoves.size(); i++)
	{
		score = min(depth - 1);
		if(score > max)
			max = score;
	}
	
	return max;
}

double Engine::min(int depth)
{
	if(depth == 0)
		return evaluate();
	
	double min = -std::numeric_limits<double>::infinity();
	int score;
	
	getPlayerMoves();
	for(int i = 0; i < (int)playerMoves.size(); i++)
	{
		score = max(depth - 1);
		if(score < min)
			min = score;
	}
	
	return min;
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

void Engine::getEnginePieces()
{
	for(int i = 0; i < 16; i++)
		enginePieces.push_back(&Pieces::get(i));
}

void Engine::getPlayerPieces()
{
	for(int i = 16; i < 32; i++)
		playerPieces.push_back(&Pieces::get(i));
}

void Engine::getEngineMoves()
{
	// get all pieces first
	engineMoves.clear();
	getEnginePieces();

	for(int i = 0; i < (int)enginePieces.size(); i++)
	{
		// filter pieces
		if(enginePieces[i]->type != 6 && enginePieces[i]->user == ENGINE)
		{
			// get legal moves for the piece
			std::vector<Square> temp = LegalMove::getLegal(Pieces::get(i));

			// make pairs from piece and where the 
<<<<<<< HEAD
<<<<<<< HEAD
			for(int j = 0; j < (int)temp.size(); j++)
			{
				moves.push_back(std::make_pair(enginePieces[i], temp[j]));
				engineMoves.push_back(temp[j]);
			}
=======
			for(auto & j : temp)
				moves.emplace_back(pieces[i], j);
>>>>>>> daa3566 (refactoring)
=======
			for(auto & j : temp)
				moves.emplace_back(pieces[i], j);
>>>>>>> daa3566 (refactoring)
		}
	}
}

void Engine::getPlayerMoves()
{
	playerMoves.clear();
	getPlayerPieces();

	for(int i = 16; i < 32; i++)
	{
		if(playerPieces[i]->type != 6 && playerPieces[i]->user == PLAYER)
		{
			// get legal moves
			std::vector<Square> temp = LegalMove::get(Pieces::get(i));

			for(int j = 0; j < (int)temp.size(); j++)
			{
				playerMoves.push_back(temp[j]);
			}
		}
	}
}







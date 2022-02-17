#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

bool Engine::PlayMove()
{
	// clear existing stuff
	enginePieces.clear();
	playerPieces.clear();
	engineMoves.clear();
	playerMoves.clear();
	enginePairs.clear();
	playerPairs.clear();

	// get fresh squares
	getAllSquares();

	// get all the avainable moves
	getEngineMoves();

	if(!enginePairs.empty())
	{
		//int n = 0;
		//Move::execute(enginePairs.at(n).first, enginePairs.at(n).second);

		MinMax xd = engineBest();
		Move::execute(xd.bestMove.first, xd.bestMove.second);
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

// returns the best move for the engine
MinMax Engine::engineBest()
{
	MinMax obj;

	// get fresh engine moves
	getEngineMoves();

	std::pair<Piece*, Square>* m = nullptr; 

	double balance = evaluate();

	for(int i = 0; i < (int)enginePairs.size(); i++)
	{
		// get fresh squares
		getAllSquares();

		// do the fake move
		makeFakeMove(enginePairs[i]);

		// evaluate move
		double a = evaluate();

		if(a > balance)
		{
			m = &enginePairs[i];
			balance = a;
		}
	}

	// set all squares back to normal
	getAllSquares();

	// if "good move" is not selected return first possible move
	if(!m)
		m = &enginePairs[0];
	
	obj.evaluation = balance;
	obj.bestMove = *m;

	return obj;
}

MinMax Engine::playerBest()
{
	MinMax obj;

	getPlayerMoves();
	
	std::pair<Piece*, Square>* m = nullptr;

	double balance = evaluate();

	for(int i = 0; i < (int)playerPairs.size(); i++)
	{
		getAllSquares();

		makeFakeMove(playerPairs[i]);

		double a = evaluate();

		if(a > balance)
		{
			m = &playerPairs[i];
			balance = a;
		}
	}

	getAllSquares();

	if(!m)
		m = &enginePairs[0];
	
	obj.evaluation = balance;
	obj.bestMove = *m;

	return obj;
}

double Engine::evaluate()
{
	getMaterialBalance();

	// king multiplier
	// center multiplier
	// line multiplier

	double calc = engineMaterial - playerMaterial;
	double eval = calc / 20;
	Global::evaluation = eval;	

	return eval;
}


void Engine::getMaterialBalance()
{
	engineMaterial = materialValue(false);
	playerMaterial = materialValue(true);
}

/*
MinMax Engine::max(int depth)
{
	if(depth == 0)
		return evaluate();

	double max = -std::numeric_limits<double>::infinity();
	int score;

	getEngineMoves();
	for(int i = 0; i < (int)engineMoves.size(); i++)
	{
		score = min(depth - 1).evaluation;
		if(score > max)
			max = score;
	}
	
	return max;
}

MinMax Engine::min(int depth)
{
	if(depth == 0)
		return evaluate();
	
	double min = std::numeric_limits<double>::infinity();
	int score;
	
	getPlayerMoves();
	for(int i = 0; i < (int)playerMoves.size(); i++)
	{
		score = max(depth - 1).evaluation;
		if(score < min)
			min = score;
	}
	
	return min;
}
*/

double Engine::materialValue(bool player)
{
	double n = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(player && squares[i][j].piece.user == PLAYER)
				n += getValue(squares[i][j]);

			if((!player) && squares[i][j].piece.user == ENGINE)
				n += getValue(squares[i][j]);
		}
	}
	
	return n;
}

double Engine::getValue(Square square)
{
	double n = 0;
	switch(square.piece.type)
	{
		case KING: n += 1000; break; // might not be final
		case NONE: break;
		case ROOK: n += 5; break;
		case PAWN: n += 1; break;
		case QUEEN: n += 9; break;
		case KNIGHT: n += 3; break;
		case BISHOP: n += 3.25; break;
	}
	return n;
}

void Engine::getAllSquares()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			squares[i][j] = Sqr::squareCopy(i, j);
}

void Engine::makeFakeMove(std::pair<Piece*, Square> move)
{
	// source goes to target
	squares[move.second.x][move.second.y].piece = *move.first;

	// source is set to zero
	squares[move.first->x][move.first->y].piece = ghost(move.first->x, move.first->y);
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
			for(int j = 0; j < (int)temp.size(); j++)
			{
				enginePairs.push_back(std::make_pair(enginePieces[i], temp[j]));
				engineMoves.push_back(temp[j]);
			}
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
				playerPairs.push_back(std::make_pair(playerPieces[i], temp[j]));
				playerMoves.push_back(temp[j]);
			}
		}
	}
}







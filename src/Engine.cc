#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

bool Engine::PlayMove()
{
	// clear existing stuff
	clearEngine();
	clearPlayer();

	// get fresh squares
	getAllSquares();

	// check if engine has moves
	getEngineMoves();

	if(!enginePairs.empty())
	{
		clearEngine();

		MinMax xd = engineBest();
		Move::execute(xd._bestMove.first, xd._bestMove.second);
		
		//MinMax m = max(2);

		//std::cout << m._bestMove.second.piece.type;

		//Move::execute(m._bestMove.first, m._bestMove.second);
	
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
	getEngineMoves();

	std::pair<Piece*, Square>* m = nullptr; 

	double balance = evaluate();

	for(int i = 0; i < (int)enginePairs.size(); i++)
	{
		// do the fake move
		//makeFakeMove(enginePairs[i]);

		// evaluate move
		double a = evaluate() + 0.01;

		if(a > balance)
		{
			m = &enginePairs[i];
			balance = a;
		}

		//fakeMoveNormal(enginePairs[i]);
	}

	// set all squares back to normal
	//getAllSquares();

	return MinMax(balance, *m);
}

MinMax Engine::playerBest()
{
	std::pair<Piece*, Square>* m = nullptr;

	double balance = evaluate();

	for(int i = 0; i < (int)playerPairs.size(); i++)
	{
		makeFakeMove(playerPairs[i]);

		double a = evaluate() + 0.01;

		if(a > balance)
		{
			m = &playerPairs[i];
			balance = a;
		}

	}

	getAllSquares();

	return MinMax(balance, *m);
}

double Engine::evaluate()
{
	// king multiplier
	// center multiplier
	// line multiplier

	getMaterialBalance();
	double calc = engineMaterial - playerMaterial;
	
	// this is just an example conversion
	double eval = calc / 20;
	
	// maybe we have some use for this later dunno
	Global::evaluation = eval;
	return eval;
}


void Engine::getMaterialBalance()
{
	engineMaterial = materialValue(false);
	playerMaterial = materialValue(true);
}

MinMax Engine::max(int depth)
{
	if(depth == 0) return engineBest();

	getEngineMoves();

	int score;
	int max = INT_MIN;
	MinMax bestMove;

	for(int i = 0; i < (int)enginePairs.size(); i++)
	{
		//getAllSquares();

		// make fake move
		//makeFakeMove(enginePairs[i]);

		// call to min
		MinMax move = min(depth - 1);
		score = move._evaluation;
		if(score > max)
		{
			max = score;
			bestMove = MinMax(move._evaluation, move._bestMove);
		}

	}

	return bestMove;
}

MinMax Engine::min(int depth)
{
	if(depth == 0) return playerBest();

	getPlayerMoves();

	int score;
	int min = INT_MAX;
	MinMax bestMove;
	
	for(int i = 0; i < (int)playerPairs.size(); i++)
	{
		//makeFakeMove(playerPairs[i]);
		MinMax move = max(depth - 1);
		score = move._evaluation;
		if(score < min)
		{
			min = score;
			bestMove = MinMax(move._evaluation, move._bestMove);
		}
	}
	
	return bestMove;
}

//TODO rewrite this
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

// something is up with these

void Engine::makeFakeMove(std::pair<Piece*, Square> move)
{
	// get the target piece
	target = &squares[move.second.x][move.second.y].piece;

	// source goes to target
	squares[move.second.x][move.second.y].piece = *move.first;

	// source is set to zero
	squares[move.first->x][move.first->y].piece = ghost(move.first->x, move.first->y);
}

void Engine::fakeMoveNormal(std::pair<Piece*, Square> move)
{
	// source goes to normal
	squares[move.first->x][move.first->y].piece = *move.first;

	// target goes to normal
	squares[move.second.x][move.second.y].piece = *target;
}

void Engine::getEnginePieces()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(Sqr::getSquare(i, j).piece.user == ENGINE)
				enginePieces.push_back(&Pieces::getReal(&Sqr::getSquare(i, j).piece));
}

void Engine::getPlayerPieces()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(Sqr::getSquare(i, j).piece.user == PLAYER)
				enginePieces.push_back(&Pieces::getReal(&Sqr::getSquare(i, j).piece));
}

void Engine::getEngineMoves()
{
	// get all pieces first
	clearEngine();
	getEnginePieces();

	for(auto& i : enginePieces)
	{
		// get legal moves for the piece
		std::vector<Square> moves = LegalMove::getLegal(*i);

		for(auto& j : moves)
		{
			enginePairs.push_back(std::make_pair(i, j));
			engineMoves.push_back(j);
		}
	}
}

void Engine::getPlayerMoves()
{
	clearPlayer();
	getPlayerPieces();

	for(auto& i : playerPieces)
	{
		std::vector<Square> moves = LegalMove::getLegal(*i);
		for(auto& j : moves)
		{
			playerPairs.push_back(std::make_pair(i, j));
			playerMoves.push_back(j);
		}
	}
}

void Engine::clearEngine()
{
	enginePieces.clear();
	engineMoves.clear();
	enginePairs.clear();
}

void Engine::clearPlayer()
{
	playerPieces.clear();
	playerMoves.clear();
	playerPairs.clear();
}




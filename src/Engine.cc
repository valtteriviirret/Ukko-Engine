#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

bool Engine::PlayMove()
{
	setOriginalPieces();

	rounds = 2;

	// clear existing stuff
	clearEngine();
	clearPlayer();

	// check if engine has moves
	getEngineMoves();

	if(!enginePairs.empty())
	{
		clearEngine();

		MinMax m = maxi(rounds);

		// set position back to normal
		//getOriginalPieces();

		Move::execute(Pieces::getReal(m._bestMove->first), &m._bestMove->second, true);
	
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

	double balance = oldEvaluate();

	for(int i = 0; i < (int)enginePairs.size(); i++)
	{
		// evaluate move
		double a = oldEvaluate() + 0.01;

		if(a > balance)
		{
			m = &enginePairs[i];
			balance = a;
		}
	}

	return MinMax(balance, m);
}

MinMax Engine::playerBest()
{
	getPlayerMoves();

	std::pair<Piece*, Square>* m = nullptr;

	double balance = oldEvaluate();

	for(int i = 0; i < (int)playerPairs.size(); i++)
	{
		double a = oldEvaluate() + 0.01;

		if(a > balance)
		{
			m = &playerPairs[i];
			balance = a;
		}
	}

	return MinMax(balance, m);
}

double Engine::oldEvaluate()
{
	// king multiplier
	
	Piece* engineKing = nullptr;
	Piece* playerKing = nullptr;
	
	// FOR ENGINE
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(Sqr::getSquare(i, j).piece.user == ENGINE)
				if(Sqr::getSquare(i, j).piece.type == KING)
					engineKing = &Sqr::getSquare(i, j).piece;
					
	// POSITION
	// OWN PIECES NEAR ++
	// ENEMY PIECES NEAR --
	
	
	
	
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

void Engine::setOriginalPieces()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			oldPieces[i][j] = Sqr::getSquare(i, j);
}

void Engine::getOriginalPieces()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			Sqr::squareHelper(i, j)->piece = oldPieces[i][j].piece;
}

/*
int Engine::evaluate()
{
    int selection = 0;
    double score = 0;

    for (int i = rand() % 16; i < (int)enginePairs.size(); i++)
    {
        Square initialPos = Sqr::getSquare(enginePairs.at(i).first->x, enginePairs.at(i).first->y);
        Piece& initialPiece = enginePairs.at(i).second.piece;
        Move::execute(enginePairs.at(i).first, enginePairs.at(i).second);
        getMaterialBalance();

        if (score < engineMaterial / playerMaterial)
        {
            selection = i;
            score = engineMaterial / playerMaterial;
        }

        Move::execute(enginePairs.at(i).first, initialPos);
        Sqr::squareHelper(enginePairs.at(i).second.x, enginePairs.at(i).second.y)->piece = initialPiece;
    }

    return selection;
}
*/

void Engine::getMaterialBalance()
{
	engineMaterial = materialValue(false);
	playerMaterial = materialValue(true);
}

MinMax Engine::maxi(int depth)
{
	if(depth == 0)
		return engineBest();

	getEngineMoves();

	int score = 0;
	int max = INT_MIN;
	std::pair<Piece*, Square>* m = nullptr;

	for(int i = 0; i < (int)enginePairs.size(); i++)
	{
		if(depth == rounds && i != 0)
			getOriginalPieces();

		// make fake move
		makeFakeMove(&enginePairs[i]);

		// call to min
		MinMax move = mini(depth - 1);

		score = move._evaluation;

		if(score > max)
		{
			max = score;
			m = move._bestMove;
		}
	}
	
	return MinMax(max, m);
}

MinMax Engine::mini(int depth)
{
	if(depth == 0) 
		return playerBest();

	getPlayerMoves();

	int score = 0;
	int min = INT_MAX;
	std::pair<Piece*, Square>* m = nullptr;

	for(int i = 0; i < (int)playerPairs.size(); i++)
	{
		makeFakeMove(&playerPairs[i]);
		
		MinMax move = maxi(depth - 1);
		score = move._evaluation;

		if(score < min)
		{
			min = score;
			m = move._bestMove;
		}
	}
	
	return MinMax(min, m);
}

double Engine::materialValue(bool player)
{
	double n = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(player && Sqr::getSquare(i, j).piece.user == PLAYER)
				n += getValue(Sqr::getSquare(i, j));

			if((!player) && Sqr::getSquare(i, j).piece.user == ENGINE)
				n += getValue(Sqr::getSquare(i, j));
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

void Engine::makeFakeMove(std::pair<Piece*, Square>* move)
{
	Move::execute(Pieces::getReal(move->first), &oldPieces[move->second.x][move->second.y], false);
}

void Engine::getEnginePieces()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(oldPieces[i][j].piece.user == ENGINE)
				enginePieces.push_back(&oldPieces[i][j].piece);
}

void Engine::getPlayerPieces()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			if(oldPieces[i][j].piece.user == PLAYER)
				playerPieces.push_back(&oldPieces[i][j].piece);
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
			enginePairs.push_back(std::make_pair(i, j));
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
			playerPairs.push_back(std::make_pair(i, j));
	}
}

void Engine::clearEngine()
{
	enginePieces.clear();
	enginePairs.clear();
}

void Engine::clearPlayer()
{
	playerPieces.clear();
	playerPairs.clear();
}




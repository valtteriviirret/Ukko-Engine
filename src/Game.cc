#include "Game.hh"

Game::Game()
{
	// create new window and renderer
	window = new Window;

	// make board
	board = new Board;

	// create pieces
	pieces = new PieceFactory;

	// initialize helping namespace
	PieceRenderer::init(pieces);

	// initialize pieces in their correct places
	Pieces::init();
	
	// white starts game
	Settings::PlayerColor == WHITE ? playerTurn = true : playerTurn = false;
}

Game::~Game()
{
	delete pieces;
	delete board;
	delete window;
}

void Game::updateGame()
{
	eventHandler();
	update();
	render();
}

void Game::eventHandler()
{
	while (SDL_PollEvent(&e))
	{
		window->resize(e);

		// close application
		if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT)
			ApplicationShouldClose = true;

		// when mouse is moved
		if (e.type == SDL_MOUSEMOTION)
		{
			// Get mouse position
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
		}

		// when mouse is clicked
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			// get mouse position
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
			selectedSquare = GUI::onSelect(mousePos);

			// render possible moves
			if (selectedSquare->piece.type != NONE && selectedSquare->piece.user == PLAYER)
			{
				originalSquare = selectedSquare;
				legalMoves = LegalMove::getLegal(originalSquare->piece);
				isPieceSelected = true;
			}
		}
	}
}

// update turns
void Game::update()
{
	playerTurn ? playerPlayMove() : enginePlayMove();
	
	gameState();
}

void Game::gameState()
{
	switch(currentGameState)
	{
		case VICTORY:
			Settings::PlayerColor == WHITE ? std::cout << "1-0" : std::cout << "0-1";
			ApplicationShouldClose = true;
			break;
		
		case DEFEAT:
			Settings::PlayerColor == WHITE ? std::cout << "0-1" : std::cout << "1-0";
			ApplicationShouldClose = true;
			break;

		case DRAW:
			std::cout << "1/2";
			ApplicationShouldClose = true;

		// game is in progress
		default: break;
	}
}

void Game::render()
{
	// make gray background
	Renderer::setColor(64, 64, 64);
	Renderer::clear();

	// render console
	for (auto & i : console)
		if (i)
			i->render();

	// render board
	board->render();

	if (selectedSquare)
	{
		// color selected square
		Renderer::setColor(0, 0, 255);
		Renderer::fillRect(selectedSquare->rect);
	}

	for(auto& legalMove : legalMoves)
	{
		if(selectedSquare && playerTurn)
		{
			// color legal moves
			Renderer::setColor(255, 0, 0);
			Renderer::fillRect(legalMove.rect);
		}
	}

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			// color the square where the mouse is
			if (GUI::onMouseRollOver(mousePos, Sqr::getSquare(i, j).rect))
			{
				Renderer::setColor(0, 255, 0);
				Renderer::fillRect(Sqr::getSquare(i, j).rect);
			}
		}
	}
	
	// render pieces
	for (int i = 0; i < 32; i++)
		PieceRenderer::renderInPosition(Pieces::get(i));

	// main rendering
	Renderer::render();
}


// Player's move logic:
void Game::playerPlayMove()
{
	// if selected new square
	if (selectedSquare != originalSquare && isPieceSelected)
	{
		// get legal moves
		for (auto &legalMove: legalMoves)
		{
			// if new click is in legal moves
			if (selectedSquare->x == legalMove.x && selectedSquare->y == legalMove.y)
			{
				// loop players pieces to find the correct one
				for (int j = 16; j < 32; j++)
				{
					// loop pieces and find correct one
					if (originalSquare == &Sqr::getSquare(Pieces::get(j).x, Pieces::get(j).y))
					{
						GameManager::update(false);

						// make the move
						Move::execute(Pieces::get(j), legalMove);

						legalMoves.clear();
						updateConsole();
						isPieceSelected = false;
						playerTurn = false;
					}
					else if (legalMoves.empty() && playerTurn)
					{
						if(Global::playerInCheck)
							currentGameState = DEFEAT;
						else
							currentGameState = DRAW; 
					}
				}
			}
		}
	}
}

// Engine's move:
void Game::enginePlayMove()
{
	GameManager::update(true);

	// ???
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	engine.PlayMove();
	updateConsole();
	playerTurn = true;
}

// update console output
void Game::updateConsole()
{
	console.push_back(new Text(Move::getName(), playerTurn));
	consoleIndex++;

	for (auto& i : console)
		i->position.y -= 18;
}

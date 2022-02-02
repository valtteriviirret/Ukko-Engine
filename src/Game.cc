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

// according to valgrind in this function there is uninitialized value, check it out!
void Game::eventHandler()
{
	while (SDL_PollEvent(&e))
	{
		window->resize(e);

		// close application
		if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT)
			ApplicationShouldClose = true;

		if (e.type == SDL_MOUSEMOTION)
		{
			// Get mouse position
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
		}

		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			// get mouse position
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
			selectedSquare = GUI::onSelect(mousePos);

			isSquareSelected = false;

			// render possible moves
			for (int i = 0; i < 32; i++)
			{
				if (Pieces::get(i).x == selectedSquare->piece.x && Pieces::get(i).y == selectedSquare->piece.y)
				{
					// show enemy legal moves
					if (Pieces::get(i).user != PLAYER && Settings::showEnemyLegalMoves)
						isSquareSelected = true;

					if (Pieces::get(i).user == PLAYER)
					{
						originalSquare = selectedSquare;
						isSquareSelected = true; // rendering
						isPieceSelected = true; // select enemy
					}
				}
			}
		}
	}
}

void Game::update()
{
	if (playerTurn)
	{
		playerPlayMove();

		//if(Global::playerInCheck)
			//std::cout << "Player in check!\n";
			
	}
	else
	{
		Engine::PlayMove();

		GameManager::update();

		updateConsole();

		if(Global::engineInCheck)
			std::cout << "engine in check\n";

		// players turn
		playerTurn = true;
	}
}

void Game::updateConsole()
{
	console.push_back(new Text(Move::getName(), playerTurn));
	consoleIndex++;
	for (int i = 0; i < (int)console.size(); i++)
		console[i]->position.y -= 18;
}


// render pieces in their current positions
void Game::render()
{
	// make gray background
	Renderer::setColor(64, 64, 64);
	Renderer::clear();

	// render console
	for (int i = 0; i < (int)console.size(); i++)
		if (console[i])
			console[i]->render();

	// render board
	board->render();

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

	for(int i = 0; i < (int)legalMoves.size(); i++)
	{
		if(selectedSquare && playerTurn)
		{
			// color legal moves
			Renderer::setColor(255, 0, 0);
			Renderer::fillRect(legalMoves.at(i).rect);

			// color selected square
			Renderer::setColor(0, 0, 255);
			Renderer::fillRect(selectedSquare->rect);
		}
		else
			selectedSquare = nullptr;
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
	// if selected in eventHandler
	if (isPieceSelected)
	{
		// get the legal moves
		legalMoves = LegalMove::get(originalSquare->piece);

		// if selected new square
		if (selectedSquare != originalSquare)
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
							// make the move
							Move::execute(Pieces::get(j), legalMove);
							
							updateConsole();
							GameManager::update();
							playerTurn = false;
						}
					}
				}
				else
					isPieceSelected = false;
			}
		}
	}
}



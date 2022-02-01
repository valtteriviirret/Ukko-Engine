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
	delete consoleText;
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

			// render possible moves
			for (int i = 0; i < 32; i++)
			{
				if (Pieces::get(i).x == selectedSquare->piece.x && Pieces::get(i).y == selectedSquare->piece.y)
				{
					if (Pieces::get(i).user == PLAYER)
						isSquareSelected = true;

					// whats up with this
					if (Pieces::get(i).user != PLAYER && Settings::showEnemyLegalMoves)
						isSquareSelected = true;

					if (Pieces::get(i).user == PLAYER)
					{
						originalSquare = selectedSquare;
						isPieceSelected = true;
					}
				}

			}

		}
	}
}

void Game::update()
{
	if (consoleIndex == 999)
	{
		delete console[consoleIndex];
		consoleIndex = 0;
	}
	if (playerTurn)
	{
		playerPlayMove();
		updateBoard();
	}
	else
	{
		selectedSquare = nullptr;
		Engine::PlayMove();
		console[consoleIndex] = new Text(Move::getName(), playerTurn);
		consoleIndex++;

		for (int i = 0; i < consoleIndex; i++)
			console[i]->position.y -= 18;

		updateBoard();
		playerTurn = true;
	}
}


// render pieces in their current positions
void Game::render()
{
	// make gray background
	Renderer::setColor(64, 64, 64);
	Renderer::clear();

	// render board
	board->render();

	// color the square where to mouse is
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (GUI::onMouseRollOver(mousePos, Sqr::getSquare(x, y).rect))
			{
				Renderer::setColor(0, 255, 0);
				Renderer::fillRect(Sqr::getSquare(x, y).rect);
			}
			if (isSquareSelected)
			{
				// selected square must be on board
				if (selectedSquare != nullptr)
				{
					// get legal moves of the piece in the square
					std::vector<Square> v = LegalMove::get(selectedSquare->piece);

					Renderer::setColor(0, 0, 255);

					// color the selected square
					Renderer::fillRect(selectedSquare->rect);

					// color legal moves of the piece in the selected square
					Renderer::setColor(255, 0, 0);
					for (auto &i: v)
					{
						Renderer::fillRect(i.rect);
					}
				}
			}
		}
	}

	// render pieces
	for (int i = 0; i < 32; i++)
		PieceRenderer::renderInPosition(Pieces::get(i));

	for (int i = 0; i <= consoleIndex; i++)
	{
		if (console[i] != nullptr)
			console[i]->render();
	}

	// main rendering
	Renderer::render();
}


// Player's move logic:
void Game::playerPlayMove()
{
	// if selected in eventHandler
	if (isPieceSelected)
	{
		// get legal moves
		std::vector<Square> legalMoves = LegalMove::get(originalSquare->piece);

		// if selected new square
		if (selectedSquare != originalSquare)
		{
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
							console[consoleIndex] = new Text(Move::getName(), playerTurn);
							consoleIndex++;

							for (int i = 0; i < consoleIndex; i++)
								console[i]->position.y -= 18;

							updateBoard();
							playerTurn = false;
						}
					}
				}

					// player selects wrong piece
				else
					isPieceSelected = false;
			}
		}
	}
}


void Game::updateBoard()
{
	for(int i = 0; i < 16; i++)
	{
		std::vector v = LegalMove::get(Pieces::get(i));

		for(int j = 0; j < (int)v.size(); j++)
		{
			// see checks
			Global::playerInCheck = true;
			if(Pieces::get(j).type == 5)
				Global::playerInCheck = false;

			Global::playerCanCastleK = true;
			Global::playerCanCastleQ = true;

			// possibility to castle
			if(!Global::playerKingMoved)
			{
				if(!Global::playerKsideRookMoved)
				{
					if((v.at(j).x == 5 && v.at(j).y == 7) || (v.at(j).x == 6 && v.at(j).y == 7))
						Global::playerCanCastleK = false;
				}
				else
					Global::playerCanCastleK = false;
				
				if(!Global::playerQsideRookMoved)
				{
					if((v.at(j).x == 1 && v.at(j).y == 7) || (v.at(j).x == 2 && v.at(j).y == 7))
						Global::playerCanCastleQ = false;
				}
				else
					Global::playerCanCastleQ = false;
			}
			else
			{
				Global::playerCanCastleQ = false;
				Global::playerCanCastleK = false;
			}
		}
	}
	for(int i = 16; i < 32; i++)
	{
		std::vector v = LegalMove::get(Pieces::get(i));
		for(int j = 0; j < (int)v.size(); j++)
		{
			// see checks
			Global::engineInCheck = false;
			if(Pieces::get(j).type == 5)
				Global::engineInCheck = true;
		}
	}
}

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
	Settings::PlayerColor == WHITE ? Global::playerTurn = true : Global::playerTurn = false;
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
		// rezise window
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

		// if game is over press 'R' to reset and play again :)
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r)
			resetGame();
	}
}

// update turns
void Game::update()
{
	if (Global::state == GAME_ON)
		Global::playerTurn ? playerPlayMove() : enginePlayMove();
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
		if(selectedSquare && Global::playerTurn)
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

bool Game::moveSetup()
{
	playerPieces.clear();
	playerMoves.clear();

	// "raw pieces"
	for(int i = 16; i < 32; i++)
		playerPieces.push_back(Pieces::get(i));

	// loop all pieces
	for(auto& i : playerPieces)
	{
		// filter pieces
		if(i.type != 6 && i.user == PLAYER)
		{
			// get all legal moves
			std::vector<Square> temp = LegalMove::getLegal(i);

			for(auto& j : temp)
				playerMoves.push_back(j);
		}
	}

	return !playerMoves.empty();
}

void Game::playerPlayMove()
{
	GameManager::update();

	if(!moveSetup())
	{
		if(Global::playerInCheck)
			Global::state = DEFEAT;
		else
			Global::state = DRAW;
	}
	else
	{
		// if selected new square
		if (selectedSquare != originalSquare && isPieceSelected)
		{
			// loop legal moves for the selected piece
			for (auto& i : legalMoves)
				if (selectedSquare->x == i.x && selectedSquare->y == i.y)
					executePlayerMove(i);
		}
	}
}

void Game::executePlayerMove(Square& sq)
{
	// loop players pieces to find the correct one
	for (int j = 16; j < 32; j++)
	{
		// filter moves
		if (Pieces::get(j).user == PLAYER && Pieces::get(j).type != 6)
		{
			// loop pieces and find correct one
			if (originalSquare == &Sqr::getSquare(Pieces::get(j).x, Pieces::get(j).y))
			{
				// make the move
				Move::execute(&Pieces::get(j), sq);

				legalMoves.clear();
				isPieceSelected = false;
				updateConsole();
				Global::playerTurn = false;
				return;
			}
		}
	}
}

// Engine's move:
void Game::enginePlayMove()
{
	GameManager::update();
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	engine.PlayMove();
	updateConsole();
}

// update console output
void Game::updateConsole()
{
	switch (Global::state)
	{
		case GAME_ON:
			updateConsoleText(Move::getName());
			break;
		case VICTORY:
			updateConsoleText("Checkmate! You won!");
			Global::state = END;
			break;
		case DEFEAT:
			updateConsoleText("Checkmate! You lost.");
			Global::state = END;
			break;
		case DRAW:
			updateConsoleText("Draw!");
			Global::state = END;
			break;
		default:
			break;
	}

	if (Global::state == END)
		updateConsoleText("Hit 'R' to play again.");
}

void Game::updateConsoleText(const std::string& text)
{
	console.push_back(new Text(text, Global::playerTurn));
	consoleIndex++;

	for (auto &i: console)
		i->position.y -= 18;
}

// reset game variables
void Game::resetGame()
{
	// pieces to their correct places
	Pieces::init();

	// gameplay settings to normal
	Global::playerKingMoved = false;
	Global::engineKingMoved = false;
	Global::playerQsideRookMoved = false;
	Global::playerKsideRookMoved = false;
	Global::engineQsideRookMoved = false;
	Global::engineKsideRookMoved = false;
	Global::playerCanCastleK = true;
	Global::playerCanCastleQ = true;
	Global::engineCanCastleK = true;
	Global::engineCanCastleQ = true;
	Global::playerInCheck = false;
	Global::engineInCheck = false;

	// set game to ON
	Global::state = GAME_ON;

	// white starts game
	Settings::PlayerColor == WHITE ? Global::playerTurn = true : Global::playerTurn = false;

	// unselect square
	originalSquare = nullptr;
	selectedSquare = nullptr;

	// clear console
	console.clear();
}


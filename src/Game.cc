#include "Game.hh"
#include "LegalMoves.hh"

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
	while(SDL_PollEvent(&e)) 
	{
		window->resize(e);

		// close application
		if((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT)
			ApplicationShouldClose = true;

		if(e.type == SDL_MOUSEMOTION)
        {
            // Get mouse position
            SDL_GetMouseState(&mousePos.x, &mousePos.y);
        }

        if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			// get mouse position
            SDL_GetMouseState(&mousePos.x, &mousePos.y);
            selectedSquare = GUI::onSelect(mousePos);

			// render possible moves
			for(int i = 0; i < 32; i++)
			{
				if(Pieces::get(i).x == selectedSquare->piece.x && Pieces::get(i).y == selectedSquare->piece.y)
				{
					if(Pieces::get(i).user == PLAYER)
            			isSquareSelected = true;
					
					// whats up with this
					if(Pieces::get(i).user != PLAYER && Settings::showEnemyLegalMoves)
            			isSquareSelected = true;

					if(Pieces::get(i).user == PLAYER)
					{
						originalSquare = selectedSquare;
						isPieceSelected = true;
					}
				}
	 
			}
			
        }
	}
}

bool Game::isCheck(bool player)
{
	if(player)
	{
		for(int i = 0; i < 16; i++)
		{
			std::vector v = LegalMove::get(Pieces::get(i));
			for(auto & j : v)
				if(j.piece.type == 5)
					return false;
		}
	}
	else
	{
		for(int i = 16; i < 32; i++)
		{
			std::vector v = LegalMove::get(Pieces::get(i));
			for(auto & j : v)
				if(j.piece.type == 5)
					return false;
		}
	}
	return true;
}


void Game::update()
{
	if (playerTurn)
	{
		if (!isCheck(true))
		{
			std::cout << "Check\n!";
		}
		playMove();
	}
	if (!playerTurn)
	{
		if (!isCheck(false))
		{
			std::cout << "Check!\n";
		}
		engine.PlayMove();
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

	// main rendering
	Renderer::render();
}

// Player's move logic:
void Game::playMove()
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
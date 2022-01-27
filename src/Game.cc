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
			if(selectedSquare->piece.user == PLAYER || Settings::showEnemyLegalMoves)
			{
            	isSquareSelected = true;
			}

			// only allowed for player
			if(selectedSquare->piece.user == PLAYER) 
			{
                originalSquare = selectedSquare;
                isPieceSelected = true;
            }
        }
	}
}

void Game::update() 
{
    if(playerTurn)
	{
		// if selected in eventhandler
		if(isPieceSelected)
		{
			// get legal moves
			std::vector<Square> legalMoves = LegalMove::get(originalSquare->piece);

			// if selected new square
			if(selectedSquare != originalSquare) 
			{
				for(int i = 0; i < (int)legalMoves.size(); i++) 
				{
					// if new click is in legal moves
					if(selectedSquare->x == legalMoves.at(i).x && selectedSquare->y == legalMoves.at(i).y) 
					{
						// loop players pieces to find the correct one
						for(int j = 16; j < 32; j++)
						{
							// loop pieces and find correct one
							if(originalSquare == &Sqr::getSquare(Pieces::get(j).x, Pieces::get(j).y))
							{
								// make the move
								Move(Pieces::get(j), legalMoves.at(i));
							}
						}
					}

					// player selects wrong piece
					else
					{
						isPieceSelected = false;
					}
				}
			}
		}
    }

	else
	{
	}

}


void Game::Move(Piece& source, Square target)
{
	// if moving to enemy's square
	if(target.piece.type != 6 && target.piece.type != 5)
	{
		for(int i = 0; i < 32; i++)
		{
			if(Pieces::get(i).x == target.x && Pieces::get(i).y == target.y)
			{
				Pieces::get(i).alive = false;
			}
		}
	}

	// get square of source and destination
	Square srcSquare = Sqr::getSquare(source.x, source.y);

	// creating new empty piece for source's place
	Piece piece;
	piece.x = srcSquare.x;
	piece.y = srcSquare.y;
	piece.type = NONE;

	// change source values (updating graphics)
	source.x = target.x;
	source.y = target.y;

	// updating squares
	Sqr::getSquare(srcSquare.x, srcSquare.y).piece = piece;
	Sqr::getSquare(target.x, target.y).piece = source;

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
   	for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if (GUI::onMouseRollOver(mousePos, Sqr::getSquare(x, y).rect))
			{
                Renderer::setColor(0, 255, 0);
                Renderer::fillRect(Sqr::getSquare(x, y).rect);
            }
            if (isSquareSelected) 
			{
				// selected square must be on board
				if(selectedSquare != nullptr)
				{
					// get legal moves of the piece in the square
					std::vector<Square> v = LegalMove::get(selectedSquare->piece);

                	Renderer::setColor(0, 0, 255);
					
					// color the selected square
                	Renderer::fillRect(selectedSquare->rect);

					// color legal moves of the piece in the selected square
                    Renderer::setColor(255, 0, 0 );
					for(auto & i : v)
					{
                		Renderer::fillRect(i.rect);
					}
				}
            }
       }
    }

	// render pieces
	for(int i = 0; i < 32; i++)
		PieceRenderer::renderInPosition(Pieces::get(i));

	// main rendering
	Renderer::render();
}



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

	// put pieces in correct places
	initPieces(Settings::PlayerColor);
}

Game::~Game()
{
	delete window;
	delete pieces;
	delete board;
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
            isSquareSelected = true;

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
						// loop all pieces to find the correct one
						for(auto& j : p)
						{
							// loop pieces and find correct one
							if(originalSquare->x == j.x && originalSquare->y == j.y)
							{
								// make the move
								Move(j, legalMoves.at(i));
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

	// engine's turn, why do I get warnings here?
	else
	{
	}

}



void Game::Move(Piece& source, Square target)
{
	// get square of source and destination
	Square srcSquare = Sqr::getSquare(source.x, source.y);
	Square dstSquare = Sqr::getSquare(target.x, target.y);

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
	Sqr::getSquare(dstSquare.x, dstSquare.y).piece = piece;
	Sqr::getSquare(target.x, target.y).piece = source;

	// if moving to enemy's square
	if(target.piece.type != 6)
	{
		for(auto&i : p)
		{
			if(selectedSquare->x == i.x && selectedSquare->y == dstSquare.y)
			{
			}
		}
		// why this does not work?
		target.piece.alive = false;
		dstSquare.piece = piece;
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
	for(auto& i : p)
		PieceRenderer::renderInPosition(i);

	// main rendering
	Renderer::render();
}


// initialize pieces into correct places and save information of pieces to squares
void Game::initPieces(int playerColor)
{
	// 0-7 		ENGINE PAWNS
	// 8-15 	ENGINE PIECES
	// 16-23 	PLAYER PAWNS
	// 24-31 	PLAYER PIECES

	// setting all pieces alive
	for(int i = 0; i < ARRSIZE(p); i++)
	{
		p[i].alive = true;
	}

	// initializing enemy's pieces colors
	for(int i = 0; i < 16; i++)
	{
		if(playerColor == Color::WHITE)
			p[i].color = Color::BLACK;
		else
			p[i].color = Color::WHITE;
	}

	// initializing player's pieces colors
	for(int i = 16; i < 32; i++)
	{
		if(playerColor == Color::WHITE)
			p[i].color = Color::WHITE;
		else
			p[i].color = Color::BLACK;
	}

	// engine pawns
	for(int i = 0; i < 8; i++)
	{
		p[i].type = PAWN;	
		p[i].x = i;
		p[i].y = 1;
		p[i].user = ENGINE;
		Sqr::getSquare(i, 1).piece = p[i];
	}

	// player pawns
	for(int i = 16; i < 24; i++)
	{
		p[i].type = PAWN;
		p[i].x = (i - 16);
		p[i].y = 6;
		p[i].user = PLAYER;
		Sqr::getSquare((i - 16), 6).piece = p[i];
	}


	// ENGINE PIECES
	for(int i = 8; i < 16; i++)
	{
		p[i].y = 0;
		p[i].user = ENGINE;
	}

	p[8].type = ROOK;
	p[8].x = 0;
	Sqr::getSquare(0, 0).piece = p[8];

	p[9].type = ROOK;
	p[9].x = 7;
	Sqr::getSquare(7, 0).piece = p[9];

	p[10].type = KNIGHT;
	p[10].x = 1;
	Sqr::getSquare(1, 0).piece = p[10];

	p[11].type = KNIGHT;
	p[11].x = 6;
	Sqr::getSquare(6, 0).piece = p[11];

	p[12].type = BISHOP;
	p[12].x = 2;
	Sqr::getSquare(2, 0).piece = p[12];
	
	p[13].type = BISHOP;
	p[13].x = 5;
	Sqr::getSquare(5, 0).piece = p[13];

	p[14].type = QUEEN;
	p[14].x = 3;
	Sqr::getSquare(3, 0).piece = p[14];

	p[15].type = KING;
	p[15].x = 4;
	Sqr::getSquare(4, 0).piece = p[15];


	// PLAYER PIECES
	for(int i = 24; i < 32; i++)
	{
		p[i].y = 7;
		p[i].user = PLAYER;
	}

	p[24].type = ROOK;
	p[24].x = 0;
	Sqr::getSquare(0, 7).piece = p[24];

	p[25].type = ROOK;
	p[25].x = 7;
	Sqr::getSquare(7, 7).piece = p[25];

	p[26].type = KNIGHT;
	p[26].x = 1;
	Sqr::getSquare(1, 7).piece = p[26];

	p[27].type = KNIGHT;
	p[27].x = 6;
	Sqr::getSquare(6, 7).piece = p[27];

	p[28].type = BISHOP;
	p[28].x = 2;
	Sqr::getSquare(2, 7).piece = p[28];

	p[29].type = BISHOP;
	p[29].x = 5;
	Sqr::getSquare(5, 7).piece = p[29];

	p[30].type = QUEEN;
	p[30].x = 3;
	Sqr::getSquare(3, 7).piece = p[30];

	p[31].type = KING;
	p[31].x = 4;
	Sqr::getSquare(4, 7).piece = p[31];

	// initialize empty squares as empty
	for(int y = 2; y < 6; y++)
		for(int x = 0; x < 8; x++)
		{
			Piece piece;
			piece.y = y;
			piece.x = x;
			piece.type = NONE;
			Sqr::getSquare(x, y).piece = piece;
		}
	
    if (playerColor == WHITE)
        playerTurn = true;
    else
        playerTurn = false;
}



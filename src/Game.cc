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
            e.type = SDL_MOUSEMOTION;
            SDL_GetMouseState(&mousePos.x, &mousePos.y);
        }

        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            e.type = SDL_MOUSEBUTTONDOWN;
            SDL_GetMouseState(&mousePos.x, &mousePos.y);
            selectedSquare = GUI::onSelect(mousePos);
            isSquareSelected = true;
        }
	}
}

void Game::update()
{
    Piece* selected = nullptr;
    std::vector<Square> v;
    Square* movingPosition = nullptr;

    /*
     * TODO: Game logic. And moving the pieces
     * TODO: Implement checking algorithm that the selected square is a valid move.
     * TODO: Implement logic for capturing opponent's pieces.
     *
     *
     * Game logic might resemble something like this:
     *
    if (isSquareSelected) {

        v = LegalMove::show(selectedSquare->piece);

        for (auto &i: v) {
            if (GUI::onSelect(mousePos) == Sqr::squareHelper(mousePos.x, mousePos.y))
            {
                movingPosition = Sqr::squareHelper(mousePos.x, mousePos.y);

                if (Sqr::squareHelper(mousePos.x, mousePos.y)->piece.color != Settings::PlayerColor)
                    Sqr::squareHelper(mousePos.x, mousePos.y)->piece.alive = false;

                if (selectedSquare->piece.x > movingPosition->x)
                    selectedSquare->piece.x--;
                if (selectedSquare->piece.y > movingPosition->y)
                    selectedSquare->piece.y--;
                if (selectedSquare->piece.x < movingPosition->x)
                    selectedSquare->piece.x++;
                if (selectedSquare->piece.y < movingPosition->y)
                    selectedSquare->piece.y++;
                else
                    playerTurn = false;
            }
        }
    }
     */
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
					std::vector<Square> v = LegalMove::show(selectedSquare->piece);

                	Renderer::setColor(0, 0, 255);
					
					// color the selected square
                	Renderer::fillRect(selectedSquare->rect);
					
					// color legal moves of the piece in the selected square
					for(auto & i : v)
					{
                        Renderer::setColor(255, 0, 0 );
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

	// engine pawns
	for(int i = 0; i < 8; i++)
	{
		p[i].type = PAWN;	
		p[i].x = i;
		p[i].y = 1;
		p[i].user = ENGINE;
		Sqr::getSquare(i, 1).piece.type = PAWN;
	}

	// player pawns
	for(int i = 16; i < 24; i++)
	{
		p[i].type = PAWN;
		p[i].x = (i - 16);
		p[i].y = 6;
		p[i].user = PLAYER;
		Sqr::getSquare((i - 16), 6).piece.type = PAWN;
	}

	// ENGINE PIECES
	for(int i = 8; i < 16; i++)
	{
		p[i].y = 0;
		p[i].user = ENGINE;
	}

	p[8].type = ROOK;
	p[8].x = 0;
	Sqr::getSquare(0, 0).piece.type = ROOK;

	p[9].type = ROOK;
	p[9].x = 7;
	Sqr::getSquare(7, 0).piece.type = ROOK;

	p[10].type = KNIGHT;
	p[10].x = 1;
	Sqr::getSquare(1, 0).piece.type = KNIGHT;

	p[11].type = KNIGHT;
	p[11].x = 6;
	Sqr::getSquare(6, 0).piece.type = KNIGHT;

	p[12].type = BISHOP;
	p[12].x = 2;
	Sqr::getSquare(2, 0).piece.type = BISHOP;
	
	p[13].type = BISHOP;
	p[13].x = 5;
	Sqr::getSquare(5, 0).piece.type = BISHOP;

	p[14].type = QUEEN;
	p[14].x = 3;
	Sqr::getSquare(3, 0).piece.type = QUEEN;

	p[15].type = KING;
	p[15].x = 4;
	Sqr::getSquare(4, 0).piece.type = KING;


	// PLAYER PIECES
	for(int i = 24; i < 32; i++)
	{
		p[i].y = 7;
		p[i].user = PLAYER;
	}

	p[24].type = ROOK;
	p[24].x = 0;
	Sqr::getSquare(0, 7).piece.type = ROOK;

	p[25].type = ROOK;
	p[25].x = 7;
	Sqr::getSquare(7, 7).piece.type = ROOK;

	p[26].type = KNIGHT;
	p[26].x = 1;
	Sqr::getSquare(1, 7).piece.type = KNIGHT;

	p[27].type = KNIGHT;
	p[27].x = 6;
	Sqr::getSquare(6, 7).piece.type = KNIGHT;

	p[28].type = BISHOP;
	p[28].x = 2;
	Sqr::getSquare(2, 7).piece.type = BISHOP;

	p[29].type = BISHOP;
	p[29].x = 5;
	Sqr::getSquare(5, 7).piece.type = BISHOP;

	p[30].type = QUEEN;
	p[30].x = 3;
	Sqr::getSquare(3, 7).piece.type = QUEEN;

	p[31].type = KING;
	p[31].x = 4;
	Sqr::getSquare(4, 7).piece.type = KING;


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

    if (playerColor == WHITE)
        playerTurn = true;
    else
        playerTurn = false;
}



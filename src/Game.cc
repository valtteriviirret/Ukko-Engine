#include "Game.hh"
#include "LegalMoves.hh"
#include "SquareManager.hh"

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

	
	// example of legalmove recognition
	Sqr::getSquare(1, 3).piece = ROOK;
	std::vector<Square> v (LegalMove::show(p[1]));

	std::cout << p[1].color;
	std::cout << p[1].x;
	std::cout << p[1].y;
	std::cout << p[1].type;
	std::cout << p[1].user;

	for(int i = 0; i < (int)v.size(); i++)
	{
		std::cout << v.at(i).piece;
	}

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
	}
}


// initialize pieces into correct places and save information of pieces to squares
void Game::initPieces(int playerColor)
{
	int bp = 1, b = 0, wp = 6, w = 7;

	// white and black change places
	if(playerColor != Color::WHITE)
	{
		bp = 6;
		b = 7;
		wp = 1;
		w = 0;
	}

	// pawns into places
	for(int i = 0; i < ARRSIZE(p); i++)
	{
		p[i].alive = true;

		if(i < 8)
		{
			// black pawns
			p[i].x = i;
			p[i].y = bp;
			p[i].type = PAWN;
			p[i].color = Color::BLACK;
			Sqr::getSquare(i, bp).piece = PAWN;
		}

		else if(i >= 8 && i < 16)
		{
			// x is defined in second loop
			p[i].y = b;
			p[i].color = Color::BLACK;
		}
		
		else if(i >= 16 && i < 24)
		{
			p[i].x = i - 16;
			p[i].y = wp;
			p[i].type = PAWN;
			p[i].color = Color::WHITE;
			Sqr::getSquare(i - 16, wp).piece = PAWN;
		}
		else
		{
			p[i].y = w;
			p[i].color = Color::WHITE;
		}
	}


	// rest of pieces into places
	for(int i = 0; i < ARRSIZE(p); i++)
	{
		if(i == 8 || i == 9 || i == 24 || i == 25)
		{
			p[i].type = ROOK;
			p[i].x = (i == 8 || i == 24) ? 0 : 7;

		}
		else if(i == 10 || i == 11 || i == 26 || i == 27)
		{
			p[i].type = KNIGHT;
			p[i].x = (i == 10 || i == 26) ? 1 : 6;
		}
		else if(i == 12 || i == 13 || i == 28 || i == 29)
		{
			p[i].type = BISHOP;
			p[i].x = (i == 13 || i == 28) ? 2 : 5;
		}
		else if(i == 14 || i == 30)
		{
			p[i].type = QUEEN;
			p[i].x = 3;
		}
		else if(i == 15 || i == 31)
		{
			p[i].type = KING;
			p[i].x = 4;
		}
	}
	
	// info of pieces saved into squares
	for(auto& i : p)
	{
		int y = (i.color == BLACK) ? bp : wp;
		Sqr::getSquare(i.x, y).piece = i.type;
	}

	// initialise user for piece
	for(int i = 0; i < ARRSIZE(p); i++)
	{
		if(i < 16)
			p[i].user = OPPONENT;
		else
			p[i].user = PLAYER;
	}
}

void Game::update()
{

}

// render pieces in their current positions
void Game::render()
{
    // make white background
    Renderer::setColor(255, 255, 255);
    Renderer::clear();

    // render board
    board->render();

	// color the square where to mouse is
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if (GUI::onMouseRollOver(mousePos, Sqr::getSquare(x, y).rect)) {
                Renderer::setColor(0, 255, 0);
                Renderer::fillRect(Sqr::getSquare(x, y).rect);
            }
        }
    }
	
	// render pieces
	for(auto& i : p)
		PieceRenderer::renderInPosition(i);

	// main rendering
	Renderer::render();
}

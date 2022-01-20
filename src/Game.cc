#include "Game.hh"
#include "SquareManager.hh"

Game::Game()
{
	initPieces(true);
}


// initialize pieces into correct places and save information of pieces to squares
void Game::initPieces(bool whiteBottom)
{
	int bp = 1, b = 0, wp = 6, w = 7;

	// white and black change places
	if(!whiteBottom)
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
			p[i].x = i;
			p[i].y = bp;
			p[i].type = PAWN;
			p[i].color = Color::BLACK;
			Sqr::getSquare(i, bp).piece = PAWN;
		}

		else if(i >= 8 && i < 16)
		{
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
	for(int i = 0; i < ARRSIZE(p); i++)
	{
		int y = (p[i].color == BLACK) ? bp : wp;
		Sqr::getSquare(p[i].x, y).piece = p[i].type;
	}

}

// render pieces in their currect positions
void Game::update()
{
	for(auto& i : p)
		PieceRenderer::renderInPosition(i);
}

#include "Game.hh"

Game::Game()
{
	// testpiece
	pieces[0].alive = true;
	pieces[0].color = true;
	pieces[0].type = "test";
	pieces[0].x = 0;
	pieces[0].y = 0;
}

void Game::initPieces()
{
	for(int i = 0; i < ARRSIZE(pieces); i++)
	{
		pieces[i].alive = true;

		// first 16 are black
		if(i < 16)
			pieces[i].color = true;
		else
			pieces[i].color = false;
	}
}

void Game::update()
{
	PieceRenderer::renderInPosition(pieces[0]);

	for(int i = 0; i < ARRSIZE(pieces); i++)
		PieceRenderer::renderInPosition(pieces[i]);
}

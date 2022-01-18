#include "Game.hh"

Game::Game()
{
	pieces[0].alive = true;
	pieces[0].color = true;
	pieces[0].type = "test";
	pieces[0].x = 0;
	pieces[0].y = 0;
}

void Game::update()
{
	Move::setPosition(pieces[0].x, pieces[0].y);
}

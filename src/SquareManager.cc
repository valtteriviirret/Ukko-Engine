#include "SquareManager.hh"

namespace Sqr
{
	// the actual squares
	Square squares[8][8];

	// getting individual square
	Square& getSquare(int x, int y) { return squares[x][y]; }

	// handle mouse events in square
	void handleEvent(Square square, SDL_Event e)
	{
		// if mouse event happened
		if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		{
			// get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);


		}

	}
}

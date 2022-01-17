#include "Board.hh"

Board::Board()
{
}

void Board::makeSquares()
{
	// width and height of single tile
	auto width = srcrect.w / 10 / 8 * 0.8f;
	auto height = srcrect.h / 10 / 8;

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			// make all squares
			squares[i][j].x = i * width;
			squares[i][j].y = j * height;
			squares[i][j].w = width;
			squares[i][j].h = height;

			// set rendering color to black
			Renderer::setColor(0, 0, 0);
			
			// render black squares
			if((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0))
			{
				Renderer::fillRect(squares[i][j]);
			}
		}
	}
}

void Board::makeRects()
{
	srcrect.x = 0;
	srcrect.y = 0;

	// make source bigger than screen size so the source will be the size of the window
	srcrect.w = Screen::getWidth() * 10;
	srcrect.h = Screen::getHeight() * 10;
    
	dstrect.x = 0;
    dstrect.y = 0;

	// leave space on the right
    dstrect.w = Screen::getWidth() * 0.8f; 
	dstrect.h = Screen::getHeight();
}

Board::~Board()
{
	SDL_DestroyTexture(board);
	board = nullptr;
}

void Board::render()
{
	// set the rendering color to red (testing)
	Renderer::setColor(255, 0, 0);

	// FUTURE PERFORMANCE UPGRADE, ONLY UPDATE THESE IF SCREENSIZE IS CHANGED
	// also then initialize in constructor

	// update rects
	makeRects();

	// update squares
	makeSquares();
}

// return board
SDL_Texture* Board::getBoard() { return board; }

// return square if the board
SDL_Rect Board::getSquare(int x, int y) { return squares[x][y]; }


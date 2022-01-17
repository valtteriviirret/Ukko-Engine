#include "Board.hh"

Board::Board()
{
	board = Texture::load("../Assets/board.png");

	if(board)
		dotdot = true;

	// for some reason different paths for us
	else
	{
		dotdot = false;
		std::cout << "Attempting to reload board\n";
		board = Texture::load("Assets/board.png");
	}

	if(!board)
		std::cout << "Failed to load board\n";

}

Board::~Board()
{
	SDL_DestroyTexture(board);
	board = nullptr;
}

SDL_Texture* Board::getBoard() { return board; }
bool Board::getDotDot() { return dotdot; }

void Board::render()
{
	SDL_Rect srcrect;
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = Screen::getWidth() * 10;
	srcrect.h = Screen::getHeight() * 10;
	SDL_Rect dstrect = srcrect;
	SDL_RenderCopy(Renderer::get(), board, &srcrect, nullptr);
}


#include "GUI.hh"

bool GUI::onMouseRollOver(SDL_Point &mousePos, SDL_Rect &square)
{
	return SDL_PointInRect(&mousePos, &square);
}

Square *GUI::onSelect(SDL_Point &mousePos)
{
	int x = mousePos.x * 10 / Screen::getWidth();
	int y = mousePos.y * 8 / Screen::getHeight();

	if (Sqr::squareHelper(x, y) != nullptr)
		return &Sqr::getSquare(x, y);
	else
		return &Sqr::getSquare(7, y);
}

void GUI::renderPromotionUI(SDL_Renderer *ren)
{
    SDL_Rect promotionTable = {0 + Screen::getWidth() / 12, Screen::getHeight() / 3, Screen::getWidth() / 3 * 2, Screen::getHeight() / 3};

    Button button[4] = {
            promotionTable.x + 50, promotionTable.y + 25, Screen::getWidth() / 10, Screen::getHeight() / 10, 10, QUEEN,
            promotionTable.x + 150, promotionTable.y + 25, Screen::getWidth() / 10, Screen::getHeight() / 10, 6, BISHOP,
            promotionTable.x + 250, promotionTable.y + 25, Screen::getWidth() / 10, Screen::getHeight() / 10, 11, ROOK,
            promotionTable.x + 350, promotionTable.y + 25, Screen::getWidth() / 10, Screen::getHeight() / 10, 8, KNIGHT
    };

    SDL_SetRenderDrawColor(ren, 128, 128, 128, 255);
    SDL_RenderFillRect(ren, &promotionTable);
}

#include "GUI.hh"

bool GUI::onMouseRollOver(SDL_Point& mousePos, SDL_Rect& square)
{
    return SDL_PointInRect(&mousePos, &square); 
}

Square* GUI::onSelect(SDL_Point& mousePos) {

    int x = mousePos.x * 10 / Screen::getWidth();
    int y = mousePos.y * 8 / Screen::getHeight();

    if (Sqr::squareHelper(x, y) != nullptr)
        return &Sqr::getSquare(x, y);
    else
        return &Sqr::getSquare(7, y);
	
	// Why did you do this?
	// We cannot utilize the right side for anything in the future, this makes no sense to me.
}

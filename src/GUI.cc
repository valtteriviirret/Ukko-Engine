#include "GUI.hh"

bool GUI::onMouseRollOver(SDL_Point& mousePos, SDL_Rect& square)
{
    if(SDL_PointInRect(&mousePos, &square)) {
        return true;
    }

    return false;
}

Square& GUI::onSelect(SDL_Point& mousePos) {

    int x = mousePos.x * 10 / Screen::getWidth();
    int y = mousePos.y * 8 / Screen::getHeight();

    if (Sqr::squareHelper(x, y) != nullptr)
        return Sqr::getSquare(x, y);

    return Sqr::getSquare(7, y);
}
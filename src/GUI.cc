#include "GUI.hh"

bool GUI::onMouseRollOver(SDL_Point& mousePos, SDL_Rect& square)
{
    if(SDL_PointInRect(&mousePos, &square)) {
        return true;
    }

    return false;
}

Square GUI::onSelect(SDL_Point& mousePos) {

    int x = mousePos.x / 80;
    int y = mousePos.y / 75;

    return Sqr::getSquare(x, y);
}

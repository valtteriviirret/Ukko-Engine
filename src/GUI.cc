#include "GUI.hh"

bool GUI::onMouseRollOver(SDL_Point& mousePos, SDL_Rect& square)
{
    if(SDL_PointInRect(&mousePos, &square)) {
        return true;
    }

    return false;
}

Square GUI::onSelect(SDL_Point& mousePos) {

    int x = mousePos.x / 80; // These values must be relative to screen size.
    int y = mousePos.y / 75; // Can be possibly fixed with Screen::getWidth() and Screen::getHeight()

    // TODO: Fix the bug when window size is changed

    return Sqr::getSquare(x, y);
}

#include "GUI.hh"
#include "iostream"

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

    // Kkona
    if (x > 8)
        y = 0;

    std::cout << "X: " << x << ", Y: " << y << "\n";

    return Sqr::getSquare(x, y);
}
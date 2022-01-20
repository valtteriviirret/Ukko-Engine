#include "GUI.hh"

SDL_Point GUI::mousePos(SDL_Event &e) {

    int x, y;

    // Get mouse position
    e.type = SDL_MOUSEMOTION;
    SDL_GetMouseState(&x, &y);

    return {x, y};
}

bool GUI::onMouseRollOver(SDL_Point& mousePos, SDL_Rect& square)
{
    if(SDL_PointInRect(&mousePos, &square)) {
        return true;
    }

    return false;
}
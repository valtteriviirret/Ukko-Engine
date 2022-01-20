//
// Created by valiant on 19.1.2022.
//

#include "GUI.hh"

void GUI::MouseEvent(SDL_Event &e) {

}

bool GUI::onMouseRollOver(SDL_Rect& square) {

    SDL_PumpEvents();
    SDL_GetMouseState(&mousePos.x, &mousePos.y);

    if(SDL_PointInRect(&mousePos, &square)) {
        return true;
    }

    return false;
}
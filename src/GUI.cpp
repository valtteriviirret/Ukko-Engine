//
// Created by valiant on 19.1.2022.
//

#include "GUI.h"

bool GUI::onMouseRollOver(SDL_Rect& square) {

    SDL_PumpEvents();
    SDL_GetMouseState(&mousePos.x, &mousePos.y);

    if(SDL_PointInRect(&mousePos, &square)) {
        squareSelected = square;
        return true;
    }

    return false;
}

void GUI::renderSelection(SDL_Rect square) {
    if (onMouseRollOver(square)) {
        Renderer::setColor(0, 255, 0);
        Renderer::fillRect(squareSelected);
    }
}
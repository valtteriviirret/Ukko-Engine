//
// Created by valiant on 19.1.2022.
//

#ifndef UKKOSHAKKI_GUI_HH
#define UKKOSHAKKI_GUI_HH

#include "SDL2/SDL.h"
#include "Board.hh"
#include "Renderer.hh"
#include "Square.hh"

class GUI {
private:
    static SDL_Point mousePos;
    static SDL_Rect& squareSelected;
    static bool onMouseRollOver(SDL_Rect& square);
public:
    static void renderSelection(SDL_Rect square);
};


#endif //UKKOSHAKKI_GUI_HH
